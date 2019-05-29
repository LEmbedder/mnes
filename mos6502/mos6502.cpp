#include <iomanip>
#include <iostream>
#include <sstream>
#include "mos6502.hpp"

#define BIND(function) std::bind(&mos6502::function, this)

const std::array<std::string, 4> mos6502::TOKENS = { "abs", "imm", "ind", "zpg" };

static void print_separator(unsigned size, std::ostream &stream);
template<typename T> static void print_hex_value(T value, std::ostream &stream);

mos6502::mos6502(unsigned num_pages, const std::vector<uint8_t> &rom_data)
{
    if (num_pages < 2)
        throw std::runtime_error("At least 2 pages must be allocated.");

    A_ = X_ = Y_ = 0;
    S_ = 0x00FF & STACK_TOP;
    PC_ = 0;
    irq_vector = 0xFFFF;
    cycles_ = 0;

    unsigned memory_size = num_pages * PAGE_SIZE;
    memory_.resize(memory_size);
    
    instructions.resize(256);

    const instruction INVALID = { "Invalid Opcode", -1, -1, BIND(invalid_opcode) };
    for (int i = 0; i < instructions.size(); i++)
        instructions[i] = INVALID;

    instructions[0x00] = { "BRK", 1, 7, BIND(BRK) };
    instructions[0x01] = { "ORA ($ind,X)", 2, 6, BIND(ORA_indX) };
    instructions[0x05] = { "ORA $zpg", 2, 3, BIND(ORA_zpg) };
    instructions[0x06] = { "ASL $zpg", 2, 5, BIND(ASL_zpg) };
    instructions[0x08] = { "PHP", 1, 3, BIND(PHP) };
    instructions[0x09] = { "ORA #$imm", 2, 2, BIND(ORA_imm) };
    instructions[0x0A] = { "ASL A", 1, 2, BIND(ASL_A) };
    instructions[0x0D] = { "ORA $abs", 3, 4, BIND(ORA_abs) };
    instructions[0x0E] = { "ASL $abs", 3, 6, BIND(ASL_abs) };

    instructions[0x10] = { "BPL", 2, 2, BIND(BPL) };
    instructions[0x11] = { "ORA ($ind),Y", 2, 5, BIND(ORA_indY) };
    instructions[0x15] = { "ORA $zpg,X", 2, 4, BIND(ORA_zpgX) };
    instructions[0x16] = { "ASL $zpg,X", 2, 6, BIND(ASL_zpgX) };
    instructions[0x18] = { "CLC", 1, 2, BIND(CLC) };
    instructions[0x19] = { "ORA $abs,Y", 3, 4, BIND(ORA_absY) };
    instructions[0x1D] = { "ORA $abs,X", 3, 4, BIND(ORA_absX) };
    instructions[0x1E] = { "ASL $abs,X", 3, 7, BIND(ASL_absX) };

    instructions[0x20] = { "JSR $abs", 3, 6, BIND(JSR_abs) };
    instructions[0x21] = { "AND ($ind,X)", 2, 6, BIND(AND_indX) };
    instructions[0x24] = { "BIT $zpg", 2, 3, BIND(BIT_zpg) };
    instructions[0x25] = { "AND $zpg", 2, 3, BIND(AND_zpg) };
    instructions[0x26] = { "ROL $zpg", 2, 5, BIND(ROL_zpg) };
    instructions[0x28] = { "PLP", 1, 4, BIND(PLP) };
    instructions[0x29] = { "AND #$imm", 2, 2, BIND(AND_imm) };
    instructions[0x2A] = { "ROL A", 1, 2, BIND(ROL_A) };
    instructions[0x2C] = { "BIT $abs", 3, 4, BIND(BIT_abs) };
    instructions[0x2D] = { "AND $abs", 3, 4, BIND(AND_abs) };

    instructions[0x30] = { "BMI", 2, 2, BIND(BMI) };
    instructions[0x31] = { "AND ($ind),Y", 2, 5, BIND(AND_indY) };
    instructions[0x35] = { "AND $zpg,X", 2, 4, BIND(AND_zpgX) };
    instructions[0x36] = { "ROL $zpg,X", 2, 6, BIND(ROL_zpgX) };
    instructions[0x38] = { "SEC", 1, 2, BIND(SEC) };
    instructions[0x39] = { "AND $abs,Y", 3, 4, BIND(AND_absY) };
    instructions[0x3D] = { "AND $abs,X", 3, 4, BIND(AND_absX) };
    instructions[0x3E] = { "ROL $abs,X", 3, 7, BIND(ROL_absX) };

    instructions[0x40] = { "RTI", 1, 6, BIND(RTI) };
    instructions[0x41] = { "EOR ($ind,X)", 2, 6, BIND(EOR_indX) };
    instructions[0x45] = { "EOR $zpg", 2, 3, BIND(EOR_zpg) };
    instructions[0x46] = { "LSR $zpg", 2, 5, BIND(LSR_zpg) };
    instructions[0x48] = { "PHA", 1, 3, BIND(PHA) };
    instructions[0x49] = { "EOR #$imm", 2, 2, BIND(EOR_imm) };
    instructions[0x4A] = { "LSR A", 1, 2, BIND(LSR_A) };
    instructions[0x4C] = { "JMP $abs", 3, 3, BIND(JMP_abs) };
    instructions[0x4D] = { "EOR $abs", 3, 4, BIND(EOR_abs) };
    instructions[0x4E] = { "LSR $abs", 3, 6, BIND(LSR_abs) };

    instructions[0x50] = { "BVC", 2, 2, BIND(BVC) };
    instructions[0x51] = { "EOR ($ind),Y", 2, 5, BIND(EOR_indY) };
    instructions[0x55] = { "EOR $zpg,X", 2, 4, BIND(EOR_zpgX) };
    instructions[0x56] = { "LSR $zpg,X", 2, 6, BIND(LSR_zpgX) };
    instructions[0x58] = { "CLI", 1, 2, BIND(CLI) };
    instructions[0x59] = { "EOR $abs,Y", 3, 4, BIND(EOR_absY) };
    instructions[0x5D] = { "EOR $abs,X", 3, 4, BIND(EOR_absX) };
    instructions[0x5E] = { "LSR $abs,X", 3, 7, BIND(LSR_absX) };

    instructions[0x60] = { "RTS", 1, 6, BIND(RTS) };
    instructions[0x61] = { "ADC ($ind,X)", 2, 6, BIND(ADC_indX) };
    instructions[0x65] = { "ADC $zpg", 2, 3, BIND(ADC_zpg) };
    instructions[0x66] = { "ROR $zpg", 2, 5, BIND(ROR_zpg) };
    instructions[0x68] = { "PLA", 1, 4, BIND(PLA) };
    instructions[0x69] = { "ADC #$imm", 2, 2, BIND(ADC_imm) };
    instructions[0x6A] = { "ROR A", 1, 2, BIND(ROR_A) };
    instructions[0x6C] = { "JMP ($ind)", 3, 5, BIND(JMP_ind) };
    instructions[0x6D] = { "ADC $abs", 3, 4, BIND(ADC_abs) };
    instructions[0x6E] = { "ROR $abs", 3, 6, BIND(ROR_abs) };

    instructions[0x70] = { "BVS", 2, 2, BIND(BVS) };
    instructions[0x71] = { "ADC ($ind),Y", 2, 5, BIND(ADC_indY) };
    instructions[0x75] = { "ADC $zpg,X", 2, 4, BIND(ADC_zpgX) };
    instructions[0x76] = { "ROR $zpg,X", 2, 6, BIND(ROR_zpgX) };
    instructions[0x78] = { "SEI", 1, 2, BIND(SEI) };
    instructions[0x79] = { "ADC $abs,Y", 3, 4, BIND(ADC_absY) };
    instructions[0x7D] = { "ADC $abs,X", 3, 4, BIND(ADC_absX) };
    instructions[0x7E] = { "ROR $abs,X", 3, 7, BIND(ROR_absX) };

    instructions[0x81] = { "STA ($ind,X)", 2, 6, BIND(STA_indX) };
    instructions[0x84] = { "STY $zpg", 2, 3, BIND(STY_zpg) };
    instructions[0x85] = { "STA $zpg", 2, 3, BIND(STA_zpg) };
    instructions[0x86] = { "STX $zpg", 2, 3, BIND(STX_zpg) };
    instructions[0x88] = { "DEY", 1, 2, BIND(DEY) };
    instructions[0x8A] = { "TXA", 1, 2, BIND(TXA) };
    instructions[0x8C] = { "STY $abs", 3, 4, BIND(STY_abs) };
    instructions[0x8D] = { "STA $abs", 3, 4, BIND(STA_abs) };
    instructions[0x8E] = { "STX $abs", 3, 4, BIND(STX_abs) };

    instructions[0x90] = { "BCC", 2, 2, BIND(BCC) };
    instructions[0x91] = { "STA ($ind),Y", 2, 6, BIND(STA_indY) };
    instructions[0x94] = { "STY $zpg,X", 2, 4, BIND(STY_zpgX) };
    instructions[0x95] = { "STA $zpg,X", 2, 4, BIND(STA_zpgX) };
    instructions[0x96] = { "STX $zpg,Y", 2, 4, BIND(STX_zpgY) };
    instructions[0x98] = { "TYA", 1, 2, BIND(TYA) };
    instructions[0x99] = { "STA $abs,Y", 3, 5, BIND(STA_absY) };
    instructions[0x9A] = { "TXS", 1, 2, BIND(TXS) };
    instructions[0x9D] = { "STA $abs,X", 3, 5, BIND(STA_absX) };

    instructions[0xA0] = { "LDY #$imm", 2, 2, BIND(LDY_imm) };
    instructions[0xA1] = { "LDA ($ind,X)", 2, 6, BIND(LDA_indX) };
    instructions[0xA2] = { "LDX #$imm", 2, 2, BIND(LDX_imm) };
    instructions[0xA4] = { "LDY $zpg", 2, 3, BIND(LDY_zpg) };
    instructions[0xA5] = { "LDA $zpg", 2, 3, BIND(LDA_zpg) };
    instructions[0xA6] = { "LDX $zpg", 2, 3, BIND(LDX_zpg) };
    instructions[0xA8] = { "TAY", 1, 2, BIND(TAY) };
    instructions[0xA9] = { "LDA #$imm", 2, 2, BIND(LDA_imm) };
    instructions[0xAA] = { "TAX", 1, 2, BIND(TAX) };
    instructions[0xAC] = { "LDY $abs", 3, 4, BIND(LDY_abs) };
    instructions[0xAD] = { "LDA $abs", 3, 4, BIND(LDA_abs) };
    instructions[0xAE] = { "LDX $abs", 3, 4, BIND(LDX_abs) };

    instructions[0xB0] = { "BCS", 2, 2, BIND(BCS) };
    instructions[0xB1] = { "LDA ($ind),Y", 2, 5, BIND(LDA_indY) };
    instructions[0xB4] = { "LDY $zpg,X", 2, 4, BIND(LDY_zpgX) };
    instructions[0xB5] = { "LDA $zpg,X", 2, 4, BIND(LDA_zpgX) };
    instructions[0xB6] = { "LDX $zpg,Y", 2, 4, BIND(LDX_zpgY) };
    instructions[0xB8] = { "CLV", 1, 2, BIND(CLV) };
    instructions[0xB9] = { "LDA $abs,Y", 3, 4, BIND(LDA_absY) };
    instructions[0xBA] = { "TSX", 1, 2, BIND(TSX) };
    instructions[0xBC] = { "LDY $abs,X", 3, 4, BIND(LDY_absX) };
    instructions[0xBD] = { "LDA $abs,X", 3, 4, BIND(LDA_absX) };
    instructions[0xBE] = { "LDX $abs,Y", 3, 4, BIND(LDX_absY) };

    instructions[0xC0] = { "CPY #$imm", 2, 2, BIND(CPY_imm) };
    instructions[0xC1] = { "CMP ($ind,X)", 2, 6, BIND(CMP_indX) };
    instructions[0xC4] = { "CPY $zpg", 2, 3, BIND(CPY_zpg) };
    instructions[0xC5] = { "CMP $zpg", 2, 3, BIND(CMP_zpg) };
    instructions[0xC6] = { "DEC $zpg", 2, 5, BIND(DEC_zpg) };
    instructions[0xC8] = { "INY", 1, 2, BIND(INY) };
    instructions[0xC9] = { "CMP #$imm", 2, 2, BIND(CMP_imm) };
    instructions[0xCA] = { "DEX", 1, 2, BIND(DEX) };
    instructions[0xCC] = { "CPY $abs", 3, 4, BIND(CPY_abs) };
    instructions[0xCD] = { "CMP $abs", 3, 4, BIND(CMP_abs) };
    instructions[0xCE] = { "DEC $abs", 3, 6, BIND(DEC_abs) };

    instructions[0xD0] = { "BNE", 2, 2, BIND(BNE) };
    instructions[0xD1] = { "CMP ($ind),Y", 2, 5, BIND(CMP_indY) };
    instructions[0xD5] = { "CMP $zpg,X", 2, 4, BIND(CMP_zpgX) };
    instructions[0xD6] = { "DEC $zpg,X", 2, 6, BIND(DEC_zpgX) };
    instructions[0xD8] = { "CLD", 1, 2, BIND(CLD) };
    instructions[0xD9] = { "CMP $abs,Y", 3, 4, BIND(CMP_absY) };
    instructions[0xDD] = { "CMP $abs,X", 3, 4, BIND(CMP_absX) };
    instructions[0xDE] = { "DEC $abs,X", 3, 7, BIND(DEC_absX) };

    instructions[0xE0] = { "CPX #$imm", 2, 2, BIND(CPX_imm) };
    instructions[0xE1] = { "SBC ($ind,X)", 2, 6, BIND(SBC_indX) };
    instructions[0xE4] = { "CPX $zpg", 2, 3, BIND(CPX_zpg) };
    instructions[0xE5] = { "SBC $zpg", 2, 3, BIND(SBC_zpg) };
    instructions[0xE6] = { "INC $zpg", 2, 5, BIND(INC_zpg) };
    instructions[0xE8] = { "INX", 1, 2, BIND(INX) };
    instructions[0xE9] = { "SBC #$imm", 2, 2, BIND(SBC_imm) };
    instructions[0xEA] = { "NOP", 1, 2, BIND(NOP) };
    instructions[0xEC] = { "CPX $abs", 3, 4, BIND(CPX_abs) };
    instructions[0xED] = { "SBC $abs", 3, 4, BIND(SBC_abs) };
    instructions[0xEE] = { "INC $abs", 3, 6, BIND(INC_abs) };

    instructions[0xF0] = { "BEQ", 2, 2, BIND(BEQ) };
    instructions[0xF1] = { "SBC ($ind),Y", 2, 5, BIND(SBC_indY) };
    instructions[0xF5] = { "SBC $zpg,X", 2, 4, BIND(SBC_zpgX) };
    instructions[0xF6] = { "INC $zpg,X", 2, 6, BIND(INC_zpgX) };
    instructions[0xF8] = { "SED", 1, 2, BIND(SED) };
    instructions[0xF9] = { "SBC $abs,Y", 3, 4, BIND(SBC_absY) };
    instructions[0xFD] = { "SBC $abs,X", 3, 4, BIND(SBC_absX) };
    instructions[0xFE] = { "INC $abs,X", 3, 7, BIND(INC_absX) };
}

std::string mos6502::disassemble(const std::vector<uint8_t> &buffer, uint16_t &pc)
{
    instruction instr = instructions[buffer[pc]];

    int operand = 0;
    for (int i = instr.size - 1; i > 0; i--) {
        unsigned address = pc + 1;
        operand |= buffer[address] << 8;
    }
    
    std::ostringstream oss;
    oss << std::hex << operand;

    size_t index = 0;
    std::string syntax = instr.syntax;
    for (auto token : TOKENS) {
        index = syntax.find(token);
        if (index != std::string::npos) {
            syntax.replace(index, token.length(), oss.str());
            break;
        }
    }

    pc += instr.size;
    return syntax;
}

uint8_t mos6502::memory(uint16_t address) const { return memory_[address]; }

void mos6502::print_state(std::ostream &stream) const
{
    stream << "A = ";
    print_hex_value(A_, stream);
    stream << "  X = ";
    print_hex_value(X_, stream);
    stream << "  Y = ";
    print_hex_value(Y_, stream);
    stream << "  S = ";
    print_hex_value(S_, stream);
    stream << "  PC = ";
    print_hex_value(PC_, stream);
    stream << std::endl << "NV-B-IZC" << std::endl;
    for (int i = 0; i < sizeof(uint8_t) * 8; i++) {
        if (i == 2 || i == 4) {
            stream << "-";
            continue;
        }
        stream << P_[i];
    }
    stream << std::endl << "Elapsed Cycles: " << cycles_ << std::endl << std::endl;
}

void mos6502::print_memory(unsigned bytes_per_row, std::ostream &stream) const
{
    for (uint16_t i = 0; i < memory_.size(); i += bytes_per_row) {
        if (i % 256 == 0)
            print_separator(58, stream);

        print_hex_value(i, stream);
        stream << "-";
        print_hex_value(static_cast<uint16_t>(i + bytes_per_row - 1), stream);
        stream << ": ";

        for (unsigned j = i; j < i + bytes_per_row; j++) {
            print_hex_value(memory_[j], stream);
            stream << " ";
        }
        stream << std::endl;
    }
    print_separator(58, stream);
}

void mos6502::load_memory(uint16_t address, uint8_t value) { memory_[address] = value; }

bool mos6502::negative(uint8_t value) { return (value >> 7) != 0; }

bool mos6502::zero(uint8_t value) { return value == 0; }

void mos6502::step_pc() { PC_ += instructions[memory(PC())].size; }

void mos6502::step_cycles() { cycles_ += instructions[memory(PC())].cycles; }

void mos6502::push_stack(uint8_t value)
{
    if (S() == STACK_BOTTOM)
        throw std::runtime_error("Stack overflow");

    load_memory(S(), value);
    --S_;
}

void mos6502::push_flags()
{
    uint8_t flags = 0;
    for (int i = 0; i < P_.size(); i++)
        flags |= (P_[i] << i);
    push_stack(flags);
}

uint8_t mos6502::pop_stack()
{
    if (S() == STACK_TOP)
        throw std::runtime_error("Empty stack");

    uint8_t value = memory(S());
    ++S_;
    return value;
}

void mos6502::pop_flags()
{
    uint8_t flags = pop_stack();
    for (int i = 0; i < P_.size(); i++)
        P_[i] = ((flags >> i) & 1);
}

void mos6502::branch()
{
    ++cycles_;
    uint16_t pc = PC_ + rel();
    if ((pc & 0xFF00) != (PC_ & 0xFF00))
        ++cycles_;
    PC_ = pc;
}

uint8_t mos6502::imm() { return memory(PC() + 1); }

uint8_t mos6502::rel()
{
    uint8_t value = memory(PC() + 1);
    if ((value & 0x80) != 0) {
        value &= 0x7F;
        value *= -1;
    }

    return value;
}

uint16_t mos6502::zpg() { return memory(PC() + 1); }

uint16_t mos6502::zpgX()
{
    uint16_t address = memory(PC() + 1) + X();
    return address & 0xFF;
}

uint16_t mos6502::zpgY()
{
    uint16_t address = memory(PC() + 1) + Y();
    return address & 0xFF;
}

uint16_t mos6502::abs() { return (memory(PC() + 2) << 8) | memory(PC() + 1); }

uint16_t mos6502::absX()
{
    uint16_t address = (memory(PC() + 2) << 8) | memory(PC() + 1);
    uint32_t effective = address + X();
    if ((effective & 0xFFFF0000) != (address & 0xFF00))
        ++cycles_;

    return effective;
}

uint16_t mos6502::absY()
{
    uint16_t address = (memory(PC() + 2) << 8) | memory(PC() + 1);
    uint32_t effective = address + Y();
    if ((effective & 0xFFFF0000) != (address & 0xFF00))
        ++cycles_;

    return effective;
}

uint16_t mos6502::indX()
{
    uint16_t address = memory(memory(PC() + 1) + X());
    return address & 0xFF;
}

uint16_t mos6502::indY()
{
    uint16_t address = memory(memory(PC() + 1));
    uint32_t effective = address + Y();
    if ((effective & 0xFFFF0000) != (address & 0xFF00))
        ++cycles_;

    return effective;
}

void mos6502::invalid_opcode() { throw std::runtime_error("Invalid Opcode"); }

template<typename T>
static void print_hex_value(T value, std::ostream &stream)
{
    stream << std::setfill('0') << std::setw(sizeof(value) * 2) << std::hex << std::uppercase;
    stream << static_cast<int>(value);
}

void print_separator(unsigned size, std::ostream &stream)
{
    for (unsigned i = 0; i < size; i++)
        stream << "-";
    stream << std::endl;
}

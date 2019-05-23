#include <cstdio>
#include <sstream>
#include "mos6502.hpp"

const std::string mos6502::INVALID = "Invalid Opcode";
const std::array<std::string, 4> mos6502::TOKENS = { "abs", "imm", "ind", "zpg" };

mos6502::mos6502(unsigned memory_size)
{
    A_ = X_ = Y_ = P_ = SP_ = 0;
    PC_ = 0;
    memory_.resize(memory_size);
}

uint8_t mos6502::read_flag(flag_type type) const
{
    switch (type) {
    case flag_type::negative:
        return (P_ >> 7) & 1;
    case flag_type::overflow:
        return (P_ >> 6) & 1;
    case flag_type::brk:
        return (P_ >> 4) & 1;
    case flag_type::decimal_mode:
        return (P_ >> 3) & 1;
    case flag_type::interrupt_disable:
        return (P_ >> 2) & 1;
    case flag_type::zero:
        return (P_ >> 1) & 1;
    case flag_type::carry:
        return P_ & 1;
    default:
        throw std::runtime_error("Invalid flag type.");
    }
}

std::string mos6502::disassemble(const std::vector<uint8_t> &buffer, unsigned &pc)
{
    instruction instr = INSTRUCTIONS[buffer[pc]];

    int operand = 0;
    for (int i = instr.size - 1; i > 0; i--)
        operand |= buffer[pc + static_cast<uint64_t>(i)] << 8;
    
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

void mos6502::execute_instruction()
{
    switch (memory_[PC_]) {
    case 0x00: // BRK
        break;
    case 0x01: // ORA ($ind,X)
        break;
    case 0x05: // ORA $zpg
        break;
    case 0x06: // ASL $zpg
        break;
    case 0x08: // PHP
        break;
    case 0x09: // ORA #$imm
        break;
    case 0x0A: // ASL A
        break;
    case 0x0D: // ORA $abs
        break;
    case 0x0E: // ASL $abs
        break;

    case 0x10: // BPL
        break;
    case 0x11: // ORA ($ind),Y
        break;
    case 0x15: // ORA $zpg,X
        break;
    case 0x16: // ASL $zpg,X
        break;
    case 0x18: // CLC
        break;
    case 0x19: // ORA $abs,Y
        break;
    case 0x1D: // ORA $abs,X
        break;
    case 0x1E: // ASL $abs,X
        break;

    case 0x20: // JSR $abs
        break;
    case 0x21: // AND ($ind,X)
        break;
    case 0x24: // BIT $zpg
        break;
    case 0x25: // AND $zpg
        break;
    case 0x26: // ROL $zpg
        break;
    case 0x28: // PLP
        break;
    case 0x29: // AND #$imm
        break;
    case 0x2A: // ROL A
        break;
    case 0x2C: // BIT $abs
        break;
    case 0x2D: // AND $abs
        break;
    case 0x2E: // ROL $abs
        break;

    case 0x30: // BMI
        break;
    case 0x31: // AND ($ind),Y
        break;
    case 0x35: // AND $zpg,X
        break;
    case 0x36: // ROL $zpg,X
        break;
    case 0x38: // SEC
        break;
    case 0x39: // AND $abs,Y
        break;
    case 0x3D: // AND $abs,X
        break;
    case 0x3E: // ROL $abs,X
        break;

    case 0x40: // RTI
        break;
    case 0x41: // EOR ($ind,X)
        break;
    case 0x45: // EOR $zpg
        break;
    case 0x46: // LSR $zpg
        break;
    case 0x48: // PHA
        break;
    case 0x49: // EOR #$imm
        break;
    case 0x4A: // LSR A
        break;
    case 0x4C: // JMP $abs
        break;
    case 0x4D: // EOR $abs
        break;

    case 0x4E: // LSR $abs
        break;
    case 0x50: // BVC
        break;
    case 0x51: // EOR ($ind),Y
        break;
    case 0x55: // EOR $zpg,X
        break;
    case 0x56: // LSR $zpg,X
        break;
    case 0x58: // CLI
        break;
    case 0x59: // EOR $abs,Y
        break;
    case 0x5D: // EOR $abs,X
        break;
    case 0x5E: // LSR $abs,X
        break;

    case 0x60: // RTS
        break;
    case 0x61: // ADC ($ind,X)
        break;
    case 0x65: // ADC $zpg
        break;
    case 0x66: // ROR $zpg
        break;
    case 0x68: // PLA   
        break;
    case 0x69: // ADC #$imm
        break;
    case 0x6A: // ROR A
        break;
    case 0x6C: // JMP ($ind)
        break;
    case 0x6D: // ADC $abs
        break;
    case 0x6E: // ROR $abs
        break;

    case 0x70: // BVS
        break;
    case 0x71: // ADC ($ind),Y
        break;
    case 0x75: // ADC $zpg,X
        break;
    case 0x76: // ROR $zpg,X
        break;
    case 0x78: // SEI
        break;
    case 0x79: // ADC $abs,Y
        break;
    case 0x7D: // ADC $abs,X
        break;
    case 0x7E: // ROR $abs,X
        break;

    case 0x81: // STA ($ind,X)
        break;
    case 0x84: // STY $zpg
        break;
    case 0x85: // STA $zpg
        break;
    case 0x86: // STX $zpg
        break;
    case 0x88: // DEY
        break;
    case 0x8A: // TXA
        break;
    case 0x8C: // STY $abs
        break;
    case 0x8D: // STA $abs
        break;
    case 0x8E: // STX $abs
        break;

    case 0x90: // BCC
        break;
    case 0x91: // STA ($ind),Y
        break;
    case 0x94: // STY $zpg,X
        break;
    case 0x95: // STA $zpg,X
        break;
    case 0x96: // STX $zpg,Y
        break;
    case 0x98: // TYA
        break;
    case 0x99: // STA $abs,Y
        break;
    case 0x9A: // TXS
        break;
    case 0x9D: // STA $abs,X
        break;

    case 0xA0: // LDY #$imm
        break;
    case 0xA1: // LDA ($ind,X)
        break;
    case 0xA2: // LDX #$imm
        break;
    case 0xA4: // LDY $zpg
        break;
    case 0xA5: // LDA $zpg
        break;
    case 0xA6: // LDX $zpg
        break;
    case 0xA8: // TAY
        break;
    case 0xA9: // LDA #$imm
        break;
    case 0xAA: // TAX
        break;
    case 0xAC: // LDY $abs
        break;
    case 0xAD: // LDA $abs
        break;
    case 0xAE: // LDX $abs
        break;

    case 0xB0: // BCS
        break;
    case 0xB1: // LDA ($ind),Y
        break;
    case 0xB4: // LDY $zpg,X
        break;
    case 0xB5: // LDA $zpg,X
        break;
    case 0xB6: // LDX $zpg,Y
        break;
    case 0xB8: // CLV
        break;
    case 0xB9: // LDA $abs,Y
        break;
    case 0xBA: // TSX
        break;
    case 0xBC: // LDY $abs,X
        break;
    case 0xBD: // LDA $abs,X
        break;
    case 0xBE: // LDX $abs,Y
        break;

    case 0xC0: // CPY #$imm
        break;
    case 0xC1: // CMP ($ind,X)
        break;
    case 0xC4: // CPY $zpg
        break;
    case 0xC5: // CMP $zpg
        break;
    case 0xC6: // DEC $zpg
        break;
    case 0xC8: // INY
        break;
    case 0xC9: // CMP #$imm
        break;
    case 0xCA: // DEX
        break;
    case 0xCC: // CPY $abs
        break;
    case 0xCD: // CMP $abs
        break;
    case 0xCE: // DEC $abs
        break;

    case 0xD0: // BNE
        break;
    case 0xD1: // CMP ($ind),Y
        break;
    case 0xD5: // CMP $zpg,X
        break;
    case 0xD6: // DEC $zpg,X
        break;
    case 0xD8: // CLD
        break;
    case 0xD9: // CMP $abs,Y
        break;
    case 0xDD: // CMP $abs,X
        break;
    case 0xDE: // DEC $abs,X
        break;

    case 0xE0: // CPX #$imm
        break;
    case 0xE1: // SBC ($ind,X)
        break;
    case 0xE4: // CPX $zpg
        break;
    case 0xE5: // SBC $zpg
        break;
    case 0xE6: // INC $zpg
        break;
    case 0xE8: // INX
        break;
    case 0xE9: // SBC #$imm
        break;
    case 0xEA: // NOP
        break;
    case 0xEC: // CPX $abs
        break;
    case 0xED: // SBC $abs
        break;
    case 0xEE: // INC $abs
        break;

    case 0xF0: // BEQ
        break;
    case 0xF1: // SBC ($ind),Y
        break;
    case 0xF5: // SBC $zpg,X
        break;
    case 0xF6: // INC $zpg,X
        break;
    case 0xF8: // SED
        break;
    case 0xF9: // SBC $abs,Y
        break;
    case 0xFD: // SBC $abs,X
        break;
    case 0xFE: // INC $abs,X
        break;
    default:
        throw std::runtime_error(INVALID);
    }
}

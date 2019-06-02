#include <iomanip>
#include <iostream>
#include <sstream>
#include "mos6502.hpp"

const std::array<std::string, 4> mos6502::TOKENS = { "abs", "imm", "ind", "zpg" };

static void print_separator(unsigned size, std::ostream &stream);
template<typename T> static void print_hex_value(T value, std::ostream &stream);

mos6502::mos6502(unsigned num_pages, const std::vector<uint8_t> &rom_data)
{
    if (num_pages < 2)
        throw std::runtime_error("At least 2 pages must be allocated.");
    else if (num_pages > 256)
        throw std::runtime_error("The number of pages to allocated cannot exceed 256.");

    A_ = X_ = Y_ = S_ = 0;
    PC_ = 0;
    P_[2] = true;
    P_[INTERRUPT_DISABLE] = true;
    cycles_ = 0;

    unsigned memory_size = num_pages * PAGE_SIZE;
    memory_.resize(memory_size);
    std::copy(rom_data.begin(), rom_data.end(), memory_.begin());
    
    reset();
    load_instructions();
}

std::string mos6502::disassemble() { return disassemble(memory_, PC()); }

std::string mos6502::disassemble(const std::vector<uint8_t> &buffer, uint16_t pc)
{
    instruction instr = instructions[buffer[pc]];

    int operand = 0;
    for (int i = instr.size - 1; i > 0; i--) {
        unsigned address = pc + i;
        operand |= buffer[address] << (8 * (i - 1));
    }
    
    std::ostringstream oss;
    if (instr.size == 2)
        print_hex_value(static_cast<uint8_t>(operand), oss);
    else if (instr.size == 3)
        print_hex_value(static_cast<uint16_t>(operand), oss);

    size_t index = 0;
    std::string syntax = instr.syntax;
    for (auto token : TOKENS) {
        index = syntax.find(token);
        if (index != std::string::npos) {
            syntax.replace(index, token.length(), oss.str());
            break;
        }
    }

    return syntax;
}

uint8_t mos6502::memory(uint16_t address) const { return memory_[address]; }

void mos6502::print_state(std::ostream &stream) const
{
    stream << " PC:";
    print_hex_value(PC_, stream);
    stream << " A:";
    print_hex_value(A_, stream);
    stream << " X:";
    print_hex_value(X_, stream);
    stream << " Y:";
    print_hex_value(Y_, stream);

    uint8_t flags = 0;
    stream << " P:";
    for (int i = 0; i < P_.size(); i++)
        flags |= (P_[i] << i);
    print_hex_value(flags, stream);

    stream << " S:";
    print_hex_value(S_, stream);
    stream << std::dec << " Cyc:" << cycles_ << std::endl;
}

void mos6502::print_memory(std::ostream &stream) const
{
    constexpr unsigned BYTES_PER_ROW = 16;
    for (unsigned i = 0; i < memory_.size(); i += BYTES_PER_ROW) {
        if (i % 256 == 0)
            print_separator(58, stream);

        print_hex_value(static_cast<uint16_t>(i), stream);
        stream << "-";
        print_hex_value(static_cast<uint16_t>(i + BYTES_PER_ROW - 1), stream);
        stream << ": ";

        for (unsigned j = i; j < i + BYTES_PER_ROW; j++) {
            print_hex_value(memory_[j], stream);
            stream << " ";
        }
        stream << std::endl;
    }
    print_separator(58, stream);
}

void mos6502::execute_instruction() { instructions[memory(PC())].impl(); }

uint16_t mos6502::combine(uint8_t high, uint8_t low) { return (high << 8) | low; }

uint16_t mos6502::read_vector(uint16_t address)
{
    uint16_t value = combine(memory(address + 1), memory(address));
    return value;
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

void mos6502::reset()
{
    S_ = 0xFD;
    PC_ = read_vector(RESET);
    cycles_ += 7;
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

uint16_t mos6502::abs() { return read_vector(PC()); }

uint16_t mos6502::absX()
{
    uint16_t address = read_vector(PC());
    uint32_t effective = address + X();
    if ((effective & 0xFFFF0000) != (address & 0xFF00))
        ++cycles_;

    return effective;
}

uint16_t mos6502::absY()
{
    uint16_t address = read_vector(PC());
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

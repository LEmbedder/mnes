#include <iomanip>
#include <iostream>
#include "mos6502.hpp"

template<typename T>
static void print_hex_value(T value, std::ostream &stream);

void mos6502::print_state(std::ostream &stream) const
{
    stream << "A = ";
    print_hex_value(A_, stream);
    stream << "  X = ";
    print_hex_value(X_, stream);
    stream << "  Y = ";
    print_hex_value(Y_, stream);
    stream << "  PC = ";
    print_hex_value(PC_, stream);
    stream << std::endl << "NV-BDIZC" << std::endl;
    for (int i = 0; i < sizeof(uint8_t) * 8; i++) {
        if (i == 2) {
            stream << "-";
            continue;
        }
        stream << P_[i];
    }
    stream << std::endl << std::endl;
}

void mos6502::print_memory(unsigned bytes_per_row, std::ostream &stream) const
{
    for (uint16_t i = 0; i < memory_.size(); i += bytes_per_row) {
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
}

template<typename T>
static void print_hex_value(T value, std::ostream &stream)
{
    stream << std::setfill('0') << std::setw(sizeof(value) * 2) << std::hex << std::uppercase;
    stream << static_cast<int>(value);
}

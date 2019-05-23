#ifndef MOS6502_HPP
#define MOS6502_HPP

#include <array>
#include <iostream>
#include <string>
#include <vector>

class mos6502 {
public:
    enum class flag_type { negative, overflow, brk, decimal_mode, interrupt_disable, zero, carry };

    mos6502(unsigned memory_size);
    uint8_t read_flag(flag_type type) const;
    void print_state() const;
    void print_memory(unsigned bytes_per_row = 16) const;
    void execute_instruction();
    static std::string disassemble(const std::vector<uint8_t> &buffer, unsigned &pc);

    uint8_t A() const { return A_; }
    uint8_t X() const { return X_; }
    uint8_t Y() const { return Y_; }
    uint8_t SP() const { return SP_; }
    uint16_t PC() const { return PC_; }
private:
    struct instruction {
        std::string syntax;
        int size, cycles;
    };

    uint8_t A_, X_, Y_, P_, SP_;
    uint16_t PC_;
    std::vector<uint8_t> memory_;
    static const std::string INVALID;
    static const std::vector<instruction> INSTRUCTIONS;
    static const std::array<std::string, 4> TOKENS;
};

#endif

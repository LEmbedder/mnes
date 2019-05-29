#include "mos6502.hpp"

int main()
{
    try {
        mos6502 cpu(2, std::vector<uint8_t>());
        cpu.A_ = 0x40;
        cpu.memory_[0x0] = 0x5;
        cpu.memory_[0x1] = 0x2;
        cpu.memory_[0x2] = 0xAA;
        cpu.instructions[0x5].impl();
        cpu.print_state();
        cpu.print_memory();
    } catch (std::exception &e) {
        std::cout << "ERROR: " <<  e.what() << std::endl;
        return 1;
    }

    return 0;
}

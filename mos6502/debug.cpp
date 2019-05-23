#include "mos6502.hpp"

void mos6502::print_state() const
{
    printf(" A = %02X  X = %02X  Y = %02X\n", A_, X_, Y_);
    printf("SP = %02X PC = %04X\n", SP_, PC_);

    puts("NV-BDIZC");
    for (int i = sizeof(uint8_t) * 8 - 1; i >= 0; i--) {
        if (i == 5) {
            printf("-");
            continue;
        }
        printf("%d", (P_ >> i) & 1);
    }
    printf("\n\n");
}

void mos6502::print_memory(unsigned bytes_per_row) const
{
    for (unsigned i = 0; i < memory_.size(); i += bytes_per_row) {
        printf("%04X-%04X: ", i, i + bytes_per_row - 1);
        for (unsigned j = i; j < i + bytes_per_row; j++)
            printf("%02X ", memory_[j]);
        printf("\n");
    }
}

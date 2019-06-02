#include "mos6502.hpp"

void mos6502::BRK()
{
    uint8_t high = PC() >> 8;
    uint8_t low = PC() & 0xFF;
    push_stack(low);
    push_stack(high);
    push_flags();

    P_[BREAK] = true;
    PC_ = read_vector(IRQ);
    step_cycles();
    step_pc();
}

void mos6502::NOP()
{
    step_cycles();
    step_pc();
}

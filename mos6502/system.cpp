#include "mos6502.hpp"

void mos6502::BRK()
{
    push_stack(PC());
    push_flags();

    P_[BREAK] = true;
    PC_ = irq_vector;
    step_cycles();
    step_pc();
}

void mos6502::NOP()
{
    step_cycles();
    step_pc();
}

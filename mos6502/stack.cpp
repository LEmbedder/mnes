#include "mos6502.hpp"

void mos6502::PHA()
{
    push_stack(A());
    step_cycles();
    step_pc();
}

void mos6502::PHP()
{
    push_flags();
    step_cycles();
    step_pc();
}

void mos6502::PLA()
{
    A_ = pop_stack();
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::PLP()
{
    pop_flags();
    step_cycles();
    step_pc();
}

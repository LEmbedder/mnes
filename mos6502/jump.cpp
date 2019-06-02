#include "mos6502.hpp"

void mos6502::JMP_abs()
{
    step_cycles();
    PC_ = read_vector(PC());
}

void mos6502::JMP_ind()
{
    step_cycles();
    uint16_t operand = read_vector(PC());
    PC_ = read_vector(operand);
}

void mos6502::JSR_abs()
{
    step_cycles();
    uint8_t push = memory(PC() + 2);
    push_stack(push);
    PC_ = abs();
}

void mos6502::RTI()
{
    step_cycles();
    pop_flags();
    PC_ = pop_stack();
}

void mos6502::RTS()
{
    step_cycles();
    uint8_t low = pop_stack();
    uint8_t high = pop_stack();
    PC_ = combine(high, low);
}

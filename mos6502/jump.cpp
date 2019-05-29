#include "mos6502.hpp"

void mos6502::JMP_abs()
{
    PC_ = (memory(PC() + 2) << 8) | memory(PC() + 1);
    step_cycles();
}

void mos6502::JMP_ind()
{
    uint16_t operand = (memory(PC() + 2) << 8) | memory(PC() + 1);
    uint8_t low = memory(operand);
    uint8_t high = memory(operand + 1);
    PC_ = (high << 8) | low;
    step_cycles();
}

void mos6502::JSR_abs()
{
    uint16_t push = memory(PC() + 2);
    push_stack(push);
    PC_ = abs();
    step_cycles();
}

void mos6502::RTI()
{
    pop_flags();
    PC_ = pop_stack();
    step_cycles();
}

void mos6502::RTS()
{
    uint8_t low = pop_stack();
    uint8_t high = pop_stack();
    PC_ = ((high << 8) | low) + 1;
    step_cycles();
}

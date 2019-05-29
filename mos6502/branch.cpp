#include "mos6502.hpp"

void mos6502::BCC()
{
    step_cycles();
    if (!P(CARRY))
        branch();
    else
        step_pc();
}

void mos6502::BCS()
{
    step_cycles();
    if (P(CARRY))
        branch();
    else
        step_pc();
}

void mos6502::BEQ()
{
    step_cycles();
    if (P(ZERO))
        branch();
    else
        step_pc();
}

void mos6502::BMI()
{
    step_cycles();
    if (P(NEGATIVE))
        branch();
    else
        step_pc();
}

void mos6502::BNE()
{
    step_cycles();
    if (!P(ZERO))
        branch();
    else
        step_pc();
}

void mos6502::BPL()
{
    step_cycles();
    if (!P(NEGATIVE))
        branch();
    else
        step_pc();
}

void mos6502::BVC()
{
    step_cycles();
    if (!P(OVER_FLOW))
        branch();
    else
        step_pc();
}

void mos6502::BVS()
{
    step_cycles();
    if (P(OVER_FLOW))
        branch();
    else
        step_pc();
}

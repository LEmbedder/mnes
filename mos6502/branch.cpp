#include "mos6502.hpp"

void mos6502::branch(bool condition)
{
    step_cycles();
    if (condition) {
        ++cycles_;
        uint16_t pc = PC_ + rel();
        if ((pc & 0xFF00) != (PC_ & 0xFF00))
            ++cycles_;
        PC_ = pc;
    } else {
        step_pc();
    }
}

void mos6502::BCC() { branch(!P(CARRY)); }

void mos6502::BCS() { branch(P(CARRY)); }

void mos6502::BEQ() { branch(P(ZERO)); }

void mos6502::BMI() { branch(P(NEGATIVE)); }

void mos6502::BNE() { branch(!P(ZERO)); }

void mos6502::BPL() { branch(!P(NEGATIVE)); }

void mos6502::BVC() { branch(!P(OVER_FLOW)); }

void mos6502::BVS() { branch(P(OVER_FLOW)); }

#include "mos6502.hpp"

void mos6502::CLC()
{
    P_[CARRY] = false;
    step_cycles();
    step_pc();
}

void mos6502::CLD()
{
    step_cycles();
    step_pc();
}

void mos6502::CLI()
{
    P_[INTERRUPT_DISABLE] = false;
    step_cycles();
    step_pc();
}

void mos6502::CLV()
{
    P_[OVER_FLOW] = false;
    step_cycles();
    step_pc();
}

void mos6502::CMP_imm()
{
    uint8_t operand = imm();
    uint8_t value = A() - operand;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CMP_zpg()
{
    uint16_t address = zpg();
    uint8_t value = A() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CMP_zpgX()
{
    uint16_t address = zpgX();
    uint8_t value = A() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CMP_abs()
{
    uint16_t address = abs();
    uint8_t value = A() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CMP_absX()
{
    uint16_t address = absX();
    uint8_t value = A() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CMP_absY()
{
    uint16_t address = absY();
    uint8_t value = A() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CMP_indX()
{
    uint16_t address = indX();
    uint8_t value = A() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CMP_indY()
{
    uint16_t address = indY();
    uint8_t value = A() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CPX_imm()
{
    uint8_t operand = imm();
    uint8_t value = X() - operand;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CPX_zpg()
{
    uint16_t address = zpg();
    uint8_t value = X() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CPX_abs()
{
    uint16_t address = abs();
    uint8_t value = X() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CPY_imm()
{
    uint8_t operand = imm();
    uint8_t value = Y() - operand;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CPY_zpg()
{
    uint16_t address = zpg();
    uint8_t value = Y() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CPY_abs()
{
    uint16_t address = abs();
    uint8_t value = Y() - memory(address);
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::SEC()
{
    P_[CARRY] = true;
    step_cycles();
    step_pc();
}

void mos6502::SED()
{
    step_cycles();
    step_pc();
}

void mos6502::SEI()
{
    P_[INTERRUPT_DISABLE] = true;
    step_cycles();
    step_pc();
}

#include "mos6502.hpp"

void mos6502::clear_flag(flag_type type)
{
    P_[type] = false;
    step_cycles();
    step_pc();
}

void mos6502::CLC() { clear_flag(CARRY); }

void mos6502::CLD() { clear_flag(DECIMAL); }

void mos6502::CLI() { clear_flag(INTERRUPT_DISABLE); }

void mos6502::CLV() { clear_flag(OVER_FLOW); }

void mos6502::CMP(uint8_t operand)
{
    uint8_t value = A() - operand;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CMP_imm()
{
    uint8_t operand = imm();
    CMP(operand);
}

void mos6502::CMP_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    CMP(operand);
}

void mos6502::CMP_zpgX()
{
    uint16_t address = zpgX();
    uint8_t operand = memory(address);
    CMP(operand);
}

void mos6502::CMP_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    CMP(operand);
}

void mos6502::CMP_absX()
{
    uint16_t address = absX();
    uint8_t operand = memory(address);
    CMP(operand);
}

void mos6502::CMP_absY()
{
    uint16_t address = absY();
    uint8_t operand = memory(address);
    CMP(operand);
}

void mos6502::CMP_indX()
{
    uint16_t address = indX();
    uint8_t operand = memory(address);
    CMP(operand);
}

void mos6502::CMP_indY()
{
    uint16_t address = indY();
    uint8_t operand = memory(address);
    CMP(operand);
}

void mos6502::CPX(uint8_t operand)
{
    uint8_t value = X() - operand;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CPX_imm()
{
    uint8_t operand = imm();
    CPX(operand);
}

void mos6502::CPX_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    CPX(operand);
}

void mos6502::CPX_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    CPX(operand);
}

void mos6502::CPY(uint8_t operand)
{
    uint8_t value = Y() - operand;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    P_[CARRY] = value >= 0;
    step_cycles();
    step_pc();
}

void mos6502::CPY_imm()
{
    uint8_t operand = imm();
    CPY(operand);
}

void mos6502::CPY_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    CPY(operand);
}

void mos6502::CPY_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    CPY(operand);
}

void mos6502::set_flag(flag_type type)
{
    P_[type] = true;
    step_cycles();
    step_pc();
}

void mos6502::SEC() { set_flag(CARRY); }

void mos6502::SED() { set_flag(DECIMAL); }

void mos6502::SEI() { set_flag(INTERRUPT_DISABLE); }

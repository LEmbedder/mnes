#include "mos6502.hpp"

void mos6502::ADC(uint8_t operand)
{
    uint16_t value = A() + operand + P(CARRY);
    P_[CARRY] = (value & 0xFF00) != 0;
    P_[OVER_FLOW] = !((A() ^ operand) & 0x80) && ((A() ^ value) & 0x80);
    A_ = value & 0xFF;
    step_cycles();
    step_pc();
}

void mos6502::ADC_imm()
{
    uint8_t operand = imm();
    ADC(operand);
}

void mos6502::ADC_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    ADC(operand);
}

void mos6502::ADC_zpgX()
{
    uint16_t address = zpgX();
    uint8_t operand = memory(address);
    ADC(operand);
}

void mos6502::ADC_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    ADC(operand);
}

void mos6502::ADC_absX()
{
    uint16_t address = absX();
    uint8_t operand = memory(address);
    ADC(operand);
}

void mos6502::ADC_absY()
{
    uint16_t address = absY();
    uint8_t operand = memory(address);
    ADC(operand);
}

void mos6502::ADC_indX()
{
    uint16_t address = indX();
    uint8_t operand = memory(address);
    ADC(operand);
}

void mos6502::ADC_indY()
{
    uint16_t address = indY();
    uint8_t operand = memory(address);
    ADC(operand);
}

void mos6502::DEC(uint16_t address, uint8_t value)
{
    --value;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    load_memory(address, value);
    step_cycles();
    step_pc();
}

void mos6502::DEC_zpg()
{
    uint16_t address = zpg();
    uint8_t value = memory(address);
    DEC(address, value);
}

void mos6502::DEC_zpgX()
{
    uint16_t address = zpgX();
    uint8_t value = memory(address);
    DEC(address, value);
}

void mos6502::DEC_abs()
{
    uint16_t address = abs();
    uint8_t value = memory(address);
    DEC(address, value);
}

void mos6502::DEC_absX()
{
    uint16_t address = absX();
    uint8_t value = memory(address);
    DEC(address, value);
}

void mos6502::DEX()
{
    --X_;
    P_[NEGATIVE] = negative(X());
    P_[ZERO] = zero(X());
    step_cycles();
    step_pc();
}

void mos6502::DEY()
{
    --Y_;
    P_[NEGATIVE] = negative(Y());
    P_[ZERO] = zero(Y());
    step_cycles();
    step_pc();
}

void mos6502::INC(uint16_t address, uint8_t value)
{
    ++value;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    load_memory(address, value);
    step_cycles();
    step_pc();
}

void mos6502::INC_zpg()
{
    uint16_t address = zpg();
    uint8_t value = memory(address);
    INC(address, value);
}

void mos6502::INC_zpgX()
{
    uint16_t address = zpgX();
    uint8_t value = memory(address);
    INC(address, value);
}

void mos6502::INC_abs()
{
    uint16_t address = abs();
    uint8_t value = memory(address);
    INC(address, value);;
}

void mos6502::INC_absX()
{
    uint16_t address = absX();
    uint8_t value = memory(address);
    INC(address, value);
}

void mos6502::INX()
{
    ++X_;
    P_[NEGATIVE] = negative(X());
    P_[ZERO] = zero(X());
    step_cycles();
    step_pc();
}

void mos6502::INY()
{
    ++Y_;
    P_[NEGATIVE] = negative(Y());
    P_[ZERO] = zero(Y());
    step_cycles();
    step_pc();
}

void mos6502::SBC(uint8_t operand)
{
    uint16_t value = A() - operand - (1 - P(CARRY));
    P_[CARRY] = (value & 0xFF00) != 0;
    P_[OVER_FLOW] = !((A() ^ operand) & 0x80) && ((A() ^ value) & 0x80);
    A_ = value & 0xFF;
    step_cycles();
    step_pc();
}

void mos6502::SBC_imm()
{
    uint8_t operand = imm();
    SBC(operand);
}

void mos6502::SBC_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    SBC(operand);
}

void mos6502::SBC_zpgX()
{
    uint16_t address = zpgX();
    uint8_t operand = memory(address);
    SBC(operand);
}

void mos6502::SBC_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    SBC(operand);
}

void mos6502::SBC_absX()
{
    uint16_t address = absX();
    uint8_t operand = memory(address);
    SBC(operand);
}

void mos6502::SBC_absY()
{
    uint16_t address = absY();
    uint8_t operand = memory(address);
    SBC(operand);
}

void mos6502::SBC_indX()
{
    uint16_t address = indX();
    uint8_t operand = memory(address);
    SBC(operand);
}

void mos6502::SBC_indY()
{
    uint16_t address = indY();
    uint8_t operand = memory(address);
    SBC(operand);
}

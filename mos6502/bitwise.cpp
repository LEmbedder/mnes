#include "mos6502.hpp"

void mos6502::AND(uint8_t operand)
{
    A_ &= operand;
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::AND_imm()
{
    uint8_t operand = imm();
    AND(operand);
}

void mos6502::AND_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    AND(operand);
}

void mos6502::AND_zpgX()
{
    uint16_t address = zpgX();
    uint8_t operand = memory(address);
    AND(operand);
}

void mos6502::AND_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    AND(operand);
}

void mos6502::AND_absX()
{
    uint16_t address = absX();
    uint8_t operand = memory(address);
    AND(operand);
}

void mos6502::AND_absY()
{
    uint16_t address = absY();
    uint8_t operand = memory(address);
    AND(operand);
}

void mos6502::AND_indX()
{
    uint16_t address = indX();
    uint8_t operand = memory(address);
    AND(operand);
}

void mos6502::AND_indY()
{
    uint16_t address = indY();
    uint8_t operand = memory(address);
    AND(operand);
}

void mos6502::ASL(uint16_t address, uint8_t value)
{
    P_[CARRY] = value >> 7;
    value <<= 1;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    load_memory(address, value);
    step_cycles();
    step_pc();
}

void mos6502::ASL_A()
{
    P_[CARRY] = A() >> 7;
    A_ <<= 1;
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::ASL_zpg()
{
    uint16_t address = zpg();
    uint8_t value = memory(address);
    ASL(address, value);
}

void mos6502::ASL_zpgX()
{
    uint16_t address = zpgX();
    uint8_t value = memory(address);
    ASL(address, value);
}

void mos6502::ASL_abs()
{
    uint16_t address = abs();
    uint8_t value = memory(address);
    ASL(address, value);
}

void mos6502::ASL_absX()
{
    uint16_t address = absX();
    uint8_t value = memory(address);
    ASL(address, value);
}

void mos6502::BIT(uint8_t value)
{
    value &= A();
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = negative(value);
    P_[OVER_FLOW] = (value >> 6) & 1;
    step_cycles();
    step_pc();
}

void mos6502::BIT_zpg()
{
    uint16_t address = zpg();
    uint8_t value = memory(address);
    BIT(value);
}

void mos6502::BIT_abs()
{
    uint16_t address = abs();
    uint8_t value = memory(address) & A();
    BIT(value);
}

void mos6502::EOR(uint8_t operand)
{
    A_ ^= operand;
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::EOR_imm()
{
    uint8_t operand = imm();
    EOR(operand);
}

void mos6502::EOR_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    EOR(operand);
}

void mos6502::EOR_zpgX()
{
    uint16_t address = zpgX();
    uint8_t operand = memory(address);
    EOR(operand);
}

void mos6502::EOR_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    EOR(operand);
}

void mos6502::EOR_absX()
{
    uint16_t address = absX();
    uint8_t operand = memory(address);
    EOR(operand);
}

void mos6502::EOR_absY()
{
    uint16_t address = absY();
    uint8_t operand = memory(address);
    EOR(operand);
}

void mos6502::EOR_indX()
{
    uint16_t address = indX();
    uint8_t operand = memory(address);
    EOR(operand);
}

void mos6502::EOR_indY()
{
    uint16_t address = indY();
    uint8_t operand = memory(address);
    EOR(operand);
}

void mos6502::LSR(uint16_t address, uint8_t value)
{
    P_[CARRY] = value >> 7;
    value >>= 1;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    load_memory(address, value);
    step_cycles();
    step_pc();
}

void mos6502::LSR_A()
{
    P_[CARRY] = A_ >> 7;
    A_ >>= 1;
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::LSR_zpg()
{
    uint16_t address = zpg();
    uint8_t value = memory(address);
    LSR(address, value);
}

void mos6502::LSR_zpgX()
{
    uint16_t address = zpgX();
    uint8_t value = memory(address);
    LSR(address, value);
}

void mos6502::LSR_abs()
{
    uint16_t address = abs();
    uint8_t value = memory(address);
    LSR(address, value);
}

void mos6502::LSR_absX()
{
    uint16_t address = absX();
    uint8_t value = memory(address);
    LSR(address, value);
}

void mos6502::ORA(uint8_t operand)
{
    A_ |= operand;
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::ORA_imm()
{
    uint8_t operand = imm();
    ORA(operand);
}

void mos6502::ORA_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    ORA(operand);
}

void mos6502::ORA_zpgX()
{
    uint16_t address = zpgX();
    uint8_t operand = memory(address);
    ORA(operand);
}

void mos6502::ORA_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    ORA(operand);
}

void mos6502::ORA_absX()
{
    uint16_t address = absX();
    uint8_t operand = memory(address);
    ORA(operand);
}

void mos6502::ORA_absY()
{
    uint16_t address = absY();
    uint8_t operand = memory(address);
    ORA(operand);
}

void mos6502::ORA_indX()
{
    uint16_t address = indX();
    uint8_t operand = memory(address);
    ORA(operand);
}

void mos6502::ORA_indY()
{
    uint16_t address = indY();
    uint8_t operand = memory(address);
    ORA(operand);
}

void mos6502::ROL(uint16_t address, uint8_t value)
{
    int carry = P(CARRY);
    P_[CARRY] = value >> 7;
    value <<= 1;
    value = (value & 0xFE) | carry;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    load_memory(address, value);
    step_cycles();
    step_pc();
}

void mos6502::ROL_A()
{
    int carry = P(CARRY);
    P_[CARRY] = A() >> 7;
    A_ <<= 1;
    A_ = (A_ & 0xFE) | carry;
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::ROL_zpg()
{
    uint16_t address = zpg();
    uint8_t value = memory(address);
    ROL(address, value);
}

void mos6502::ROL_zpgX()
{
    uint16_t address = zpg();
    uint8_t value = memory(address);
    ROL(address, value);
}

void mos6502::ROL_abs()
{
    uint16_t address = abs();
    uint8_t value = memory(address);
    ROL(address, value);
}

void mos6502::ROL_absX()
{
    uint16_t address = absX();
    uint8_t value = memory(address);
    ROL(address, value);
}

void mos6502::ROR(uint16_t address, uint8_t value)
{
    int carry = P(CARRY);
    P_[CARRY] = value & 1;
    value >>= 1;
    value = (value & 0x7F) | carry;
    P_[NEGATIVE] = negative(value);
    P_[ZERO] = zero(value);
    step_cycles();
    step_pc();
}

void mos6502::ROR_A()
{
    int carry = P(CARRY);
    P_[CARRY] = A() & 1;
    A_ >>= 1;
    A_ = (A_ & 0x7F) | carry;
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::ROR_zpg()
{
    uint16_t address = zpg();
    uint8_t value = memory(address);
    ROR(address, value);
}

void mos6502::ROR_zpgX()
{
    uint16_t address = zpgX();
    uint8_t value = memory(address);
    ROR(address, value);
}

void mos6502::ROR_abs()
{
    uint16_t address = abs();
    uint8_t value = memory(address);
    ROR(address, value);
}

void mos6502::ROR_absX()
{
    uint16_t address = absX();
    uint8_t value = memory(address);
    ROR(address, value);
}

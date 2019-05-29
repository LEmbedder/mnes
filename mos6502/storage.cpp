#include "mos6502.hpp"

void mos6502::LDA_imm()
{
    uint8_t operand = imm();
    A_ = operand;
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::LDA_zpg()
{
    uint16_t address = zpg();
    A_ = memory(address);
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::LDA_zpgX()
{
    uint16_t address = zpgX();
    A_ = memory(address);
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::LDA_abs()
{
    uint16_t address = abs();
    A_ = memory(address);
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::LDA_absX()
{
    uint16_t address = absX();
    A_ = memory(address);
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
    
}

void mos6502::LDA_absY()
{
    uint16_t address = absY();
    A_ = memory(address);
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::LDA_indX()
{
    uint16_t address = indX();
    A_ = memory(address);
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::LDA_indY()
{
    uint16_t address = indY();
    A_ = memory(address);
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::LDX_imm()
{
    uint8_t operand = imm();
    X_ = operand;
    P_[NEGATIVE] = negative(X());
    P_[ZERO] = zero(X());
    step_cycles();
    step_pc();
}

void mos6502::LDX_zpg()
{
    uint16_t address = zpg();
    X_ = memory(address);
    P_[NEGATIVE] = negative(X());
    P_[ZERO] = zero(X());
    step_cycles();
    step_pc();
}

void mos6502::LDX_zpgY()
{
    uint16_t address = zpgY();
    X_ = memory(address);
    P_[NEGATIVE] = negative(X());
    P_[ZERO] = zero(X());
    step_cycles();
    step_pc();
}

void mos6502::LDX_abs()
{
    uint16_t address = abs();
    X_ = memory(address);
    P_[NEGATIVE] = negative(X());
    P_[ZERO] = zero(X());
    step_cycles();
    step_pc();
}

void mos6502::LDX_absY()
{
    uint16_t address = absY();
    X_ = memory(address);
    P_[NEGATIVE] = negative(X());
    P_[ZERO] = zero(X());
    step_cycles();
    step_pc();
}

void mos6502::LDY_imm()
{
    uint8_t operand = imm();
    Y_ = operand;
    P_[NEGATIVE] = negative(Y());
    P_[ZERO] = zero(Y());
    step_cycles();
    step_pc();
}

void mos6502::LDY_zpg()
{
    uint16_t address = zpg();
    Y_ = memory(address);
    P_[NEGATIVE] = negative(Y());
    P_[ZERO] = zero(Y());
    step_cycles();
    step_pc();
}

void mos6502::LDY_zpgX()
{
    uint16_t address = zpgX();
    Y_ = memory(address);
    P_[NEGATIVE] = negative(Y());
    P_[ZERO] = zero(Y());
    step_cycles();
    step_pc();
}

void mos6502::LDY_abs()
{
    uint16_t address = abs();
    Y_ = memory(address);
    P_[NEGATIVE] = negative(Y());
    P_[ZERO] = zero(Y());
    step_cycles();
    step_pc();
}

void mos6502::LDY_absX()
{
    uint16_t address = absX();
    Y_ = memory(address);
    P_[NEGATIVE] = negative(Y());
    P_[ZERO] = zero(Y());
    step_cycles();
    step_pc();
}

void mos6502::STA_abs()
{
    uint16_t address = abs();
    load_memory(address, A());
    step_cycles();
    step_pc();
}

void mos6502::STA_absX()
{
    uint16_t address = absX();
    load_memory(address, A());
    step_cycles();
    step_pc();
}

void mos6502::STA_absY()
{
    uint16_t address = absY();
    load_memory(address, A());
    step_cycles();
    step_pc();
}

void mos6502::STA_zpg()
{
    uint16_t address = zpg();
    load_memory(address, A());
    step_cycles();
    step_pc();
}

void mos6502::STA_zpgX()
{
    uint16_t address = zpgX();
    load_memory(address, A());
    step_cycles();
    step_pc();
}

void mos6502::STA_indX()
{
    uint16_t address = indX();
    load_memory(address, A());
    step_cycles();
    step_pc();
}

void mos6502::STA_indY()
{
    uint16_t address = indY();
    load_memory(address, A());
    step_cycles();
    step_pc();
}

void mos6502::STX_abs()
{
    uint16_t address = abs();
    load_memory(address, X());
    step_cycles();
    step_pc();
}

void mos6502::STX_zpg()
{
    uint16_t address = zpg();
    load_memory(address, X());
    step_cycles();
    step_pc();
}

void mos6502::STX_zpgY()
{
    uint16_t address = zpgY();
    load_memory(address, X());
    step_cycles();
    step_pc();
}

void mos6502::STY_zpg()
{
    uint16_t address = zpg();
    load_memory(address, Y());
    step_cycles();
    step_pc();
}

void mos6502::STY_zpgX()
{
    uint16_t address = zpgX();
    load_memory(address, Y());
    step_cycles();
    step_pc();
    step_cycles();
}

void mos6502::STY_abs()
{
    uint16_t address = abs();
    load_memory(address, Y());
    step_cycles();
    step_pc();
}

void mos6502::TAX()
{
    X_ = A();
    P_[NEGATIVE] = negative(X());
    P_[ZERO] = zero(X());
    step_cycles();
    step_pc();
}

void mos6502::TAY()
{
    Y_ = A();
    P_[NEGATIVE] = negative(Y());
    P_[ZERO] = zero(Y());
    step_cycles();
    step_pc();
}

void mos6502::TSX()
{
    X_ = S() & 0xFF;
    P_[NEGATIVE] = negative(X());
    P_[ZERO] = zero(X());
    step_cycles();
    step_pc();
}

void mos6502::TXA()
{
    A_ = X();
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

void mos6502::TXS()
{
    S_ = X();
    step_cycles();
    step_pc();
}

void mos6502::TYA()
{
    A_ = Y();
    P_[NEGATIVE] = negative(A());
    P_[ZERO] = zero(A());
    step_cycles();
    step_pc();
}

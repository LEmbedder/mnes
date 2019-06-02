#include "mos6502.hpp"

void mos6502::load(uint8_t &reg, uint8_t operand)
{
    reg = operand;
    P_[NEGATIVE] = negative(reg);
    P_[ZERO] = zero(reg);
    step_cycles();
    step_pc();
}

void mos6502::LDA_imm()
{
    uint8_t operand = imm();
    load(A_, operand);
}

void mos6502::LDA_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    load(A_, operand);
}

void mos6502::LDA_zpgX()
{
    uint16_t address = zpgX();
    uint8_t operand = memory(address);
    load(A_, operand);
}

void mos6502::LDA_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    load(A_, operand);
}

void mos6502::LDA_absX()
{
    uint16_t address = absX();
    uint8_t operand = memory(address);
    load(A_, operand);
    
}

void mos6502::LDA_absY()
{
    uint16_t address = absY();
    uint8_t operand = memory(address);
    load(A_, operand);
}

void mos6502::LDA_indX()
{
    uint16_t address = indX();
    uint8_t operand = memory(address);
    load(A_, operand);
}

void mos6502::LDA_indY()
{
    uint16_t address = indY();
    uint8_t operand = memory(address);
    load(A_, operand);
}

void mos6502::LDX_imm()
{
    uint8_t operand = imm();
    load(X_, operand);
}

void mos6502::LDX_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    load(X_, operand);
}

void mos6502::LDX_zpgY()
{
    uint16_t address = zpgY();
    uint8_t operand = memory(address);
    load(X_, operand);
}

void mos6502::LDX_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    load(X_, operand);
}

void mos6502::LDX_absY()
{
    uint16_t address = absY();
    uint8_t operand = memory(address);
    load(X_, operand);
}

void mos6502::LDY_imm()
{
    uint8_t operand = imm();
    load(Y_, operand);
}

void mos6502::LDY_zpg()
{
    uint16_t address = zpg();
    uint8_t operand = memory(address);
    load(Y_, operand);
}

void mos6502::LDY_zpgX()
{
    uint16_t address = zpgX();
    uint8_t operand = memory(address);
    load(Y_, operand);
}

void mos6502::LDY_abs()
{
    uint16_t address = abs();
    uint8_t operand = memory(address);
    load(Y_, operand);
}

void mos6502::LDY_absX()
{
    uint16_t address = absX();
    uint8_t operand = memory(address);
    load(Y_, operand);
}

void mos6502::store(uint16_t address, uint8_t reg)
{
    load_memory(address, reg);
    step_cycles();
    step_pc();
}

void mos6502::STA_abs()
{
    uint16_t address = abs();
    store(address, A());
}

void mos6502::STA_absX()
{
    uint16_t address = absX();
    store(address, A());
}

void mos6502::STA_absY()
{
    uint16_t address = absY();
    store(address, A());
}

void mos6502::STA_zpg()
{
    uint16_t address = zpg();
    store(address, A());
}

void mos6502::STA_zpgX()
{
    uint16_t address = zpgX();
    store(address, A());
}

void mos6502::STA_indX()
{
    uint16_t address = indX();
    store(address, A());
}

void mos6502::STA_indY()
{
    uint16_t address = indY();
    store(address, A());
}

void mos6502::STX_abs()
{
    uint16_t address = abs();
    store(address, X());
}

void mos6502::STX_zpg()
{
    uint16_t address = zpg();
    store(address, X());
}

void mos6502::STX_zpgY()
{
    uint16_t address = zpgY();
    store(address, X());
}

void mos6502::STY_zpg()
{
    uint16_t address = zpg();
    store(address, Y());
}

void mos6502::STY_zpgX()
{
    uint16_t address = zpgX();
    store(address, Y());
}

void mos6502::STY_abs()
{
    uint16_t address = abs();
    store(address, Y());
}

void mos6502::transfer(uint8_t source, uint8_t &destination, bool flags)
{
    destination = source;
    if (flags) {
        P_[NEGATIVE] = negative(destination);
        P_[ZERO] = zero(destination);
    }
    step_cycles();
    step_pc();
}

void mos6502::TAX() { transfer(A(), X_); }

void mos6502::TAY() { transfer(A(), Y_); }

void mos6502::TSX() { transfer(S() & 0xFF, X_); }

void mos6502::TXA() { transfer(X(), A_); }

void mos6502::TXS() { transfer(X(), S_, false); }

void mos6502::TYA() { transfer(Y(), A_); }

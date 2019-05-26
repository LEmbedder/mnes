#ifndef MOS6502_HPP
#define MOS6502_HPP

#include <array>
#include <bitset>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class mos6502 {
public:
    enum flag_type {
        NEGATIVE = 0,
        OVER_FLOW = 1,
        BREAK = 3,
        DECIMAL_MODE = 4,
        INTERRUPT_DISABLE = 5,
        ZERO = 6,
        CARRY = 7
    };

    mos6502(unsigned memory_size);
    void print_state(std::ostream &stream = std::cout) const;
    void print_memory(unsigned bytes_per_row = 16, std::ostream &stream = std::cout) const;
    std::string disassemble(const std::vector<uint8_t> &buffer, unsigned &pc);

    uint8_t A() const { return A_; }
    uint8_t X() const { return X_; }
    uint8_t Y() const { return Y_; }
    uint8_t SP() const { return SP_; }
    uint16_t PC() const { return PC_; }
    bool P(flag_type type) const { return P_[type]; }
private:
    struct instruction {
        std::string syntax;
        int size = 0, cycles = 0;
        std::function<void()> impl;
    };

    uint8_t A_, X_, Y_, SP_;
    uint16_t PC_;
    unsigned cycles_;
    std::bitset<8> P_;
    std::vector<uint8_t> memory_;
    std::vector<instruction> instructions;
    static const std::array<std::string, 4> TOKENS;

    void load_instructions();
    void invalid_opcode();
    void BRK();
    void ORA_indX();
    void ORA_zpg();
    void ASL_zpg();
    void PHP();
    void ORA_imm();
    void ASL_A();
    void ORA_abs();
    void ASL_abs();
    void BPL();
    void ORA_indY();
    void ORA_zpgX();
    void ASL_zpgX();
    void CLC();
    void ORA_absY();
    void ORA_absX();
    void ASL_absX();
    void JSR_abs();
    void AND_indX();
    void BIT_zpg();
    void AND_zpg();
    void ROL_zpg();
    void PLP();
    void AND_imm();
    void ROL_A();
    void BIT_abs();
    void AND_abs();
    void ROL_abs();
    void BMI();
    void AND_indY();
    void AND_zpgX();
    void ROL_zpgX();
    void SEC();
    void AND_absY();
    void AND_absX();
    void ROL_absX();
    void RTI();
    void EOR_indX();
    void EOR_zpg();
    void LSR_zpg();
    void PHA();
    void EOR_imm();
    void LSR_A();
    void JMP_abs();
    void EOR_abs();
    void LSR_abs();
    void BVC();
    void EOR_indY();
    void EOR_zpgX();
    void LSR_zpgX();
    void CLI();
    void EOR_absY();
    void EOR_absX();
    void LSR_absX();
    void RTS();
    void ADC_indX();
    void ADC_zpg();
    void ROR_zpg();
    void PLA();
    void ADC_imm();
    void ROR_A();
    void JMP_ind();
    void ADC_abs();
    void ROR_abs();
    void BVS();
    void ADC_indY();
    void ADC_zpgX();
    void ROR_zpgX();
    void SEI();
    void ADC_absY();
    void ADC_absX();
    void ROR_absX();
    void STA_indX();
    void STY_zpg();
    void STA_zpg();
    void STX_zpg();
    void DEY();
    void TXA();
    void STY_abs();
    void STA_abs();
    void STX_abs();
    void BCC();
    void STA_indY();
    void STY_zpgX();
    void STA_zpgX();
    void STX_zpgY();
    void TYA();
    void STA_absY();
    void TXS();
    void STA_absX();
    void LDY_imm();
    void LDA_indX();
    void LDX_imm();
    void LDY_zpg();
    void LDA_zpg();
    void LDX_zpg();
    void TAY();
    void LDA_imm();
    void TAX();
    void LDY_abs();
    void LDA_abs();
    void LDX_abs();
    void BCS();
    void LDA_indY();
    void LDY_zpgX();
    void LDA_zpgX();
    void LDX_zpgY();
    void CLV();
    void LDA_absY();
    void TSX();
    void LDY_absX();
    void LDA_absX();
    void LDX_absY();
    void CPY_imm();
    void CMP_indX();
    void CPY_zpg();
    void CMP_zpg();
    void DEC_zpg();
    void INY();
    void CMP_imm();
    void DEX();
    void CPY_abs();
    void CMP_abs();
    void DEC_abs();
    void BNE();
    void CMP_indY();
    void CMP_zpgX();
    void DEC_zpgX();
    void CLD();
    void CMP_absY();
    void CMP_absX();
    void DEC_absX();
    void CPX_imm();
    void SBC_indX();
    void CPX_zpg();
    void SBC_zpg();
    void INC_zpg();
    void INX();
    void SBC_imm();
    void NOP();
    void CPX_abs();
    void SBC_abs();
    void INC_abs();
    void BEQ();
    void SBC_indY();
    void SBC_zpgX();
    void INC_zpgX();
    void SED();
    void SBC_absY();
    void SBC_absX();
    void INC_absX();
};

#endif

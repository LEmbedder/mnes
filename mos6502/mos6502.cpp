#include <iostream>
#include <sstream>
#include "mos6502.hpp"

const std::array<std::string, 4> mos6502::TOKENS = { "abs", "imm", "ind", "zpg" };

mos6502::mos6502(unsigned memory_size)
{
    A_ = X_ = Y_ = SP_ = 0;
    PC_ = 0;
    cycles_ = 0;
    memory_.resize(memory_size);
    load_instructions();
}

std::string mos6502::disassemble(const std::vector<uint8_t> &buffer, unsigned &pc)
{
    instruction instr = instructions[buffer[pc]];

    int operand = 0;
    for (int i = instr.size - 1; i > 0; i--)
        operand |= buffer[pc + static_cast<uint64_t>(i)] << 8;
    
    std::ostringstream oss;
    oss << std::hex << operand;

    size_t index = 0;
    std::string syntax = instr.syntax;
    for (auto token : TOKENS) {
        index = syntax.find(token);
        if (index != std::string::npos) {
            syntax.replace(index, token.length(), oss.str());
            break;
        }
    }

    pc += instr.size;
    return syntax;
}

void mos6502::invalid_opcode() { throw std::runtime_error("Invalid Opcode"); }

void mos6502::BRK()
{

}

void mos6502::ORA_indX()
{

}

void mos6502::ORA_zpg()
{

}

void mos6502::ASL_zpg()
{

}

void mos6502::PHP()
{

}

void mos6502::ORA_imm()
{

}

void mos6502::ASL_A()
{

}

void mos6502::ORA_abs()
{

}

void mos6502::ASL_abs()
{

}

void mos6502::BPL()
{

}

void mos6502::ORA_indY()
{

}

void mos6502::ORA_zpgX()
{

}

void mos6502::ASL_zpgX()
{

}

void mos6502::CLC()
{

}

void mos6502::ORA_absY()
{

}

void mos6502::ORA_absX()
{

}

void mos6502::ASL_absX()
{

}

void mos6502::JSR_abs()
{

}

void mos6502::AND_indX()
{

}

void mos6502::BIT_zpg()
{

}

void mos6502::AND_zpg()
{

}

void mos6502::ROL_zpg()
{

}

void mos6502::PLP()
{

}

void mos6502::AND_imm()
{

}

void mos6502::ROL_A()
{

}

void mos6502::BIT_abs()
{

}

void mos6502::AND_abs()
{

}

void mos6502::ROL_abs()
{

}

void mos6502::BMI()
{

}

void mos6502::AND_indY()
{

}

void mos6502::AND_zpgX()
{

}

void mos6502::ROL_zpgX()
{

}

void mos6502::SEC()
{

}

void mos6502::AND_absY()
{

}

void mos6502::AND_absX()
{

}

void mos6502::ROL_absX()
{

}

void mos6502::RTI()
{

}

void mos6502::EOR_indX()
{

}

void mos6502::EOR_zpg()
{

}

void mos6502::LSR_zpg()
{

}

void mos6502::PHA()
{

}

void mos6502::EOR_imm()
{

}

void mos6502::LSR_A()
{

}

void mos6502::JMP_abs()
{

}

void mos6502::EOR_abs()
{

}

void mos6502::LSR_abs()
{

}

void mos6502::BVC()
{

}

void mos6502::EOR_indY()
{

}

void mos6502::EOR_zpgX()
{

}

void mos6502::LSR_zpgX()
{

}

void mos6502::CLI()
{

}

void mos6502::EOR_absY()
{

}

void mos6502::EOR_absX()
{

}

void mos6502::LSR_absX()
{

}

void mos6502::RTS()
{

}

void mos6502::ADC_indX()
{

}

void mos6502::ADC_zpg()
{

}

void mos6502::ROR_zpg()
{

}

void mos6502::PLA()
{

}

void mos6502::ADC_imm()
{

}

void mos6502::ROR_A()
{

}

void mos6502::JMP_ind()
{

}

void mos6502::ADC_abs()
{

}

void mos6502::ROR_abs()
{

}

void mos6502::BVS()
{

}

void mos6502::ADC_indY()
{

}

void mos6502::ADC_zpgX()
{

}

void mos6502::ROR_zpgX()
{

}

void mos6502::SEI()
{

}

void mos6502::ADC_absY()
{

}

void mos6502::ADC_absX()
{

}

void mos6502::ROR_absX()
{

}

void mos6502::STA_indX()
{

}

void mos6502::STY_zpg()
{

}

void mos6502::STA_zpg()
{

}

void mos6502::STX_zpg()
{

}

void mos6502::DEY()
{

}

void mos6502::TXA()
{

}

void mos6502::STY_abs()
{

}

void mos6502::STA_abs()
{

}

void mos6502::STX_abs()
{

}

void mos6502::BCC()
{

}

void mos6502::STA_indY()
{

}

void mos6502::STY_zpgX()
{

}

void mos6502::STA_zpgX()
{

}

void mos6502::STX_zpgY()
{

}

void mos6502::TYA()
{

}

void mos6502::STA_absY()
{

}

void mos6502::TXS()
{

}

void mos6502::STA_absX()
{

}

void mos6502::LDY_imm()
{

}

void mos6502::LDA_indX()
{

}

void mos6502::LDX_imm()
{

}

void mos6502::LDY_zpg()
{

}

void mos6502::LDA_zpg()
{

}

void mos6502::LDX_zpg()
{

}

void mos6502::TAY()
{

}

void mos6502::LDA_imm()
{

}

void mos6502::TAX()
{

}

void mos6502::LDY_abs()
{

}

void mos6502::LDA_abs()
{

}

void mos6502::LDX_abs()
{

}

void mos6502::BCS()
{

}

void mos6502::LDA_indY()
{

}

void mos6502::LDY_zpgX()
{

}

void mos6502::LDA_zpgX()
{

}

void mos6502::LDX_zpgY()
{

}

void mos6502::CLV() 
{

}

void mos6502::LDA_absY()
{

}

void mos6502::TSX()
{

}

void mos6502::LDY_absX()
{

}

void mos6502::LDA_absX()
{

}

void mos6502::LDX_absY()
{

}

void mos6502::CPY_imm()
{

}

void mos6502::CMP_indX()
{

}

void mos6502::CPY_zpg()
{

}

void mos6502::CMP_zpg()
{

}

void mos6502::DEC_zpg()
{

}

void mos6502::INY()
{

}

void mos6502::CMP_imm()
{

}

void mos6502::DEX()
{

}

void mos6502::CPY_abs()
{

}

void mos6502::CMP_abs()
{

}

void mos6502::DEC_abs()
{

}

void mos6502::BNE()
{

}

void mos6502::CMP_indY()
{

}

void mos6502::CMP_zpgX()
{

}

void mos6502::DEC_zpgX()
{

}

void mos6502::CLD()
{

}

void mos6502::CMP_absY()
{

}

void mos6502::CMP_absX()
{

}

void mos6502::DEC_absX()
{

}

void mos6502::CPX_imm()
{

}

void mos6502::SBC_indX()
{

}

void mos6502::CPX_zpg()
{

}

void mos6502::SBC_zpg()
{

}

void mos6502::INC_zpg()
{

}

void mos6502::INX()
{

}

void mos6502::SBC_imm()
{

}

void mos6502::NOP()
{

}

void mos6502::CPX_abs()
{

}

void mos6502::SBC_abs()
{

}

void mos6502::INC_abs()
{

}

void mos6502::BEQ()
{

}

void mos6502::SBC_indY()
{

}

void mos6502::SBC_zpgX()
{

}

void mos6502::INC_zpgX()
{

}

void mos6502::SED()
{

}

void mos6502::SBC_absY()
{

}

void mos6502::SBC_absX()
{

}

void mos6502::INC_absX()
{

}

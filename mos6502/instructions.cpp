#include "mos6502.hpp"

const std::vector<mos6502::instruction> mos6502::INSTRUCTIONS = {
    { "BRK", 1, 7 },          // 0x00
    { "ORA ($ind,X)", 2, 6 }, // 0x01
    { INVALID, -1, -1 },      // 0x02
    { INVALID, -1, -1 },      // 0x03
    { INVALID, -1, -1 },      // 0x04
    { "ORA $zpg", 2, 3 },     // 0x05
    { "ASL $zpg", 2, 5 },     // 0x06
    { INVALID, -1, -1 },      // 0x07
    { "PHP", 1, 3 },          // 0x08
    { "ORA #$imm", 2, 2 },    // 0x09
    { "ASL A", 1, 2 },        // 0x0A
    { INVALID, -1, -1 },      // 0x0B
    { INVALID, -1, -1 },      // 0x0C
    { "ORA $abs", 3, 4 },     // 0x0D
    { "ASL $abs", 3, 6 },     // 0x0E
    { INVALID, -1, -1 },      // 0x0F

    { "BPL", 2, 2 },          // 0x10
    { "ORA ($ind),Y", 2, 5 }, // 0x11
    { INVALID, -1, -1 },      // 0x12
    { INVALID, -1, -1 },      // 0x13
    { INVALID, -1, -1 },      // 0x14
    { "ORA $zpg,X", 2, 4 },   // 0x15
    { "ASL $zpg,X", 2, 6 },   // 0x16
    { INVALID, -1, -1 },      // 0x17
    { "CLC", 1, 2 },          // 0x18
    { "ORA $abs,Y", 3, 4 },   // 0x19
    { INVALID, -1, -1 },      // 0x1A
    { INVALID, -1, -1 },      // 0x1B
    { INVALID, -1, -1 },      // 0x1C
    { "ORA $abs,X", 3, 4 },   // 0x1D
    { "ASL $abs,X", 3, 7 },   // 0x1E
    { INVALID, -1, -1 },      // 0x1F

    { "JSR $abs", 3, 6 },     // 0x20
    { "AND ($ind,X)", 2, 6 }, // 0x21
    { INVALID, -1, -1 },      // 0x22
    { INVALID, -1, -1 },      // 0x23
    { "BIT $zpg", 2, 3 },     // 0x24
    { "AND $zpg", 2, 3 },     // 0x25
    { "ROL $zpg", 2, 5 },     // 0x26
    { INVALID, -1, -1 },      // 0x27
    { "PLP", 1, 4 },          // 0x28
    { "AND #$imm", 2, 2 },    // 0x29
    { "ROL A", 1, 2 },        // 0x2A
    { INVALID, -1, -1 },      // 0x2B
    { "BIT $abs", 3, 4 },     // 0x2C
    { "AND $abs", 3, 4 },     // 0x2D
    { "ROL $abs", 3, 6 },     // 0x2E
    { INVALID, -1, -1 },      // 0x2F

    { "BMI", 2, 2 },          // 0x30
    { "AND ($ind),Y", 2, 5 }, // 0x31
    { INVALID, -1, -1 },      // 0x32
    { INVALID, -1, -1 },      // 0x33
    { INVALID, -1, -1 },      // 0x34
    { "AND $zpg,X", 2, 4 },   // 0x35
    { "ROL $zpg,X", 2, 6 },   // 0x36
    { INVALID, -1, -1 },      // 0x37
    { "SEC", 1, 2 },          // 0x38
    { "AND $abs,Y", 3, 4 },   // 0x39
    { INVALID, -1, -1 },      // 0x3A
    { INVALID, -1, -1 },      // 0x3B
    { INVALID, -1, -1 },      // 0x3C
    { "AND $abs,X", 3, 4 },   // 0x3D
    { "ROL $abs,X", 3, 7 },   // 0x3E
    { INVALID, -1, -1 },      // 0x3F

    { "RTI", 1, 6 },          // 0x40
    { "EOR ($ind,X)", 2, 6 }, // 0x41
    { INVALID, -1, -1 },      // 0x42
    { INVALID, -1, -1 },      // 0x43
    { INVALID, -1, -1 },      // 0x44
    { "EOR $zpg", 2, 3 },     // 0x45
    { "LSR $zpg", 2, 5 },     // 0x46
    { INVALID, -1, -1 },      // 0x47
    { "PHA", 1, 3 },          // 0x48
    { "EOR #$imm", 2, 2 },    // 0x49
    { "LSR A", 1, 2 },        // 0x4A
    { INVALID, -1, -1 },      // 0x4B
    { "JMP $abs", 3, 3 },     // 0x4C
    { "EOR $abs", 3, 4 },     // 0x4D
    { "LSR $abs", 3, 6 },     // 0x4E
    { INVALID, -1, -1 },      // 0x4F

    { "BVC", 2, 2 },          // 0x50
    { "EOR ($ind),Y", 2, 5 }, // 0x51
    { INVALID, -1, -1 },      // 0x52
    { INVALID, -1, -1 },      // 0x53
    { INVALID, -1, -1 },      // 0x54
    { "EOR $zpg,X", 2, 4 },   // 0x55
    { "LSR $zpg,X", 2, 6 },   // 0x56
    { INVALID, -1, -1 },      // 0x57
    { "CLI", 1, 2 },          // 0x58
    { "EOR $abs,Y", 3, 4 },   // 0x59
    { INVALID, -1, -1 },      // 0x5A
    { INVALID, -1, -1 },      // 0x5B
    { INVALID, -1, -1 },      // 0x5C
    { "EOR $abs,X", 3, 4 },   // 0x5D
    { "LSR $abs,X", 3, 7 },   // 0x5E
    { INVALID, -1, -1 },      // 0x5F

    { "RTS", 1, 6 },          // 0x60
    { "ADC ($ind,X)", 2, 6 }, // 0x61
    { INVALID, -1, -1 },      // 0x62
    { INVALID, -1, -1 },      // 0x63
    { INVALID, -1, -1 },      // 0x64
    { "ADC $zpg", 2, 3 },     // 0x65
    { "ROR $zpg", 2, 5 },     // 0x66
    { INVALID, -1, -1 },      // 0x67
    { "PLA", 1, 4 },          // 0x68
    { "ADC #$imm", 2, 2 },    // 0x69
    { "ROR A", 1, 2 },        // 0x6A
    { INVALID, -1, -1 },      // 0x6B
    { "JMP ($ind)", 3, 5 },   // 0x6C
    { "ADC $abs", 3, 4 },     // 0x6D
    { "ROR $abs", 3, 6 },     // 0x6E
    { INVALID, -1, -1 },      // 0x6F

    { "BVS", 2, 2 },          // 0x70
    { "ADC ($ind),Y", 2, 5 }, // 0x71
    { INVALID, -1, -1 },      // 0x72
    { INVALID, -1, -1 },      // 0x73
    { INVALID, -1, -1 },      // 0x74
    { "ADC $zpg,X", 2, 4 },   // 0x75
    { "ROR $zpg,X", 2, 6 },   // 0x76
    { INVALID, -1, -1 },      // 0x77
    { "SEI", 1, 2 },          // 0x78
    { "ADC $abs,Y", 3, 4 },   // 0x79
    { INVALID, -1, -1 },      // 0x7A
    { INVALID, -1, -1 },      // 0x7B
    { INVALID, -1, -1 },      // 0x7C
    { "ADC $abs,X", 3, 4 },   // 0x7D
    { "ROR $abs,X", 3, 7 },   // 0x7E
    { INVALID, -1, -1 },      // 0x7F

    { INVALID, -1, -1 },      // 0x80
    { "STA ($ind,X)", 2, 6 }, // 0x81
    { INVALID, -1, -1 },      // 0x82
    { INVALID, -1, -1 },      // 0x83
    { "STY $zpg", 2, 3 },     // 0x84
    { "STA $zpg", 2, 3 },     // 0x85
    { "STX $zpg", 2, 3 },     // 0x86
    { INVALID, -1, -1 },      // 0x87
    { "DEY", 1, 2 },          // 0x88
    { INVALID, -1, -1 },      // 0x89
    { "TXA", 1, 2 },          // 0x8A
    { INVALID, -1, -1 },      // 0x8B
    { "STY $abs", 3, 4 },     // 0x8C
    { "STA $abs", 3, 4 },     // 0x8D
    { "STX $abs", 3, 4 },     // 0x8E
    { INVALID, -1, -1 },      // 0x8F

    { "BCC", 2, 2 },          // 0x90
    { "STA ($ind),Y", 2, 6 }, // 0x91
    { INVALID, -1, -1 },      // 0x92
    { INVALID, -1, -1 },      // 0x93
    { "STY $zpg,X", 2, 4 },   // 0x94
    { "STA $zpg,X", 2, 4 },   // 0x95
    { "STX $zpg,Y", 2, 4 },   // 0x96
    { INVALID, -1, -1 },      // 0x97
    { "TYA", 1, 2 },          // 0x98
    { "STA $abs,Y", 3, 5 },   // 0x99
    { "TXS", 1, 2 },          // 0x9A
    { INVALID, -1, -1 },      // 0x9B
    { INVALID, -1, -1 },      // 0x9C
    { "STA $abs,X", 3, 5 },   // 0x9D
    { INVALID, -1, -1 },      // 0x9E
    { INVALID, -1, -1 },      // 0x9F

    { "LDY #$imm", 2, 2 },    // 0xA0
    { "LDA ($ind,X)", 2, 6 }, // 0xA1
    { "LDX #$imm", 2, 2 },    // 0xA2
    { INVALID, -1, -1 },      // 0xA3
    { "LDY $zpg", 2, 3 },     // 0xA4
    { "LDA $zpg", 2, 3 },     // 0xA5
    { "LDX $zpg", 2, 3 },     // 0xA6
    { INVALID, -1, -1 },      // 0xA7
    { "TAY", 1, 2 },          // 0xA8
    { "LDA #$imm", 2, 2 },    // 0xA9
    { "TAX", 1, 2 },          // 0xAA
    { INVALID, -1, -1 },      // 0xAB
    { "LDY $abs", 3, 4 },     // 0xAC
    { "LDA $abs", 3, 4 },     // 0xAD
    { "LDX $abs", 3, 4 },     // 0xAE
    { INVALID, -1, -1 },      // 0xAF

    { "BCS", 2, 2 },          // 0xB0
    { "LDA ($ind),Y", 2, 5 }, // 0xB1
    { INVALID, -1, -1 },      // 0xB2
    { INVALID, -1, -1 },      // 0xB3
    { "LDY $zpg,X", 2, 4 },   // 0xB4
    { "LDA $zpg,X", 2, 4 },   // 0xB5
    { "LDX $zpg,Y", 2, 4 },   // 0xB6
    { INVALID, -1, -1 },      // 0xB7
    { "CLV", 1, 2 },          // 0xB8
    { "LDA $abs,Y", 3, 4 },   // 0xB9
    { "TSX", 1, 2 },          // 0xBA
    { INVALID, -1, -1 },      // 0xBB
    { "LDY $abs,X", 3, 4 },   // 0xBC
    { "LDA $abs,X", 3, 4 },   // 0xBD
    { "LDX $abs,Y", 3, 4 },   // 0xBE
    { INVALID, -1, -1 },      // 0xBF

    { "CPY #$imm", 2, 2 },    // 0xC0
    { "CMP ($ind,X)", 2, 6 }, // 0xC1
    { INVALID, -1, -1 },      // 0xC2
    { INVALID, -1, -1 },      // 0xC3
    { "CPY $zpg", 2, 3 },     // 0xC4
    { "CMP $zpg", 2, 3 },     // 0xC5
    { "DEC $zpg", 2, 5 },     // 0xC6
    { INVALID, -1, -1 },      // 0xC7
    { "INY", 1, 2 },          // 0xC8
    { "CMP #$imm", 2, 2 },    // 0xC9
    { "DEX", 1, 2 },          // 0xCA
    { INVALID, -1, -1 },      // 0xCB
    { "CPY $abs", 3, 4 },     // 0xCC
    { "CMP $abs", 3, 4 },     // 0xCD
    { "DEC $abs", 3, 6 },     // 0xCE
    { INVALID, -1, -1 },      // 0xCF

    { "BNE", 2, 2 },          // 0xD0
    { "CMP ($ind),Y", 2, 5 }, // 0xD1
    { INVALID, -1, -1 },      // 0xD2
    { INVALID, -1, -1 },      // 0xD3
    { INVALID, -1, -1 },      // 0xD4
    { "CMP $zpg,X", 2, 4 },   // 0xD5
    { "DEC $zpg,X", 2, 6 },   // 0xD6
    { INVALID, -1, -1  },      // 0xD7
    { "CLD", 1, 2 },          // 0xD8
    { "CMP $abs,Y", 3, 4 },   // 0xD9
    { INVALID, -1, -1 },      // 0xDA
    { INVALID, -1, -1 },      // 0xDB
    { INVALID, -1, -1 },      // 0xDC
    { "CMP $abs,X", 3, 4 },   // 0xDD
    { "DEC $abs,X", 3, 7 },   // 0xDE
    { INVALID, -1, -1 },      // 0xDF

    { "CPX #$imm", 2, 2 },    // 0xE0
    { "SBC ($ind,X)", 2, 6 }, // 0xE1
    { INVALID, -1, -1 },      // 0xE2
    { INVALID, -1, -1 },      // 0xE3
    { "CPX $zpg", 2, 3 },     // 0xE4
    { "SBC $zpg", 2, 3 },     // 0xE5
    { "INC $zpg", 2, 5 },     // 0xE6
    { INVALID, -1, -1 },      // 0xE7
    { "INX", 1, 2 },          // 0xE8
    { "SBC #$imm", 2, 2 },    // 0xE9
    { "NOP", 1, 2 },          // 0xEA
    { INVALID, -1, -1 },      // 0xEB
    { "CPX $abs", 3, 4 },     // 0xEC
    { "SBC $abs", 3, 4 },     // 0xED
    { "INC $abs", 3, 6 },     // 0xEE
    { INVALID, -1, -1 },      // 0xEF

    { "BEQ", 2, 2 },          // 0xF0
    { "SBC ($ind),Y", 2, 5 }, // 0xF1
    { INVALID, -1, -1 },      // 0xF2
    { INVALID, -1, -1 },      // 0xF3
    { INVALID, -1, -1 },      // 0xF4
    { "SBC $zpg,X", 2, 4 },   // 0xF5
    { "INC $zpg,X", 2, 6 },   // 0xF6
    { INVALID, -1, -1 },      // 0xF7
    { "SED", 1, 2 },          // 0xF8
    { "SBC $abs,Y", 3, 4 },   // 0xF9
    { INVALID, -1, -1 },      // 0xFA
    { INVALID, -1, -1 },      // 0xFB
    { INVALID, -1, -1 },      // 0xFC
    { "SBC $abs,X", 3, 4 },   // 0xFD
    { "INC $abs,X", 3, 7 },   // 0xFE
    { INVALID, -1, -1 }       // 0xFF
};

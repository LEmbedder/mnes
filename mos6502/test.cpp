#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "mos6502.hpp"

static std::vector<uint8_t> load_test_rom(const std::string &filename, unsigned header_size = 16);

int main()
{
    std::vector<uint8_t> rom_data = load_test_rom("../roms/nestest.nes");
    try {
        mos6502 cpu(256, rom_data);
        while (cpu.PC() < 0xFFFF) {
            uint16_t pc = cpu.PC();
            std::string syntax = cpu.disassemble();
            std::cout << syntax;
            for (int i = 10 - static_cast<int>(syntax.length()); i >= 0; i--)
                std::cout << " ";

            cpu.print_state();
            cpu.execute_instruction();
        }
    } catch (std::exception &e) {
        std::cout << "ERROR: " <<  e.what() << std::endl;
        return 1;
    }

    std::cin.get();
    return 0;
}

static std::vector<uint8_t> load_test_rom(const std::string &filename, unsigned header_size)
{
    std::ifstream file(filename, std::ios::binary);
    auto begin = std::istreambuf_iterator<char>(file);
    std::advance(begin, header_size);
    auto end = std::istreambuf_iterator<char>();
    std::vector<uint8_t> buffer(begin, end);


    std::vector<uint8_t> rom_data;
    rom_data.resize(0x10000);
    std::copy(buffer.begin(), buffer.begin() + 0x4000, rom_data.begin() + 0x8000);
    std::copy(buffer.begin(), buffer.begin() + 0x4000, rom_data.begin() + 0xC000);
    rom_data.resize(0x10000);
    rom_data[0xFFFC] = 0x00;
    rom_data[0xFFFD] = 0xC0;
    return rom_data;
}

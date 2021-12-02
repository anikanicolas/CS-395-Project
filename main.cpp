/**
 * Computer Architecture Project
 * Anika Nicolas & Rosemary Koshy
 * Due: Friday, November 12 at 1:30 PM
 * C++17
 * A DEC Alpha processor simulator that reads and executes binary programs.
 * 1. Instruction fetch: fetch instructions from memory
 * 2. Instruction decode and register fetch: read registers and decode the
 * instruction
 * 3. Execute: execute the instruction or calculate an address
 * 4. Memory access: access an operand in data memory
 * 5. Register write back: write the result into a register
 * TODO: ALU, decode, ...
 * TODO(anikanicolas): add more instructions to input.txt or add input1.txt
 */
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "decode.cpp"
#include "execute.cpp"
#include "instructions.cpp"
#include "memory.cpp"
#include "writeback.cpp"

/**
 * Print error message and terminate program execution with failure status
 * @param message First part of error message to print
 */
[[noreturn]] void fail(const std::string &message) {
    perror(message.c_str());
    exit(EXIT_FAILURE);
}

std::vector<std::string> read(const std::string &filename) {
    std::ifstream file;
    std::string line;
    std::vector<std::string> instructions;
    file.open(filename);

    if (!file) fail("File " + filename + " not opened");
    while (file >> line) instructions.push_back(line);

    file.close();
    return instructions;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [filename]\n";
        return EXIT_FAILURE;
    }

    // declare variables
    auto *pipeline = new std::string[5];
    size_t counter = 0;
    auto *registers = new int64_t[32];
    std::map<std::string, std::string> op_map = get_op_map();
    std::map<std::string, std::string> func_map = get_func_map();
    std::map<std::string, std::string> comp_map = get_comp_map();
    std::map<std::string, std::string> jump_map = get_jump_map();

    std::vector<std::string> instructions = read(argv[1]);

    std::cout << std::setw(8) << "Clock";
    std::cout << '|';
    std::cout << std::setw(32) << "Fetch";
    std::cout << '|';
    std::cout << std::setw(32) << "Decode";
    std::cout << '|';
    std::cout << std::setw(32) << "Execute";
    std::cout << '|';
    std::cout << std::setw(32) << "Memory";
    std::cout << '|';
    std::cout << std::setw(32) << "Write-back";
    std::cout << '\n';

    for (size_t clock = 0; clock < instructions.size(); ++clock) {
        std::cout << std::setw(8) << clock;
        std::cout << '|';
        pipeline[0] = instructions[counter];
        std::cout << std::setw(32) << pipeline[0];
        std::cout << '|';
        pipeline[1] = decode(pipeline[0], op_map, func_map, comp_map, jump_map);
        std::cout << std::setw(32) << pipeline[1];
        std::cout << '|';
        std::cout << std::setw(32) << "Execute";
        std::cout << '|';
        std::cout << std::setw(32) << "Memory";
        std::cout << '|';
        std::cout << std::setw(32) << "Write-back";
        std::cout << '\n';
        ++counter;
    }

    delete[] registers;
    delete[] pipeline;
    return EXIT_SUCCESS;
}

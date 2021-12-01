/**
 * Computer Architecture Project
 * Anika Nicolas & Rosemary Koshy
 * Due: Friday, November 12 at 1:30 PM
 * C++17
 * A self-contained RISC-V assembler and simulator that reads and executes
 * RV32I Base Integer Instruction Set assembly programs.
 * fetch, decode, execute, memory, write-back
 * TODO: ALU, decode, ...
 */
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

//#include "processor.cpp"

/**
 * Print error message and terminate program execution with failure status
 * @param message First part of error message to print
 */
void fail(const std::string &message) {
    perror(message.c_str());
    exit(EXIT_FAILURE);
}

std::vector<std::string> read(const std::string &filename) {
    std::ifstream file;
    std::string line;
    std::vector<std::string> instructions;
    file.open(filename);

    if (!file) fail("File " + filename + " not opened");
    while (file) {
        file >> line;
        instructions.push_back(line);
    }

    file.close();
    return instructions;
}

int main(int argc, char *argv[]) {
    // declare variables
    std::vector<std::string> pipeline;
    size_t counter = 0;
    auto *registers = new int64_t[32];

    if (argc != 2) {
        std::cerr << "Usage: " << basename(argv[0]) << " [filename]\n";
        return EXIT_FAILURE;
    }
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
        std::cout << std::setw(32) << instructions[counter];
        std::cout << '|';
        std::cout << std::setw(32) << "Decode";
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
    return EXIT_SUCCESS;
}

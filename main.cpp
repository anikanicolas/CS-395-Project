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
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

void read()

int main(int argc, char* argv[]) {
    // declare variables
    std::ifstream file;
    std::string line;
    std::vector<std::string> instructions;
    std::vector<std::string> pipeline;
    size_t counter = 0;

    file.open("input.txt");
    if (!file) {
        perror("Cannot open file");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; file; ++i) {
        file >> line;
        instructions.push_back(line);
    }

    std::cout << std::setw(8) << "Clock";
    std::cout << '|';
    std::cout << std::setw(32) << "Fetch";
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
        std::cout << std::setw(32) << "Execute";
        std::cout << '|';
        std::cout << std::setw(32) << "Memory";
        std::cout << '|';
        std::cout << std::setw(32) << "Write-back";
        std::cout << '\n';
        ++counter;
    }

    file.close();
    return EXIT_SUCCESS;
}

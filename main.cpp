/**
 * Computer Architecture Project
 * Anika Nicolas & Rosemary Koshy
 * Due: Friday, November 12 at 1:30 PM
 * C++17
 * A self-contained RISC-V assembler and simulator that reads and executes
 * RV32I Base Integer Instruction Set assembly programs.
 * fetch, decode, execute, memory, write-back
 */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    std::ifstream file;
    std::string line;
    file.open("input.txt");
    if (!file) {
        perror("Cannot open file");
        return EXIT_FAILURE;
    }
    while (file) {
        file >> line;
        std::cout << line << '\n';
    }
    file.close();
    return EXIT_SUCCESS;
}

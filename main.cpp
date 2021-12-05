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

/**
 * Read instructions from file and return as vector
 * @param filename name of file to read instructions from
 * @return vector of instructions
 */
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

/**
 * Row out for program excepting clock
 * @param pipeline basic five-stage risc pipeline to print
 */
void print_pipeline(std::string *pipeline) {
    std::cout << std::setw(32) << pipeline[0];
    std::cout << '|';
    std::cout << std::setw(32) << pipeline[1];
    std::cout << '|';
    std::cout << std::setw(32) << pipeline[2];
    std::cout << '|';
    std::cout << std::setw(32) << pipeline[3];
    std::cout << '|';
    std::cout << std::setw(32) << pipeline[4];
    std::cout << std::endl;
}

/**
 * Read program argument and call helper functions
 * @param argc argument count including program name
 * @param argv array of C-string arguments
 * @return exit status
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [filename]\n";
        return EXIT_FAILURE;
    }

    // declare variables
    std::string pipeline[5] = {"Fetch", "Decode", "Execute", "Memory",
                               "Writeback"};
    size_t counter = 0;
    auto *registers = new int64_t[32];
    std::map<std::string, std::string> op_map = get_op_map();
    std::map<std::string, std::string> func_map = get_func_map();
    std::map<std::string, std::string> comp_map = get_comp_map();
    std::map<std::string, std::string> jump_map = get_jump_map();

    std::vector<std::string> instructions = read(argv[1]);

    std::cout << "Clock|";
    print_pipeline(pipeline);

    /*
     * I believe we can implement stalling by doing the pipeline in reverse
     * order. We do the last thing in the pipeline first, then each thing before
     * that. We don't want to move fetch into decode because if it turns out
     * decode can't be moved to execute yet, then we'd have to revert it. The
     * first in line should move forward before those waiting behind do.
     */
    for (size_t clock = 0; clock < instructions.size(); ++clock) {
        pipeline[0] = instructions[counter];
        pipeline[1] = decode(pipeline[0], op_map, func_map, comp_map, jump_map);
        std::cout << std::setw(5) << clock << '|';
        print_pipeline(pipeline);
        ++counter;
    }

    delete[] registers;
    return EXIT_SUCCESS;
}

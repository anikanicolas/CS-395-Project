/**
 * Computer Architecture Project
 * Anika Nicolas & Rosemary Koshy
 * Due: Wed, Dec 8 at 1:30 PM
 * C++17
 * A RISC-V processor simulator that reads and executes binary programs.
 * https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf
 * https://cs.stanford.edu/people/eroberts/courses/soco/projects/risc/pipelining/index.html
 * https://en.wikipedia.org/wiki/Instruction_pipelining
 * https://en.wikipedia.org/wiki/Classic_RISC_pipeline
 * 1. Instruction fetch: fetch instructions from memory
 * 2. Instruction decode and register fetch: read registers and decode
 * instruction
 * 3. Execute: execute the instruction or calculate an address
 * 4. Memory access: access an operand in data memory
 * 5. Register write back: write the result into a register
 * TODO: ALU, ...
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

#include "idecode.cpp"
#include "iexecute.cpp"
#include "maccess.cpp"
#include "rfetch.cpp"
#include "rwriteback.cpp"

/**
 * Print error message and terminate program execution with failure status
 * @param message First part of error message to print
 */
[[noreturn]] void fail(const std::string &message) {
    perror(message.c_str());
    exit(EXIT_FAILURE);
}

/**
 * Read instructions from input stream and return as vector
 * @param input_stream to read instructions from
 * @return vector of instructions
 */
std::vector<std::string> read(std::istream &input_stream) {
    /// line gotten from file
    std::string line;
    /// vector of instructions to return
    std::vector<std::string> instructions;
    while (input_stream >> line) instructions.push_back(line);
    return instructions;
}

/**
 * Convert vector to string
 * @param vec vector to convert
 * @return string of each item in vector separated by space
 */
std::string vectostr(const std::vector<std::string> &vec) {
    /// string to return
    std::string str;
    if (!vec.empty()) {
        str.append(vec[0]);
        for (size_t i = 1; i < vec.size(); ++i) {
            str.append(' ' + vec[i]);
        }
    }
    return str;
}

/**
 * Print pipeline as table
 * @param pipeline basic five-stage risc pipeline to print
 */
void print_pipeline(std::vector<std::string> *pipeline) {
    std::cout << std::setw(32) << vectostr(pipeline[0]);
    std::cout << '|';
    std::cout << std::setw(32) << vectostr(pipeline[1]);
    std::cout << '|';
    std::cout << std::setw(32) << vectostr(pipeline[2]);
    std::cout << '|';
    std::cout << std::setw(32) << vectostr(pipeline[3]);
    std::cout << '|';
    std::cout << std::setw(32) << vectostr(pipeline[4]);
    std::cout << '|';
    std::cout << std::setw(32) << vectostr(pipeline[5]);
    std::cout << std::endl;
}

/**
 * Read program argument and call helper functions
 * @param argc argument count including program name should be 1 or 2
 * @param argv array of C-string arguments including filename
 * @return exit status
 */
int main(int argc, char *argv[]) {
    /// vector of binary instruction strings read from file
    std::vector<std::string> instructions;
    if (argc == 1) {
        instructions = read(std::cin);
    } else if (argc == 2) {
        /// name of file to read instructions from
        std::string filename = argv[1];
        /// input file stream
        std::ifstream file;
        file.open(filename);
        if (!file) fail("File " + filename + " not opened");
        instructions = read(file);
        file.close();
    } else {
        std::cerr << "Usage: " << basename(argv[0]) << " [filename]\n";
        return EXIT_FAILURE;
    }

    /// RISC pipeline (plus register fetch)
    std::vector<std::string> pipeline[6] = {{"Instruction Fetch"},
                                            {"Instruction Decode"},
                                            {"Register Fetch"},
                                            {"Execute"},
                                            {"Memory access"},
                                            {"Register Writeback"}};
    /// program counter holds the address of the current instruction
    size_t pc = 0;
    /// array of 32 unsigned 32-bit integer registers (0 is unused)
    auto *registers = new uint32_t[32];
    for (uint32_t i = 0; i < 32; ++i) {
        registers[i] = i;
    }

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
        pipeline[0] = {instructions[pc]};
        pipeline[1] = idecode(pipeline[0][0]);
        pipeline[2] = rfetch(pipeline[1], registers);
        pipeline[3] = iexecute(pipeline[2], pc);
        pipeline[4] = maccess(pipeline[3]);
        pipeline[5] = rwriteback(pipeline[4], registers);
        std::cout << std::setw(5) << clock << '|';
        print_pipeline(pipeline);
        ++pc;
    }

    delete[] registers;
    return EXIT_SUCCESS;
}

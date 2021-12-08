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
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <libgen.h>

#include "idecode.h"
#include "iexecute.h"
#include "maccess.h"
#include "rfetch.h"
#include "rwriteback.h"
#include "utils.h"

/**
 * Print pipeline as table
 * @param pipeline basic five-stage risc pipeline to print
 */
static void print_pipeline(std::vector<std::string> *pipeline) {
    std::cout << std::left << std::setw(32) << vectostr(pipeline[0]) << '|';
    std::cout << std::setw(30) << vectostr(pipeline[1]) << '|';
    std::cout << std::setw(40) << vectostr(pipeline[2]) << '|';
    std::cout << std::setw(40) << vectostr(pipeline[3]) << '|';
    std::cout << std::setw(40) << vectostr(pipeline[4]) << '|';
    std::cout << std::setw(8) << vectostr(pipeline[5]) << '|' << std::endl;
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
                                            {"Instruction Execute"},
                                            {"Memory access"},
                                            {"Reg WB"}};
    /// program counter holds the address of the current instruction
    uint32_t pc = 0;
    /// array of 32 unsigned 32-bit integer registers (0 is unused)
    auto *registers = new uint32_t[32];
    for (uint32_t i = 0; i < 32; ++i) {
        registers[i] = i;
    }
    // array of booleans for each register to check if it's being written to or
    // not
    auto good_register = new bool[32];
    for (int i = 0; i < 32; i++) {
        good_register[i] = true;
    }

    auto *memory = new std::byte[4096];
    for (size_t i = 0; i < 4096; ++i) {
        memory[i] = std::byte(i);
    }

    std::cout << "Clck|";
    print_pipeline(pipeline);
    for (auto &i: pipeline) i = {};

    /*
     * I believe we can implement stalling by doing the pipeline in reverse
     * order. We do the last thing in the pipeline first, then each thing before
     * that. We don't want to move fetch into decode because if it turns out
     * decode can't be moved to execute yet, then we'd have to revert it. The
     * first in line should move forward before those waiting behind do.
     */

    bool go = true;
    std::vector<std::string> check = {"STALL"};
    std::vector<std::string> rememberins;
    for (size_t clock = 0; go; ++clock) {
        // if you have a stall at register fetch, then you want the output to
        // say
        // stall for each iteration at register fetch stage as long as the
        // register is not available
        // you also want any instructions before it go proceed as normal
        pipeline[5] = rwriteback(pipeline[4], registers, good_register);
        pipeline[4] = maccess(pipeline[3], memory);
        pipeline[3] = iexecute(pipeline[2], pc);
        if (pipeline[3] == check) {
            pipeline[3] = {};
        }
        pipeline[2] = rfetch(pipeline[1], registers, good_register);
        if (pipeline[2] != check) {
            if (!pipeline[0].empty()) {
                pipeline[1] = idecode(pipeline[0][0]);
            } else {
                pipeline[1] = {};
            }
            if (pc < instructions.size()) {
                pipeline[0] = {instructions[pc]};  // instruction fetch
            } else {
                pipeline[0] = {};
            }
            ++pc;
        }
        if (pipeline[2] == check) {
            rememberins = pipeline[1];
            pipeline[1] = {};
        }
        std::cout << std::setw(4) << clock << '|';
        print_pipeline(pipeline);
        if (pipeline[2] == check) {
            pipeline[1] = rememberins;
        }
        go = false;
        for (auto &i: pipeline)
            if (!i.empty()) go = true;
    }

    delete[] registers;
    delete[] memory;
    return EXIT_SUCCESS;
}

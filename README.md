# CS 395 Computer Architecture Project

Anika Nicolas & Rosemary Koshy

Due: Wed, Dec 8 at 1:30 PM

C++17

A RISC-V processor simulator that reads and executes binary programs.
 * https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf
 * https://cs.stanford.edu/people/eroberts/courses/soco/projects/risc/pipelining/index.html
 * https://en.wikipedia.org/wiki/Instruction_pipelining
 * https://en.wikipedia.org/wiki/Classic_RISC_pipeline
1. Instruction fetch: fetch instructions from memory
2. Instruction decode and register fetch: read registers and decode the instruction
3. Execute: execute the instruction or calculate an address
4. Memory access: access an operand in data memory
5. Register write back: write the result into a register
TODO: ALU, ...
TODO(anikanicolas): add more instructions to input.txt or add input1.txt


To Charlie:
You can run make and then say ./processor test.txt or another text file to see output

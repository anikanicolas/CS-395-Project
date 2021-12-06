/**
 * Execute: execute the instruction or calculate an address
 * https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf
 */
#include <string>

// execute stage [[ unused ]]
std::string execute(const std::string &r1, const std::string &r2, const std::string &op) {
    if (op == "addq") {
        return r1 + " + " + r2;
    } else if (op == "subq") {
        return "difference";
    }
    return "None";
}

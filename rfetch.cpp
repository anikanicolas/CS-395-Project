/**
 * Register fetch
 * https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf
 */
#include <string>
#include <vector>

std::vector<std::string> rfetch(const std::vector<std::string> &decoded) {
    for (auto word: decoded) {
        if (word[0] == 't') {

        }
    }
    return {"FAILURE"};
}

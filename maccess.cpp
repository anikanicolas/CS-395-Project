/**
 * Memory access: access an operand in data memory
 */
#include "maccess.h"

#include <string>
#include <vector>

#include "utils.h"

// memory stage
// store instruction:
// take in what iexecute returns
// vector be main memory
/// dummy function returns argument
std::vector<std::string> maccess(const std::vector<std::string> &executed, std::byte memory[4096]) {
    if (executed.empty() || executed[0].empty()) return {};
    std::vector<std::string> ret = executed;
    return ret;
}

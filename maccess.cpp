/**
 * Memory access: access an operand in data memory
 */
#include <string>
#include <vector>

// memory stage
// store instruction:
// take in what iexecute returns
// vector be main memory
/// dummy function returns argument
std::vector<std::string> maccess(const std::vector<std::string> &executed) {
    if (executed.empty() || executed[0].empty()) return {};
    std::vector<std::string> ret = executed;
    return ret;
}

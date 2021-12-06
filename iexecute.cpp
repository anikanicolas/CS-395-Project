/**
 * Instruction Execute: execute the instruction or calculate an address
 */
#include <string>
#include <vector>

// execute stage [[ unused ]]
std::vector<std::string> iexecute(const std::vector<std::string> &decoded) {
    std::vector<std::string> ret;
    if (decoded[0] == "ADD") {
        ret = {"WB", decoded[1], std::to_string(stoul(decoded[2]) + stoul(decoded[3]))};
    }
    return ret;
}

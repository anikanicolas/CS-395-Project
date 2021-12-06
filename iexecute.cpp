/**
 * Instruction Execute: execute the instruction or calculate an address
 */
#include <string>
#include <vector>

// execute stage [[ unused ]]
std::vector<std::string> iexecute(const std::vector<std::string> &decoded) {
    std::vector<std::string> ret;
    if (decoded[0] == "ADD") {
        // ADD performs the addition of rs1 and rs2
        ret = {"WB", decoded[1],
               std::to_string(stoul(decoded[2]) + stoul(decoded[3]))};
    } else if (decoded[0] == "SUB") {
        // SUB performs the subtraction of rs2 from rs1
        ret = {"WB", decoded[1],
               std::to_string(stoul(decoded[2]) - stoul(decoded[3]))};
    }
    return ret;
}

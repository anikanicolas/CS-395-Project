/**
 * Instruction Execute: execute the instruction or calculate an address
 */
#include <string>
#include <vector>

// execute stage [[ unused ]]
/**
 * Execute decoded instruction with fetched registers
 * @param decoded instruction to execute
 * @return executed instruction
 */
std::vector<std::string> iexecute(const std::vector<std::string> &decoded) {
    /// execution state to return, FAILURE by default
    std::vector<std::string> ret = {"FAILURE"};
    if (!decoded.empty()) {
        std::string op = decoded[0];
        std::string dest;
        std::string src1;
        std::string src2;
        if (decoded.size() > 1) {
            dest = decoded[1];
        }
        if (decoded.size() > 2) {
            src1 = decoded[2];
        }
        if (decoded.size() > 3) {
            src2 = decoded[3];
        }
        if (op == "LUI") {
            /*
             * A LUI instruction can first load src1 with the upper 20 bits of a target address
             * LUI (load upper immediate) places the 20-bit U-immediate into bits 31–12 of register dest
             * and places zero in the lowest 12 bits.
             */
            ret = {"WB", dest, 'b' + src1 + "000000000000"};
        } else if (op == "ADD") {
            // ADD performs the addition of src1 and src2
            ret = {"WB", dest, std::to_string(stoul(src1) + stoul(src2))};
        } else if (op == "SUB") {
            // SUB performs the subtraction of src2 from src1
            ret = {"WB", dest, std::to_string(stoul(src1) - stoul(src2))};
        }
    }
    return ret;
}

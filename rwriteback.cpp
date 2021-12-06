/**
 * Register write back: write the result into a register
 */
#include <string>
#include <vector>

// write-back stage
// return a register with the memory data

/**
 * Set integer value at register address from value
 * @param addr address of register as an integer
 * @param val to write to regs[addr]
 * @param regs array of registers
 * @return string representing value of register
 */
std::string rset(const size_t &addr, const uint32_t &val, uint32_t regs[32]) {
    if (addr) {
        regs[addr] = val;
        return {"SUCCESS"};
    }
    return {"ZERO"};
}

/**
 * Find register addresses in executed instruction and replace with values
 * @param executed vector of words representing instruction
 * @param regs array of 32 unsigned 32-bit integer registers
 * @return new copy of executed instruction with fetched registers
 */
std::vector<std::string> rwriteback(const std::vector<std::string> &executed, uint32_t regs[32]) {
    /// return of rfetch is initially executed input
    if (executed.size() == 3 && executed[0] == "WB" && executed[1][0] == 'd') {
        std::string dest = executed[1];
        std::string sval = executed[2];
        size_t addr = stoul(dest.substr(1, dest.length() - 1));
        auto val = static_cast<uint32_t>(stoul(sval));
        return {rset(addr, val, regs)};
    }
    return {"NONE"};
}

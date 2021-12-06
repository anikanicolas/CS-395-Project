/**
 * Register fetch: read registers
 */
#include <string>
#include <vector>

/**
 * Get string for integer value at register address
 * @param addr address of register as an integer
 * @param regs array of registers
 * @return string representing value of register
 */
std::string rget(const size_t &addr, const uint32_t regs[]) {
    if (!addr) {
        return "0";
    } else {
        return std::to_string(regs[addr]);
    }
}

/**
 * Find register addresses in decoded instruction and replace with values
 * @param decoded vector of words representing instruction
 * @param regs array of 32 unsigned 32-bit integer registers
 * @return new copy of decoded instruction with fetched registers
 */
std::vector<std::string> rfetch(const std::vector<std::string> &decoded, const uint32_t regs[31]) {
    /// return of rfetch is initially decoded input
    std::vector<std::string> ret = decoded;
    if (!decoded.empty()) {
        for (size_t i = 1; i < decoded.size(); ++i) {
            /// word to check if it is a register address to fetch
            std::string word = decoded[i];
            if (word[0] == 's') {
                ret[i] = rget(stoul(word.substr(1, word.length() - 1)), regs);
            }
        }
    }
    return ret;
}

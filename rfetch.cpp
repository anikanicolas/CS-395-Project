/**
 * Register fetch: read registers
 */
#include "rfetch.h"

#include <string>
#include <vector>

#include "utils.h"

/**
 * Get string for integer value at register address
 * @param addr address of register as an integer
 * @param regs array of registers
 * @return string representing value of register
 */
std::string rget(const size_t &addr, const int32_t regs[]) {
    if (!addr) {
        return "00000000000000000000000000000000";
    } else {
        return xto_string(static_cast<uint32_t>(regs[addr]));
    }
}

/**
 * Find register addresses in decoded instruction and replace with values
 * @param decoded vector of words representing instruction
 * @param regs array of 32 unsigned 32-bit integer registers
 * @return new copy of decoded instruction with fetched registers
 */
std::vector<std::string> rfetch(const std::vector<std::string> &decoded, const int32_t regs[32]) {
    if (decoded.empty() || decoded[0].empty()) return {};
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

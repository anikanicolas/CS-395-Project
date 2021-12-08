/**
 * Register fetch: read registers
 */
#include "rfetch.h"

#include <string>
#include <vector>
// Stalling: determine whether the decoded instruction reads from a register
// to which the currently executed instruction writes

#include "utils.h"

/**
 * Get string for integer value at register address
 * @param addr address of register as an integer
 * @param regs array of registers
 * @return string representing value of register
 */
std::string rget(const size_t &addr, const uint32_t regs[], const bool good_register[32]) {
    if (!addr) {
        return "00000000000000000000000000000000";
    } else {
        // stalling: check if the register is currently being written to
        if (good_register[addr]) {
            return xto_string(regs[addr]);
        } else {
            return "invalid";
        }
    }
}

/**
 * Find register addresses in decoded instruction and replace with values
 * @param decoded vector of words representing instruction
 * @param regs array of 32 unsigned 32-bit integer registers
 * @return new copy of decoded instruction with fetched registers
 */
std::vector<std::string>
rfetch(const std::vector<std::string> &decoded, const uint32_t regs[32], bool good_register[32]) {
    if (decoded.empty() || decoded[0].empty()) return {};
    /// return of rfetch is initially decoded input
    std::vector<std::string> ret = decoded;
    if (!decoded.empty()) {
        for (size_t i = 0; i < decoded.size(); ++i) {
            /// word to check if it is a register address to fetch
            std::string word = decoded[i];
            if (word[0] == 's') {
                ret[i] = rget(stoul(word.substr(1, word.length() - 1)), regs, good_register);
            }
            // if a load, then the register should not be available
            if (word[0] == 'L') {
                std::string dest_word = decoded[i + 1];
                if (dest_word[0] == 'd') {
                    auto temp_address = stoul(dest_word.substr(1, dest_word.length() - 1));
                    good_register[temp_address] = false;
                    if (!good_register[temp_address]) {
                        // If statement had no body and no else clause
                    }
                }
            }
        }
    }
    for (size_t i = 1; i < ret.size(); i++) {
        if (ret[i] == "invalid") {
            ret = {"STALL"};
        }
    }
    return ret;
}

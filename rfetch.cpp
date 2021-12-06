/**
 * Register fetch
 * https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf
 */
#include <string>
#include <vector>

std::string get_reg(const size_t &addr, const uint32_t regs[]) {
    if (!addr) {
        return "0";
    } else {
        return std::to_string(regs[addr - 1]);
    }
}

std::vector<std::string> rfetch(const std::vector<std::string> &decoded, const uint32_t regs[31]) {
    std::vector<std::string> ret = decoded;
    if (!decoded.empty()) {
        for (size_t i = 1; i < decoded.size(); ++i) {
            std::string word = decoded[i];
            if (word[0] == 't') {
                ret[i] = get_reg(stoul(word.substr(1, word.length() - 1)), regs);
            }
        }
    }
    return ret;
}

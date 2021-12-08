#include <string>
#include <vector>

#ifndef RFETCH_H
#define RFETCH_H

std::string rget(const size_t &addr, const uint32_t regs[], const bool good_register[32]);

std::vector<std::string>
rfetch(const std::vector<std::string> &decoded, const uint32_t regs[32], bool good_register[32]);

#endif

#include <string>
#include <vector>

#ifndef RFETCH_H
#define RFETCH_H

std::string rget(const uint32_t &addr, const uint32_t regs[]);

std::vector<std::string> rfetch(const std::vector<std::string> &decoded, const uint32_t regs[32]);

#endif

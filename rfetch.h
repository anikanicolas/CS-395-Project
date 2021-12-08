#include <string>
#include <vector>

#ifndef RFETCH_H
#define RFETCH_H

std::string rget(const size_t &addr, const int32_t regs[]);

std::vector<std::string> rfetch(const std::vector<std::string> &decoded, const int32_t regs[32]);

#endif

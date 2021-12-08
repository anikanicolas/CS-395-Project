#include <string>
#include <vector>

#ifndef RWRITEBACK_H
#define RWRITEBACK_H

std::string rset(const size_t &addr, const int32_t &val, int32_t regs[32]);

std::vector<std::string> rwriteback(const std::vector<std::string> &executed, int32_t regs[32]);

#endif

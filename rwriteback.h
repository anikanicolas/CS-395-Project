#include <string>
#include <vector>

#ifndef RWRITEBACK_H
#define RWRITEBACK_H

std::string rset(const size_t &addr, const uint32_t &val, uint32_t regs[32]);

std::vector<std::string> rwriteback(const std::vector<std::string> &executed, uint32_t regs[32]);

#endif

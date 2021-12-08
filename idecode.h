#include <string>
#include <vector>

#ifndef IDECODE_H
#define IDECODE_H

std::string isubstr(const std::string &instruction, const size_t &start, const size_t &end);

std::vector<std::string> idecode(const std::string &inst);

#endif

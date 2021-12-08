#include <bitset>
#include <string>
#include <vector>

#ifndef UTILS_H
#define UTILS_H

[[noreturn]] void fail(const std::string &message);

std::vector<std::string> read(std::istream &input_stream);

std::string vectostr(const std::vector<std::string> &vec);

std::string bytetostring(std::byte byte);

std::string xto_string(uint32_t uint);

std::string sxto_string(int32_t int32);

int32_t xstoi(const std::string &str);

uint32_t xstoui(const std::string &str);

std::string rmprefix(const std::string &word);

std::string to_decimal(const std::string &binary);

#endif

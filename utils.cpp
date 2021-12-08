/**
 * Helper functions and methods
 */
#include "utils.h"

#include <bitset>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

/**
 * Print error message and terminate program execution with failure status
 * @param message First part of error message to print
 */
[[noreturn]] void fail(const std::string &message) {
    perror(message.c_str());
    exit(EXIT_FAILURE);
}

/**
 * Read instructions from input stream and return as vector
 * @param input_stream to read instructions from
 * @return vector of instructions
 */
std::vector<std::string> read(std::istream &input_stream) {
    /// line gotten from file
    std::string line;
    /// vector of instructions to return
    std::vector<std::string> instructions;
    while (std::getline(input_stream, line)) instructions.push_back(line);
    return instructions;
}

/**
 * Convert vector to string
 * @param vec vector to convert
 * @return string of each item in vector separated by space
 */
std::string vectostr(const std::vector<std::string> &vec) {
    /// string to return
    std::string str;
    if (!vec.empty()) {
        str.append(vec[0]);
        for (size_t i = 1; i < vec.size(); ++i) {
            str.append(' ' + vec[i]);
        }
    }
    return str;
}

/**
 * Convert byte to binary string
 * @param byte to convert
 * @return binary string
 */
std::string bytetostring(std::byte byte) {
    return std::bitset<8>(static_cast<uint64_t>(byte)).to_string();
}

/**
 * Convert 32-bit unsigned integer to binary string
 * @param uint unsigned integer to convert
 * @return binary string
 */
std::string xto_string(uint32_t uint) {
    return std::bitset<32>(static_cast<uint64_t>(uint)).to_string();
}

/**
 * Convert signed 32-bit integer to binary string
 * @param int32 signed integer to convert
 * @return binary string
 */
std::string sxto_string(int32_t int32) {
    return xto_string(static_cast<uint32_t>(int32));
}

/**
 * Convert a binary string to a 32-bit integer
 * @param str to convert
 * @return 32-bit integer
 */
int32_t xstoi(const std::string &str) {
    return static_cast<int32_t>(std::stol(str, nullptr, 2));
}

/**
 * Convert a binary string to an unsigned 32-bit integer
 * @param str to convert
 * @return unsigned 32-bit integer
 */
uint32_t xstoui(const std::string &str) {
    return static_cast<uint32_t>(std::stoul(str, nullptr, 2));
}

/**
 * Get word excepting first character
 * @param word to remove fist character from
 * @return rest of the word
 */
std::string rmprefix(const std::string &word) {
    return word.substr(1, word.length() - 1);
}

/**
 * Convert binary string to decimal string (unsigned)
 * @param binary string to convert
 * @return decimal string
 */
std::string to_decimal(const std::string &binary) {
    return std::to_string(stoul(binary, nullptr, 2));
}

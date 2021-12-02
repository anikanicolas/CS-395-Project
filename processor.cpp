/**
 * Hello Anika,
 * I edited this file, including renaming variables.
 * Feel free to revert any changes or reformat the code to your liking.
 * --Rosemary
 */
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

std::string xfind(const std::map<std::string, std::string> &map,
                  const std::string &key) {
    auto it = map.find(key);
    if (it == map.end()) return "FAILURE";
    return it->second;
}

// convert binary string to binary integer
size_t to_size(const std::string &binary_string) {
    return stoul(binary_string, nullptr, 2);
}

// instruction decode and register fetch stage
// std::tuple<std::string, std::string, std::string> decode....{}
std::string decode(std::string inst,
                   const std::map<std::string, std::string> &op_map,
                   const std::map<std::string, std::string> &func_map,
                   const std::map<std::string, std::string> &comp_map,
                   const std::map<std::string, std::string> &jump_map) {
    std::string op = xfind(op_map, inst.substr(0, 6));
    if (op == "operation") {
        std::string func = xfind(func_map, inst.substr(20, 27));
        if (func == "addq") {
            // check if bit 19 is 1, then it's an RI type inst
            if (inst[19]) {
                size_t ra = to_size(inst.substr(6, 11));
                std::cerr << "ra: " << ra << '\n';
                size_t ib = to_size(inst.substr(11, 19));
                std::cerr << "ib: " << ib << '\n';
            } else {  // if the bit 19 is 0, then it's an RR type inst
                size_t ra = to_size(inst.substr(6, 11));
                size_t rb = to_size(inst.substr(11, 16));
                // access ra address in register array and get data
                // access rb address in register array and get data
                // return ra data, rb data, and operation
                // return std::make_tuple(ra, rb, operation)
                // return a tuple with these three data points
                // execute takes in the tuple and then execute parses the tuple
                return op + ' ' + func + ' ' + std::to_string(ra) + ' ' +
                       std::to_string(rb);
            }
        } else if (func == "subq") {
            if (inst[19] == 0) {
            }
        }
        return op + ' ' + func;
    }
    return op;
}

// execute stage
std::string execute(const std::string &r1, const std::string &r2,
                    const std::string &op) {
    if (op == "addq") {
        return r1 + " + " + r2;
    } else if (op == "subq") {
        return "difference";
    }
    return "None";
}

// memory stage
// store instruction:
// take in what execute returns
// vector be main memory
// write-back stage
// return a register with the memory data

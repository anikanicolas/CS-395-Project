/**
 * Hello Anika,
 * I edited this file, including renaming variables.
 * Feel free to revert any changes or reformat the code to your liking.
 * --Rosemary
 */
#include <cmath>
#include <map>
#include <string>

std::string xfind(const std::map<std::string, std::string> &map,
                  const std::string &key) {
    auto it = map.find(key);
    if (it == map.end()) return "FAILURE";
    return it->second;
}
//convert binary string to a decimal number
size_t to_decimal(const std::string &binary_string) {
    unsigned long num = stoul(binary_string, nullptr, 2);
    int decimal = 0;
    int count = 0;
    int remainder = 0;
    while(num != 0) {
      remainder = num % 10;
      num /= 10;
      decimal += remainder * pow(2, count);
      ++count;
    }
    return decimal;
}

// set inst map getters

std::map<std::string, std::string> get_op_map() {
    std::map<std::string, std::string> op_map;
    op_map["010000"] = "operation";
    op_map["010001"] = "comparison";
    op_map["101001"] = "ldq";
    op_map["011101"] = "stq";
    op_map["111001"] = "beq";
    op_map["111101"] = "bne";
    op_map["011010"] = "jump";
    op_map["000100"] = "op on line 1 of input.txt";
    op_map["000101"] = "op on line 2 of input.txt";
    return op_map;
}

std::map<std::string, std::string> get_func_map() {
    std::map<std::string, std::string> func_map;
    func_map["0100000"] = "addq";
    func_map["0101001"] = "subq";
    return func_map;
}

std::map<std::string, std::string> get_comp_map() {
    std::map<std::string, std::string> comp_map;
    comp_map["0100000"] = "or/bis";
    comp_map["1000000"] = "xor";
    comp_map["0100100"] = "cmoveq";
    comp_map["1001101"] = "cmplt";
    return comp_map;
}

std::map<std::string, std::string> get_jump_map() {
    std::map<std::string, std::string> jump_map;
    jump_map["00"] = "jmp";
    jump_map["01"] = "jsr";
    jump_map["10"] = "ret";
    return jump_map;
}

// decode stage
std::string decode(std::string inst, const std::map<std::string, std::string> &op_map,
                   const std::map<std::string, std::string> &func_map,
                   const std::map<std::string, std::string> &comp_map,
                   const std::map<std::string, std::string> &jump_map) {
    std::string op = xfind(op_map, inst.substr(0, 6));
    if (op == "operation") {
        std::string func = xfind(func_map, inst.substr(20, 27));
        if (func == "addq") {
            // check if bit 12 is 0, then it's an RR type inst
            if (inst[19] == 0) {
                size_t ra = to_decimal(inst.substr(6, 11));
                size_t rb = to_decimal(inst.substr(11, 16));
                return op + ' ' + func + ' ' + std::to_string(ra) + ' ' +
                       std::to_string(rb);
            }
            else if (inst[19] == 1) {
              // if the bit 12 is 1, then it's an RI type inst
              
            }
        }
        else if (func == "subq") {
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

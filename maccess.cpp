/**
 * Memory access: access an operand in data memory
 */
#include "maccess.h"

#include <string>
#include <vector>
#include <iostream>

#include "utils.h"

// memory stage
// store instruction:
// take in what iexecute returns
// vector be main memory
/// dummy function returns argument
std::vector<std::string> maccess(const std::vector<std::string> &executed, std::byte memory[4096]) {
    if (executed.empty() || executed[0].empty()) return {};
    // std::vector<std::string> ret = executed;
    // return ret;
    std::string op = executed[0];
    std::string address;
    if (op[0] == 'L') {
        std::string dest;
        if (executed.size() > 1) {
            dest = executed[1];
        }
        if (executed.size() > 2) {
            address = executed[2];
        }
        if (op == "LB") {
            // loads an 8-bit value from memory, then sign-extends to 32-bits
            // before storing in rd
            std::string load_mem = bytetostring(memory[xstoui(address) % 4096]);
            if (load_mem[0] == '0') {
                load_mem = "000000000000000000000000" + load_mem;
            } else {
                load_mem = "111111111111111111111111" + load_mem;
            }
            return {"WB", dest, load_mem};
        } else if (op == "LH") {
            // The LH loads a 16-bit value from memory, then sign-extends to
            // 32-bits before storing in rd
            std::string load_mem =
                    bytetostring(memory[xstoui(address) % 4096]) + bytetostring(memory[(xstoui(address) + 1) % 4096]);
            if (load_mem[0] == '0') {
                load_mem = "000000000000000" + load_mem;
            } else {
                load_mem = "111111111111111" + load_mem;
            }
            return {"WB", dest, load_mem};
        } else if (op == "LW") {
            //  The LW instruction loads a 32-bit value from memory into rd
            std::string load_mem =
                    bytetostring(memory[xstoui(address) % 4096]) + bytetostring(memory[(xstoui(address) + 1) % 4096]) +
                    bytetostring(memory[(xstoui(address) + 2) % 4096]) +
                    bytetostring(memory[(xstoui(address) + 3) % 4096]);
            return {"WB", dest, load_mem};
        } else if (op == "LBU") {
            // loads 8-bit values from memory but then zero extends to 32-bits
            // before storing in rd
            std::string load_mem = bytetostring(memory[xstoui(address) % 4096]);
            load_mem = "00000000000000000000000" + load_mem;
            return {"WB", dest, load_mem};
        } else if (op == "LHU") {
            // loads a 16-bit value from memory but then zero extends to 32-bits
            // before storing in rd
            std::string load_mem =
                    bytetostring(memory[xstoui(address) % 4096]) + bytetostring(memory[(xstoui(address) + 1) % 4096]);
            load_mem = "000000000000000" + load_mem;
            return {"WB", dest, load_mem};
        } else if (op[0] == 'S') {
            std::string value;
            if (executed.size() > 1) {
                value = executed[1];
            }
            if (executed.size() > 2) {
                address = executed[2];
            }
            if (op == "SB") {
                // store 8-bit values from the low bits of register rs2 to
                // memory
                memory[stoul(address) % 100] = std::byte(xstoui(value));
                // return {"WB", } nop so register 0 + register 0
            } else if (op == "SH") {
                // store 16-bit values from the low bits of register rs2 to
                // memory
                memory[stoul(address) % 100] = std::byte(xstoui(value.substr(0, 8)));
                memory[(stoul(address) + 1) % 100] = std::byte(xstoui(value.substr(8, 8)));
                // return {"WB", } nop so register 0 + register 0
            } else if (op == "SW") {
                // store 32-bit values from the low bits of register rs2 to
                // memory
                memory[stoul(address) % 100] = std::byte(xstoui(value.substr(0, 8)));
                memory[(stoul(address) + 1) % 100] = std::byte(xstoui(value.substr(8, 8)));
                memory[(stoul(address) + 2) % 100] = std::byte(xstoui(value.substr(16, 8)));
                memory[(stoul(address) + 3) % 100] = std::byte(xstoui(value.substr(24, 8)));
                // return {"WB", } nop so register 0 + register 0
            }
        }
    } else if (op[0] == 'W') {
        return executed;
    }
    return {"FAILURE"};
}

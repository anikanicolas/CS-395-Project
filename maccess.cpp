/**
 * Memory access: access an operand in data memory
 */
#include <string>
#include <vector>

// memory stage
// store instruction:
// take in what iexecute returns
// vector be main memory
/// dummy function returns argument
std::vector<std::string> memory(100, "0");
std::vector<std::string> maccess(const std::vector<std::string> &executed,
const std::vector<std::string> &memory) {
    if (executed.empty() || executed[0].empty()) return {};
    //std::vector<std::string> ret = executed;
    //return ret;
    if (!executed.empty()) {
      std::string mem_addess;
      std::string op;
      std::string dest;
      if (executed.size() > 1) {
        dest = executed[1];
      }
      if (executed.size() > 2) {
        mem_address = executed[2];
      }
      if (executed.size() > 3) {
        op = executed[3];
      }
      if (op == "LB") {
        // loads an 8-bit value from memory, then sign-extends to 32-bits before storing in rd
        std::string load_mem = memory[stoul(mem_address)%100];
        if (load_mem[0] == "0") {
          load_mem = "00000000000000000000000" + load_mem;
        } else {
          load_mem = "11111111111111111111111" + load_mem;
        }
        return {"WB", dest, load_mem};
      } else if (op == "LH") {
        // The LH loads a 16-bit value from memory, then sign-extends to
        // 32-bits before storing in rd
        std::string load_mem = memory[stoul(mem_address)%100];
        if (load_mem[0] == "0") {
          load_mem = "000000000000000" + load_mem;
        } else {
          load_mem = "111111111111111" + load_mem;
        }
        return {"WB", dest, load_mem};
      } else if (op == "LW") {
        //  The LW instruction loads a 32-bit value from memory into rd
        std::string load_mem = memory[stoul(mem_address)%100];
        return {"WB", dest, load_mem};
      } else if (op == "LBU") {
        // loads 8-bit values from memory but then zero extends to 32-bits before storing in rd
        std::string load_mem = memory[stoul(mem_address)%100];
        load_mem = "00000000000000000000000" + load_mem;
        return {"WB", dest, load_mem};
      } else if (op == "LHU") {
          // loads a 16-bit value from memory but then zero extends to 32-bits before storing in rd
          std::string load_mem = memory[stoul(mem_address)%100];
          load_mem = "000000000000000" + load_mem;
          return {"WB", dest, load_mem};
      } else if (op == "SB") {
        // store 8-bit values from the low bits of register rs2 to memory
        memory[stoul(mem_address)%100] = dest;
        //return {"WB", } nop so register 0 + register 0
      } else if (op == "SH") {
        // store 16-bit values from the low bits of register rs2 to memory
        memory[stoul(mem_address)%100] = dest;
        //return {"WB", } nop so register 0 + register 0
      } else if (op == "SW") {
        // store 32-bit values from the low bits of register rs2 to memory
        memory[stoul(mem_address)%100] = dest;
        //return {"WB", } nop so register 0 + register 0
      }
    }
}

/**
 * Instruction Execute: execute the instruction or calculate an address
 */
#include "iexecute.h"

#include <string>
#include <vector>
#include <iostream>

#include "utils.h"

// execute stage [[ unused ]]
/**
 * Execute decoded instruction with decoded registers
 * @param decoded instruction to execute
 * @return executed instruction
 */
std::vector<std::string> iexecute(const std::vector<std::string> &decoded, const uint32_t &pc) {
    if (decoded.empty() || decoded[0].empty()) return {};
    /// execution state to return, FAILURE by default
    std::vector<std::string> ret = {"FAILURE"};
    if (!decoded.empty()) {
        std::string op = decoded[0];
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        if (decoded.size() > 1) {
            arg0 = decoded[1];
        }
        if (decoded.size() > 2) {
            arg1 = decoded[2];
        }
        if (decoded.size() > 3) {
            arg2 = decoded[3];
        }
        if (decoded.size() > 4) {
            arg3 = decoded[4];
        }
        std::vector<std::string> stalling = {"STALL"};
        if (decoded == stalling) {
          return stalling;
        } else {
          if (op == "LUI") {
              /*
               * A LUI instruction can first load arg1 with the upper 20 bits of a
               * target address LUI (load upper immediate) places the 20-bit
               * U-immediate into bits 31–12 of register arg0 and places zero in
               * the lowest 12 bits.
               */
              return {"WB", arg0, arg1 + "000000000000"};
          } else if (op == "AUIPC") {
              return {"WB", arg0, xto_string(xstoui(arg1 + "000000000000") + pc)};
          } else if (op == "JAL") {
              /*
              The offset is sign-extended and added to the pc to form the jump
              target address JAL stores the address of the instruction following
              the jump (pc+4) into register rd
              */
              return {"WB", arg0, xto_string(xstoui(arg1) + pc)};
          } else if (op == "JALR") {
              /*
              The target address is obtained by adding the 12-bit signed
              I-immediate(arg2) to the register rs1(arg1), then setting the
              least-significant bit of the result to zero The address of the
              instruction following the jump (pc+4) is written to register rd
              */
              std::string rs1 = xto_string(xstoui(arg1) + xstoui(arg2));
              size_t lastnum = rs1.length() - 1;
              rs1[lastnum] = 0;
              return {"WB", arg0, "FOO"};

          } else if (op == "BEQ") {
              if (arg0 == arg1) {
                  return {"WB", "pc", xto_string(pc + xstoui(arg2))};
              }
              return {};
          } else if (op == "BNE") {
              if (arg0 != arg1) {
                  return {"WB", "pc", xto_string(pc + xstoui(arg2))};
              }
              return {};
          } else if (op == "BLT") {
              // signed version of BLTU
              if (xstoi(arg0) < xstoi(arg1)) {
                  return {"WB", arg0, xto_string(pc + xstoui(arg2))};
              }
              return {};
          } else if (op == "BGE") {
              // signed version of BGEU
              if (xstoi(arg0) >= xstoi(arg1)) {
                  return {"WB", arg0, xto_string(pc + xstoui(arg2))};
              }
              return {};
          } else if (op == "BLTU") {
              if (xstoui(arg0) < xstoui(arg1)) {
                  return {"WB", arg0, xto_string(pc + xstoui(arg2))};
              }
              return {};
          } else if (op == "BGEU") {
              if (xstoui(arg0) >= xstoui(arg1)) {
                  return {"WB", arg0, xto_string(pc + xstoui(arg2))};
              }
              return {};
          } else if (op == "LB") {
              // loads an 8-bit value from memory, then sign-extends to 32-bits
              // before storing in rd
              return {"LB", arg0, xto_string(xstoui(arg1) + xstoui(arg2))};
          } else if (op == "LH") {
              // The LH loads a 16-bit value from memory, then sign-extends to
              // 32-bits before storing in rd
              return {"LH", arg0, xto_string(xstoui(arg1) + xstoui(arg2))};
          } else if (op == "LW") {
              //  The LW instruction loads a 32-bit value from memory into rd
              return {"LW", arg0, xto_string(xstoui(arg1) + xstoui(arg2))};

          } else if (op == "LBU") {
              // loads 8-bit values from memory but then zero extends to 32-bits
              // before storing in rd
              return {"LBU", arg0, std::to_string(stoul(arg2) + stoul(arg2))};
          } else if (op == "LHU") {
              // loads a 16-bit value from memory but then zero extends to 32-bits
              // before storing in rd
              return {"LHU", arg0, std::to_string(stoul(arg2) + stoul(arg2))};
          } else if (op == "SB") {
              // store 8-bit values from the low bits of register rs2 to memory
              return {"SB", arg1.substr(24, 8), std::to_string(stoul(arg0) + stoul(arg2))};
          } else if (op == "SH") {
              // store 16-bit values from the low bits of register rs2 to memory
              return {"SH", arg2.substr(16, 16), std::to_string(stoul(arg0) + stoul(arg2))};
          } else if (op == "SW") {
              // store 32-bit values from the low bits of register rs2 to memory
              return {"SW", arg2, std::to_string(stoul(arg0) + stoul(arg2))};
          } else if (op == "ADDI") {
            //may stall for loads
          } else if (op == "SLTI") {
          } else if (op == "SLTIU") {
          } else if (op == "XORI") {
          } else if (op == "ORI") {
          } else if (op == "ANDI") {
          } else if (op == "SLLI") {
          } else if (op == "SRLI") {
          } else if (op == "SRAI") {
          } else if (op == "ADD") {
              // ADD performs the addition of arg1 and arg2
              return {"WB", arg0, sxto_string(xstoi(arg1) + xstoi(arg2))};
          } else if (op == "SUB") {
              // SUB performs the subtraction of arg2 from arg1
              return {"WB", arg0, sxto_string(xstoi(arg1) - xstoi(arg2))};
              /*
               * (add upper immediate to pc) is used to build pc-relative
               * addresses and uses the U-type format. AUIPC forms a 32-bit offset
               * from the 20-bit U-immediate, filling in the lowest 12 bits with
               * zeros, adds this offset to the pc, then places the result in
               * register rd.
               */
          } else if (op == "SLL") {
          } else if (op == "SLT") {
              /*
               * SLT and SLTU
               * perform signed and unsigned compares respectively, writing 1 to
               * rd if rs1 < rs2, 0 otherwise. Note, SLTU rd, x0, rs2 sets rd to 1
               * if rs2 is not equal to zero, otherwise sets rd to zero (assembler
               * pseudoinstruction SNEZ rd, rs).
               */
              return {"WB", arg0, xto_string(xstoi(arg1) < xstoi(arg2))};
          } else if (op == "SLTU") {
              return {"WB", arg0, xto_string(xstoui(arg1) < xstoui(arg2))};
          } else if (op == "XOR") {
              return {"WB", arg0, xto_string(xstoui(arg1) ^ xstoui(arg2))};
          } else if (op == "SRL") {
              return {"WB", arg0, xto_string(xstoui(arg1) >> xstoui(arg2))};
          } else if (op == "SRA") {
              return {"WB", arg0, xto_string(xstoui(arg1) << xstoui(arg2))};
          } else if (op == "OR") {
              return {"WB", arg0, xto_string(xstoui(arg1) | xstoui(arg2))};
          } else if (op == "AND") {
              return {"WB", arg0, xto_string(xstoui(arg1) & xstoui(arg2))};
          } else if (op == "FENCE") {
              return {"FENCE"};
          } else if (op == "ECALL") {
              // service request to environment
              return {"PRINT"};
          } else if (op == "EBREAK") {
              // cause execution to stop and return to environment
              exit(EXIT_SUCCESS);
          }
        }

    }
    return ret;
}

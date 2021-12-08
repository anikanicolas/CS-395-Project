/**
 * Instruction Execute: execute the instruction or calculate an address
 */
#include <string>
#include <vector>
//for reverse string
#include<bits/stdc++.h>

// execute stage [[ unused ]]
/**
 * Execute decoded instruction with fetched registers
 * @param decoded instruction to execute
 * @return executed instruction
 */
std::vector<std::string> iexecute(const std::vector<std::string> &decoded, const size_t &pc) {
    if (decoded.empty() || decoded[0].empty()) return {};
    /// execution state to return, FAILURE by default
    std::vector<std::string> ret = {"FAILURE"};
    if (!decoded.empty()) {
        std::string op = decoded[0];
        std::string dest;
        std::string src1;
        std::string src2;
        std::string src3;
        if (decoded.size() > 1) {
            dest = decoded[1];
        }
        if (decoded.size() > 2) {
            src1 = decoded[2];
        }
        if (decoded.size() > 3) {
            src2 = decoded[3];
        }
        if (decoded.size() > 4) {
            src3 = decoded[4];
        }
        if (op == "LUI") {
            /*
             * A LUI instruction can first load src1 with the upper 20 bits of a
             * target address LUI (load upper immediate) places the 20-bit
             * U-immediate into bits 31–12 of register dest and places zero in
             * the lowest 12 bits.
             */
            return {"WB", dest, 'b' + src1 + "000000000000"};
        } else if (op == "AUIPC") {
            return {"WB", dest, std::to_string(stoul(src1 + "000000000000") + pc)};
        } else if (op == "JAL") {
            /*
            The offset is sign-extended and added to the pc to form the jump
            target address JAL stores the address of the instruction following
            the jump (pc+4) into register rd
            */
            return {"WB", dest, std::to_string(stoul(src1) + pc)};
        } else if (op == "JALR") {
            /*
            The target address is obtained by adding the 12-bit signed
            I-immediate(src2) to the register rs1(src1), then setting the
            least-significant bit of the result to zero The address of the
            instruction following the jump (pc+4) is written to register rd
            */
            std::string rs1 = std::to_string(stoul(src1) + stoul(src2));
            size_t lastnum = rs1.length() - 1;
            rs1[lastnum] = 0;
            return {"WB", dest, "FOO"};

        } else if (op == "BEQ") {
            if (src1 == src2) {
                return {"WB", dest, std::to_string(pc + stoul(src3) + stoul(dest))};
            }
            return {};
        } else if (op == "BNE") {
            if (src1 != src2) {
                return {"WB", dest, std::to_string(pc + stoul(src3) + stoul(dest))};
            }
            return {};
        } else if (op == "BLT") {
            // signed version of BLTU
        } else if (op == "BGE") {
            // signed version of BGEU
        } else if (op == "BLTU") {
            if (stoul(src1) < stoul(src2)) {
                return {"WB", dest, std::to_string(pc + stoul(src3) + stoul(dest))};
            }
            return {};
        } else if (op == "BGEU") {
            if (stoul(src1) >= stoul(src2)) {
                return {"WB", dest, std::to_string(pc + stoul(src3) + stoul(dest))};
            }
            return {};
        } else if (op == "LB") {
          // loads an 8-bit value from memory, then sign-extends to 32-bits before storing in rd
            return {"MEM", dest, std::to_string(stoul(src2) + stoul(src3)), "LB"};
        } else if (op == "LH") {
            // The LH loads a 16-bit value from memory, then sign-extends to
            // 32-bits before storing in rd
            return {"MEM", dest, std::to_string(stoul(src2) + stoul(src3)), "LH"};
        } else if (op == "LW") {
            //  The LW instruction loads a 32-bit value from memory into rd
            return {"MEM", dest, std::to_string(stoul(src2) + stoul(src2)), "LW"};

        } else if (op == "LBU") {
          // loads 8-bit values from memory but then zero extends to 32-bits before storing in rd
            return {"MEM", dest, std::to_string(stoul(src2) + stoul(src2)), "LBU"};
        } else if (op == "LHU") {
          // loads a 16-bit value from memory but then zero extends to 32-bits before storing in rd
            return {"MEM", dest, std::to_string(stoul(src2) + stoul(src2)), "LHU"};
        } else if (op == "SB") {
          // store 8-bit values from the low bits of register rs2 to memory
          reverse(src2.begin(), src2.end())
          return {"MEM", isubstr(src2, 0, 8), std::to_string(stoul(dest)+stoul(src1)+stoul(src3)), "SB"};
        } else if (op == "SH") {
          // store 16-bit values from the low bits of register rs2 to memory
          reverse(src2.begin(), src2.end())
          return {"MEM", isubstr(src2, 0, 16), std::to_string(stoul(dest)+stoul(src1)+stoul(src3)), "SH"};
        } else if (op == "SW") {
          // store 32-bit values from the low bits of register rs2 to memory
          return {"MEM", src2, std::to_string(stoul(dest)+stoul(src1)+stoul(src3)), "SW"};
        } else if (op == "ADDI") {
        } else if (op == "SLTI") {
        } else if (op == "SLTIU") {
        } else if (op == "XORI") {
        } else if (op == "ORI") {
        } else if (op == "ANDI") {
        } else if (op == "SLLI") {
        } else if (op == "SRLI") {
        } else if (op == "SRAI") {
        } else if (op == "ADD") {
            // ADD performs the addition of src1 and src2
            return {"WB", dest, std::to_string(stoul(src1) + stoul(src2))};
        } else if (op == "SUB") {
            // SUB performs the subtraction of src2 from src1
            return {"WB", dest, std::to_string(stoul(src1) - stoul(src2))};
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
            return {"WB", dest, std::to_string(stol(src1) < stol(src2))};
        } else if (op == "SLTU") {
            return {"WB", dest, std::to_string(stoul(src1) < stoul(src2))};
        } else if (op == "XOR") {
            return {"WB", dest, std::to_string(stoul(src1) ^ stoul(src2))};
        } else if (op == "SRL") {
            return {"WB", dest, std::to_string(stoul(src1) >> stoul(src2))};
        } else if (op == "SRA") {
            return {"WB", dest, std::to_string(stoul(src1) << stoul(src2))};
        } else if (op == "OR") {
            return {"WB", dest, std::to_string(stoul(src1) | stoul(src2))};
        } else if (op == "AND") {
            return {"WB", dest, std::to_string(stoul(src1) & stoul(src2))};
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
    return ret;
}

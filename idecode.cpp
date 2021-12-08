/**
 * Instruction decode: decode the instruction
 */
#include "idecode.h"

#include <algorithm>
#include <string>
#include <vector>

#include "utils.h"

/**
 * Get substring of instruction (first bit of instruction is 31, last bit is 0)
 * @param instruction to get substring of
 * @param start first bit to read
 * @param end last bit to read
 * @return substring of instruction from start to end (inclusive)
 */
std::string isubstr(const std::string &instruction, const size_t &end, const size_t &start) {
    return instruction.substr(31 - end, end - start + 1);
}

/**
 * Decode inst
 * @param inst to decode
 * @return vector of words representing decoded inst
 */
std::vector<std::string> idecode(const std::string &inst) {
    if (inst.empty()) return {};
    std::string opcode = isubstr(inst, 6, 0);
    std::string rd = isubstr(inst, 11, 7);
    std::string funct3 = isubstr(inst, 14, 12);
    std::string rs1 = isubstr(inst, 19, 15);
    std::string rs2 = isubstr(inst, 24, 20);
    std::string funct7 = isubstr(inst, 31, 25);
    std::string imm11_0 = isubstr(inst, 31, 20);
    std::string imm31_12 = isubstr(inst, 31, 12);
    std::string imm12_10_5_4_1_11 =
            isubstr(inst, 31, 31) + isubstr(inst, 7, 7) + isubstr(inst, 30, 25) + isubstr(inst, 11, 8);
    std::string imm20_10_1_11_19_12 =
            isubstr(inst, 31, 31) + isubstr(inst, 19, 12) + isubstr(inst, 20, 20) + isubstr(inst, 30, 21);
    std::string imm11_5_4_0 = funct7 + rd;
    std::string fm = isubstr(inst, 31, 28);
    std::string pred = isubstr(inst, 27, 24);
    std::string succ = isubstr(inst, 23, 20);
    const std::string &shamt = rs2;
    std::string dest = 'd' + to_decimal(rd);
    std::string src1 = 's' + to_decimal(rs1);
    std::string src2 = 's' + to_decimal(rs2);

    if (opcode == "0110111") {
        return {"LUI", dest, imm31_12};
    } else if (opcode == "0010111") {
        return {"AUIPC", dest, imm31_12};
    } else if (opcode == "1101111") {
        return {"JAL", dest, src1, imm20_10_1_11_19_12};
    } else if (opcode == "1100111") {
        if (funct3 == "000") {
            return {"JALR", dest, src1, imm11_0};
        }
    } else if (opcode == "1100011") {
        if (funct3 == "000") {
            return {"BEQ", src1, src2, imm12_10_5_4_1_11};
        } else if (funct3 == "001") {
            return {"BNE", src1, src2, imm12_10_5_4_1_11};
        } else if (funct3 == "100") {
            return {"BLT", src1, src2, imm12_10_5_4_1_11};
        } else if (funct3 == "101") {
            return {"BGE", src1, src2, imm12_10_5_4_1_11};
        } else if (funct3 == "110") {
            return {"BLTU", src1, src2, imm12_10_5_4_1_11};
        } else if (funct3 == "111") {
            return {"BGEU", src1, src2, imm12_10_5_4_1_11};
        }
    } else if (opcode == "0000011") {
        if (funct3 == "000") {
            return {"LB", dest, src1, imm11_0};
        } else if (funct3 == "001") {
            return {"LH", dest, src1, imm11_0};
        } else if (funct3 == "010") {
            return {"LW", dest, src1, imm11_0};
        } else if (funct3 == "100") {
            return {"LBU", dest, src1, imm11_0};
        } else if (funct3 == "101") {
            return {"LHU", dest, src1, imm11_0};
        }
    } else if (opcode == "0100011") {
        if (funct3 == "000") {
            return {"SB", src1, src2, imm11_5_4_0};
        } else if (funct3 == "001") {
            return {"SH", src1, src2, imm11_5_4_0};
        } else if (funct3 == "010") {
            return {"SW", src1, src2, imm11_5_4_0};
        }
    } else if (opcode == "0010011") {
        if (funct3 == "000") {
            return {"ADDI", dest, src1, imm11_0};
        } else if (funct3 == "010") {
            return {"SLTI", dest, src1, imm11_0};
        } else if (funct3 == "011") {
            return {"SLTIU", dest, src1, imm11_0};
        } else if (funct3 == "100") {
            return {"XORI", dest, src1, imm11_0};
        } else if (funct3 == "110") {
            return {"ORI", dest, src1, imm11_0};
        } else if (funct3 == "111") {
            return {"ANDI", dest, src1, imm11_0};
        } else if (funct3 == "001") {
            if (funct7 == "0000000") {
                return {"SLLI", dest, src1, shamt};
            }
        } else if (funct3 == "101") {
            if (funct7 == "0000000") {
                return {"SRLI", dest, src1, shamt};
            } else if (funct7 == "0100000") {
                return {"SRAI", dest, src1, shamt};
            }
        }
    } else if (opcode == "0110011") {
        if (funct3 == "000") {
            if (funct7 == "0000000") {
                return {"ADD", dest, src1, src2};
            } else if (funct7 == "0100000") {
                return {"SUB", dest, src1, src2};
            }
        } else if (funct3 == "001") {
            if (funct7 == "0000000") {
                return {"SLL", dest, src1, src2};
            }
        } else if (funct3 == "010") {
            if (funct7 == "0000000") {
                return {"SLT", dest, src1, src2};
            }
        } else if (funct3 == "011") {
            if (funct7 == "0000000") {
                return {"SLTU", dest, src1, src2};
            }
        } else if (funct3 == "100") {
            if (funct7 == "0000000") {
                return {"XOR", dest, src1, src2};
            }
        } else if (funct3 == "101") {
            if (funct7 == "0000000") {
                return {"SRL", dest, src1, src2};
            } else if (funct7 == "0100000") {
                return {"SRA", dest, src1, src2};
            }
        } else if (funct3 == "110") {
            if (funct7 == "0000000") {
                return {"OR", dest, src1, src2};
            }
        } else if (funct3 == "111") {
            if (funct7 == "0000000") {
                return {"AND", dest, src1, src2};
            }
        }
    } else if (opcode == "0001111") {
        if (funct3 == "000") {
            return {"FENCE", dest, src1, succ, pred, fm};
        }
    } else if (opcode == "1110011") {
        if (funct3 == "000") {
            if (imm11_0 == "000000000000") {
                return {"ECALL"};
            } else if (imm11_0 == "000000000001") {
                return {"EBREAK"};
            }
        }
    }
    return {"FAILURE"};
}

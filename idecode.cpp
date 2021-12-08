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
    std::vector<std::string> ret = {"FAILURE"};

    if (opcode == "0110111") {
        ret = {"LUI", dest, imm31_12};
    } else if (opcode == "0010111") {
        ret = {"AUIPC", dest, imm31_12};
    } else if (opcode == "1101111") {
        ret = {"JAL", dest, src1, imm20_10_1_11_19_12};
    } else if (opcode == "1100111") {
        if (funct3 == "000") {
            ret = {"JALR", dest, src1, imm11_0};
        }
    } else if (opcode == "1100011") {
        if (funct3 == "000") {
            ret = {"BEQ", src1, src2, imm12_10_5_4_1_11};
        } else if (funct3 == "001") {
            ret = {"BNE", src1, src2, imm12_10_5_4_1_11};
        } else if (funct3 == "100") {
            ret = {"BLT", src1, src2, imm12_10_5_4_1_11};
        } else if (funct3 == "101") {
            ret = {"BGE", src1, src2, imm12_10_5_4_1_11};
        } else if (funct3 == "110") {
            ret = {"BLTU", src1, src2, imm12_10_5_4_1_11};
        } else if (funct3 == "111") {
            ret = {"BGEU", src1, src2, imm12_10_5_4_1_11};
        }
    } else if (opcode == "0000011") {
        if (funct3 == "000") {
            ret = {"LB", dest, src1, imm11_0};
        } else if (funct3 == "001") {
            ret = {"LH", dest, src1, imm11_0};
        } else if (funct3 == "010") {
            ret = {"LW", dest, src1, imm11_0};
        } else if (funct3 == "100") {
            ret = {"LBU", dest, src1, imm11_0};
        } else if (funct3 == "101") {
            ret = {"LHU", dest, src1, imm11_0};
        }
    } else if (opcode == "0100011") {
        if (funct3 == "000") {
            ret = {"SB", src1, src2, imm11_5_4_0};
        } else if (funct3 == "001") {
            ret = {"SH", src1, src2, imm11_5_4_0};
        } else if (funct3 == "010") {
            ret = {"SW", src1, src2, imm11_5_4_0};
        }
    } else if (opcode == "0010011") {
        if (funct3 == "000") {
            ret = {"ADDI", dest, src1, imm11_0};
        } else if (funct3 == "010") {
            ret = {"SLTI", dest, src1, imm11_0};
        } else if (funct3 == "011") {
            ret = {"SLTIU", dest, src1, imm11_0};
        } else if (funct3 == "100") {
            ret = {"XORI", dest, src1, imm11_0};
        } else if (funct3 == "110") {
            ret = {"ORI", dest, src1, imm11_0};
        } else if (funct3 == "111") {
            ret = {"ANDI", dest, src1, imm11_0};
        } else if (funct3 == "001") {
            if (funct7 == "0000000") {
                ret = {"SLLI", dest, src1, shamt};
            }
        } else if (funct3 == "101") {
            if (funct7 == "0000000") {
                ret = {"SRLI", dest, src1, shamt};
            } else if (funct7 == "0100000") {
                ret = {"SRAI", dest, src1, shamt};
            }
        }
    } else if (opcode == "0110011") {
        if (funct3 == "000") {
            if (funct7 == "0000000") {
                ret = {"ADD", dest, src1, src2};
            } else if (funct7 == "0100000") {
                ret = {"SUB", dest, src1, src2};
            }
        } else if (funct3 == "001") {
            if (funct7 == "0000000") {
                ret = {"SLL", dest, src1, src2};
            }
        } else if (funct3 == "010") {
            if (funct7 == "0000000") {
                ret = {"SLT", dest, src1, src2};
            }
        } else if (funct3 == "011") {
            if (funct7 == "0000000") {
                ret = {"SLTU", dest, src1, src2};
            }
        } else if (funct3 == "100") {
            if (funct7 == "0000000") {
                ret = {"XOR", dest, src1, src2};
            }
        } else if (funct3 == "101") {
            if (funct7 == "0000000") {
                ret = {"SRL", dest, src1, src2};
            } else if (funct7 == "0100000") {
                ret = {"SRA", dest, src1, src2};
            }
        } else if (funct3 == "110") {
            if (funct7 == "0000000") {
                ret = {"OR", dest, src1, src2};
            }
        } else if (funct3 == "111") {
            if (funct7 == "0000000") {
                ret = {"AND", dest, src1, src2};
            }
        }
    } else if (opcode == "0001111") {
        if (funct3 == "000") {
            ret = {"FENCE", dest, src1, succ, pred, fm};
        }
    } else if (opcode == "1110011") {
        if (funct3 == "000") {
            if (imm11_0 == "000000000000") {
                ret = {"ECALL"};
            } else if (imm11_0 == "000000000001") {
                ret = {"EBREAK"};
            }
        }
    }

    return ret;
}

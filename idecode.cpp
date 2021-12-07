/**
 * Instruction decode: decode the instruction
 */
#include <algorithm>
#include <string>
#include <vector>

/**
 * Convert binary string to decimal string
 * @param binary string to convert
 * @return decimal string
 */
std::string to_decimal(const std::string &binary) {
    return std::to_string(stoul(binary, nullptr, 2));
}

/**
 * Get substring of instruction (first bit of instruction is 31, last bit is 0)
 * @param instruction to get substring of
 * @param start first bit to read
 * @param end last bit to read
 * @return substring of instruction from start to end (not including end)
 */
std::string isubstr(const std::string &instruction, const size_t &start,
                    const size_t &end) {
    return instruction.substr(32 - end, end - start);
}

/**
 * Decode instruction
 * @param instruction to decode
 * @return vector of words representing decoded instruction
 */
std::vector<std::string> idecode(const std::string &instruction) {
    if (instruction.empty()) return {};
    std::string opcode = isubstr(instruction, 0, 7);
    std::string rd = isubstr(instruction, 7, 12);
    std::string funct3 = isubstr(instruction, 12, 15);
    std::string rs1 = isubstr(instruction, 15, 20);
    std::string rs2 = isubstr(instruction, 20, 25);
    std::string funct7 = isubstr(instruction, 25, 32);
    std::string imm11_0 = isubstr(instruction, 20, 32);
    std::string imm31_12 = isubstr(instruction, 12, 32);
    const std::string &imm4_0 = rd;
    const std::string &imm11_5 = funct7;
    const std::string &shamt = rs2;
    std::string dest = 'd' + to_decimal(rd);
    std::string src1 = 's' + to_decimal(rs1);
    std::string src2 = 's' + to_decimal(rs2);

    if (opcode == "0110111") {
        return {"LUI", dest, imm31_12};
    } else if (opcode == "0010111") {
        return {"AUIPC", dest, imm31_12};
    } else if (opcode == "1101111") {
        return {"JAL", dest, imm31_12};
    } else if (opcode == "1100111") {
        if (funct3 == "000") {
            return {"JALR", dest, src1, imm11_0};
        }
    } else if (opcode == "1100011") {
        if (funct3 == "000") {
            return {"BEQ", imm4_0, src1, src2, imm11_5};
        } else if (funct3 == "001") {
            return {"BNE", imm4_0, src1, src2, imm11_5};
        } else if (funct3 == "100") {
            return {"BLT", imm4_0, src1, src2, imm11_5};
        } else if (funct3 == "101") {
            return {"BGE", imm4_0, src1, src2, imm11_5};
        } else if (funct3 == "110") {
            return {"BLTU", imm4_0, src1, src2, imm11_5};
        } else if (funct3 == "111") {
            return {"BGEU", imm4_0, src1, src2, imm11_5};
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
            return {"SB", imm4_0, src1, src2, imm11_5};
        } else if (funct3 == "001") {
            return {"SH", imm4_0, src1, src2, imm11_5};
        } else if (funct3 == "010") {
            return {"SW", imm4_0, src1, src2, imm11_5};
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
            return {"FENCE", dest, src1, imm11_0};
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

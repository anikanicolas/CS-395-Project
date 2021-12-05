/**
 * Instruction decode and register fetch
 * Read registers and decode the instruction
 */
#include <string>

// convert binary string to binary integer
std::string to_decimal(const std::string &binary) {
    return std::to_string(stoul(binary, nullptr, 2));
}

std::string instruction_decode(const std::string &instruction) {
    std::string opcode = instruction.substr(0, 7);
    std::string rd = instruction.substr(7, 12);
    std::string rd_decimal = to_decimal(rd);
    std::string funct3 = instruction.substr(12, 15);
    std::string rs1 = instruction.substr(15, 20);
    std::string rs1_decimal = to_decimal(rs1);
    std::string rs2 = instruction.substr(20, 25);
    std::string rs2_decimal = to_decimal(rs2);
    std::string funct7 = instruction.substr(25, 32);
    std::string funct7_decimal = to_decimal(funct7);
    std::string imm11_0 = instruction.substr(20, 32);
    std::string imm31_12 = instruction.substr(12, 32);

    if (opcode == "0110111") {
        return "LUI  " + rd_decimal + " " + imm31_12;
    } else if (opcode == "0010111") {
        return "AUIPC " + rd_decimal + " " + imm31_12;
    } else if (opcode == "1101111") {
        return "JAL " + rd_decimal + " " + imm31_12;
    } else if (opcode == "1100111") {
        if (funct3 == "000") {
            return "JALR " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        }
    } else if (opcode == "1100011") {
        if (funct3 == "000") {
            return "BEQ " + rd + " " + rs1_decimal + " " + rs2_decimal + " " + funct7;
        } else if (funct3 == "001") {
            return "BNE " + rd + " " + rs1_decimal + " " + rs2_decimal + " " + funct7;
        } else if (funct3 == "100") {
            return "BLT " + rd + " " + rs1_decimal + " " + rs2_decimal + " " + funct7;
        } else if (funct3 == "101") {
            return "BGE " + rd + " " + rs1_decimal + " " + rs2_decimal + " " + funct7;
        } else if (funct3 == "110") {
            return "BLTU " + rd + " " + rs1_decimal + " " + rs2_decimal + " " + funct7;
        } else if (funct3 == "111") {
            return "BGEU " + rd + " " + rs1_decimal + " " + rs2_decimal + " " + funct7;
        }
    } else if (opcode == "0000011") {
        if (funct3 == "000") {
            return "LB " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "001") {
            return "LH " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "010") {
            return "LW " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "100") {
            return "LBU " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "101") {
            return "LHU " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        }
    } else if (opcode == "0100011") {
        if (funct3 == "000") {
            return "SB " + rd + " " + rs1_decimal + " " + rs2_decimal + " " + funct7;
        } else if (funct3 == "001") {
            return "SH " + rd + " " + rs1_decimal + " " + rs2_decimal + " " + funct7;
        } else if (funct3 == "010") {
            return "SW " + rd + " " + rs1_decimal + " " + rs2_decimal + " " + funct7;
        }
    } else if (opcode == "0010011") {
        if (funct3 == "000") {
            return "ADDI " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "010") {
            return "SLTI " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "011") {
            return "SLTIU " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "100") {
            return "XORI " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "110") {
            return "ORI " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "111") {
            return "ANDI " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "001") {
            if (funct7 == "0000000") {
                return "SLLI " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            }
        } else if (funct3 == "101") {
            if (funct7 == "0000000") {
                return "SRLI " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            } else if (funct7 == "0100000") {
                return "SRAI " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            }
        }
    } else if (opcode == "0110011") {
        if (funct3 == "000") {
            if (funct7 == "0000000") {
                return "ADD " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            } else if (funct7 == "0100000") {
                return "SUB " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            }
        } else if (funct3 == "001") {
            if (funct7 == "0000000") {
                return "SLL " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            }
        } else if (funct3 == "010") {
            if (funct7 == "0000000") {
                return "SLT " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            }
        } else if (funct3 == "011") {
            if (funct7 == "0000000") {
                return "SLTU " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            }
        } else if (funct3 == "100") {
            if (funct7 == "0000000") {
                return "XOR " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            }
        } else if (funct3 == "101") {
            if (funct7 == "0000000") {
                return "SRL " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            } else if (funct7 == "0100000") {
                return "SRA " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            }
        } else if (funct3 == "110") {
            if (funct7 == "0000000") {
                return "OR " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            }
        } else if (funct3 == "111") {
            if (funct7 == "0000000") {
                return "AND " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal;
            }
        }
    } else if (opcode == "0001111") {
        if (funct3 == "000") {
            return "FENCE";
        } else if (funct3 == "001") {
            return "FENCE.I";
        }
    } else if (opcode == "1110011") {
        if (funct3 == "000") {
            if (imm11_0 == "000000000000") {
                return "ECALL";
            } else if (imm11_0 == "000000000001") {
                return "EBREAK";
            }
        } else if (funct3 == "001") {
            return "CSRRW " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "010") {
            return "CSRRS " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "011") {
            return "CSRRC " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "101") {
            return "CSRRWI " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "110") {
            return "CSRRSI " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        } else if (funct3 == "111") {
            return "CSRRCI " + rd_decimal + " " + rs1_decimal + " " + imm11_0;
        }
    }
}

std::string register_fetch(const std::string &instruction) {
}
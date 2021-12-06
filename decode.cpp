/**
 * Instruction decode and register fetch
 * Read registers and decode the instruction
 * Reference:
 * https://github.com/riscv/riscv-isa-manual/releases/download/Ratified-IMAFDQC/riscv-spec-20191213.pdf
 */
#include <string>
#include <iostream>
#include <algorithm>

// convert binary string to binary integer
std::string to_decimal(const std::string &binary) {
    return std::to_string(stoul(binary, nullptr, 2));
}

std::string xsubstr(const std::string &instruction, size_t start, size_t end) {
    return instruction.substr(32 - end, end - start);
}

std::string instruction_decode(const std::string &instruction) {
    std::string opcode = xsubstr(instruction, 0, 7);
    std::string rd = xsubstr(instruction, 7, 12);
    std::string funct3 = xsubstr(instruction, 12, 15);
    std::string rs1 = xsubstr(instruction, 15, 20);
    std::string rs2 = xsubstr(instruction, 20, 25);
    std::string funct7 = xsubstr(instruction, 25, 32);
    std::string imm11_0 = xsubstr(instruction, 20, 32);
    std::string imm31_12 = xsubstr(instruction, 12, 32);
    std::string rd_decimal = to_decimal(rd);
    std::string rs1_decimal = to_decimal(rs1);
    std::string rs2_decimal = to_decimal(rs2);
    std::string funct7_decimal = to_decimal(funct7);
    std::string imm11_0_decimal = to_decimal(imm11_0);
    std::string imm31_12_decimal = to_decimal(imm31_12);


    if (opcode == "0110111") {
        return "LUI " + rd_decimal + " " + imm31_12_decimal;
    } else if (opcode == "0010111") {
        return "AUIPC " + rd_decimal + " " + imm31_12_decimal;
    } else if (opcode == "1101111") {
        return "JAL " + rd_decimal + " " + imm31_12_decimal;
    } else if (opcode == "1100111") {
        if (funct3 == "000") {
            return "JALR " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        }
    } else if (opcode == "1100011") {
        if (funct3 == "000") {
            return "BEQ " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal + " " + funct7_decimal;
        } else if (funct3 == "001") {
            return "BNE " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal + " " + funct7_decimal;
        } else if (funct3 == "100") {
            return "BLT " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal + " " + funct7_decimal;
        } else if (funct3 == "101") {
            return "BGE " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal + " " + funct7_decimal;
        } else if (funct3 == "110") {
            return "BLTU " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal + " " + funct7_decimal;
        } else if (funct3 == "111") {
            return "BGEU " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal + " " + funct7_decimal;
        }
    } else if (opcode == "0000011") {
        if (funct3 == "000") {
            return "LB " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        } else if (funct3 == "001") {
            return "LH " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        } else if (funct3 == "010") {
            return "LW " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        } else if (funct3 == "100") {
            return "LBU " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        } else if (funct3 == "101") {
            return "LHU " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        }
    } else if (opcode == "0100011") {
        if (funct3 == "000") {
            return "SB " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal + " " + funct7_decimal;
        } else if (funct3 == "001") {
            return "SH " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal + " " + funct7_decimal;
        } else if (funct3 == "010") {
            return "SW " + rd_decimal + " " + rs1_decimal + " " + rs2_decimal + " " + funct7_decimal;
        }
    } else if (opcode == "0010011") {
        if (funct3 == "000") {
            return "ADDI " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        } else if (funct3 == "010") {
            return "SLTI " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        } else if (funct3 == "011") {
            return "SLTIU " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        } else if (funct3 == "100") {
            return "XORI " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        } else if (funct3 == "110") {
            return "ORI " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        } else if (funct3 == "111") {
            return "ANDI " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
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
            return "FENCE " + rd_decimal + " " + rs1_decimal + " " + imm11_0_decimal;
        }
    } else if (opcode == "1110011") {
        if (funct3 == "000") {
            if (imm11_0 == "000000000000") {
                return "ECALL";
            } else if (imm11_0 == "000000000001") {
                return "EBREAK";
            }
        }
    }
    return "FAILURE";
}

std::string register_fetch(const std::string &instruction) {
}
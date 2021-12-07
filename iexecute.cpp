/**
 * Instruction Execute: execute the instruction or calculate an address
 */
#include <string>
#include <vector>

// execute stage [[ unused ]]
/**
 * Execute decoded instruction with fetched registers
 * @param decoded instruction to execute
 * @return executed instruction
 */
std::vector<std::string> iexecute(const std::vector<std::string> &decoded) {
    /// execution state to return, FAILURE by default
    std::vector<std::string> ret = {"FAILURE"};
    if (!decoded.empty()) {
        std::string op = decoded[0];
        std::string dest;
        std::string src1;
        std::string src2;
        if (decoded.size() > 1) {
            dest = decoded[1];
        }
        if (decoded.size() > 2) {
            src1 = decoded[2];
        }
        if (decoded.size() > 3) {
            src2 = decoded[3];
        }
        if (op == "LUI") {
            /*
             * A LUI instruction can first load src1 with the upper 20 bits of a target address
             * LUI (load upper immediate) places the 20-bit U-immediate into bits 31–12 of register dest
             * and places zero in the lowest 12 bits.
             */
            ret = {"WB", dest, "0b"};
        } else if (op == "ADD") {
            // ADD performs the addition of src1 and src2
            ret = {"WB", dest, std::to_string(stoul(src1) + stoul(src2))};
        } else if (op == "SUB") {
            // SUB performs the subtraction of src2 from src1
            ret = {"WB", dest, std::to_string(stoul(src1) - stoul(src2))};
            /*
             * (add upper immediate to pc) is used to build pc-relative addresses and uses the
             * U-type format. AUIPC forms a 32-bit offset from the 20-bit U-immediate, filling
             * in the lowest 12 bits with zeros, adds this offset to the pc, then places the
             * result in register rd.
             */
        } else if (op == "AUIPC") {

        } else if (op == "JAL") {

        } else if (op == "JALR") {

        } else if (op == "BEQ") {

        } else if (op == "BNE") {

        } else if (op == "BLT") {

        } else if (op == "BGE") {

        } else if (op == "BLTU") {

        } else if (op == "BGEU") {

        } else if (op == "LB") {

        } else if (op == "LH") {

        } else if (op == "LW") {

        } else if (op == "LBU") {

        } else if (op == "LHU") {

        } else if (op == "SB") {

        } else if (op == "SH") {

        } else if (op == "SW") {

        } else if (op == "ADDI") {

        } else if (op == "SLTI") {

        } else if (op == "SLTIU") {

        } else if (op == "XORI") {

        } else if (op == "ORI") {

        } else if (op == "ANDI") {

        } else if (op == "SLLI") {

        } else if (op == "SRLI") {

        } else if (op == "SRAI") {

        } else if (op == "SLL") {

        } else if (op == "SLT") {

        } else if (op == "SLTU") {

        } else if (op == "XOR") {

        } else if (op == "SRL") {

        } else if (op == "SRA") {

        } else if (op == "OR") {

        } else if (op == "AND") {

        } else if (op == "FENCE") {

        } else if (op == "ECALL") {

        } else if (op == "EBREAK") {

        }
    }
    return ret;
}

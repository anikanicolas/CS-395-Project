#include <cmath>
#include <iostream>
#include <map>
#include <string>

// set instruction

std::map<std::string, std::string> opCodes;
opCodes["010000"] = "operation";
opCodes["010001"] = "comparison";
opCodes["101001"] = "ldq";
opCodes["011101"] = "stq";
opCodes["111001"] = "beq";
opCodes["111101"] = "bne";
opCodes["011010"] = "jump";

std::map<std::string, std::string> funcCodesOperation;
funcCodesOperation["0100000"] = "addq";
funcCodesOperation["0101001"] = "subq";

std::map<std::string, std::string> funcCodesComparison;
funcCodesComparison["0100000"] = "or/bis";
funcCodesComparison["1000000"] = "xor";
funcCodesComparison["0100100"] = "cmoveq";
funcCodesComparison["1001101"] = "cmplt";

std::map<std::string, std::string> hintCodes;
hintCodes["00"] = "jmp";
hintCodes["01"] = "jsr";
hintCodes["10"] = "ret";

// decode stage
std::string decode(std::string instruction) {
    std::string opcode;
    opcode = instruction.substr(0, 5);
    if (opCodes.find(opcode)->second == "operation") {
        std::string functfield;
        functfield = instruction.substr(20, 27);
        if (funcCodesOperation.find(functfield)->second == "addq") {
            // check bit 12
            if (instruction[19] ==
                0) {  // if bit 12 is 0, then it's an RR type instruction
                std::string ra = instruction.substr(6, 11);
                std::string rb = instruction.substr(11, 16);
            }
        }
    }
}

// execute stage
std::string execute(std::string r1, std::string r2, std::string operation) {
    if (operation == "addq") {
    }
}

// memory stage
// store instruction:
// take in what execute returns
// vector be main memory
// write-back stage
// return a register with the memory data
int binaryToDecimal(long long int binaryNum) {
    int decimal = 0;
    int count = 0;
    int remainder = 0;
    while (binaryNum != 0) {
        remainder = n % 10;
        binaryNum /= 10;
        decimal += remainder * pow(2, count);
        ++count;
    }
    return decimal;
}

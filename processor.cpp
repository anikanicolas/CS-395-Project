#include <iostream>
#include <map>

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

std::string instructionMemory(std::string instruction) {
  std::string opcode;
  for (int i = 0; i <  6; i++) {
    opcode += instruction[i];
  }
  if (Opcodes.find(opcode)->second == "operation") {
    std::string functfield;
    for (int i = 20; i < 27; i++) {
      functfield += instruction[i];
    }
    if (funcCodesOperation.find(functfield)->second == "addq") {
      //check bit 12
      if (instruction[19] == 0) { // if bit 12 is 0, then it's an RR type instruction
        std::string ra;
        for (int i = 6; i < 11; i++) {
          ra += instruction[i];
        }
        std::string rb;
        for (int i = 11; i < 16; i++) {
          rb += instruction[i];
        }
        std::string rc = ALU(ra, rb, "addq");
      }
    }
  }
}

std::string ALU(std::string r1, std::string r2, std::string operation) {
  if (operation == "addq") {
    
  }
}

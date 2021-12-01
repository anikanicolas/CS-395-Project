// set inst map getters

std::map <std::string, std::string> get_op_map() {
    std::map <std::string, std::string> op_map;
    op_map["010000"] = "operation";
    op_map["010001"] = "comparison";
    op_map["101001"] = "ldq";
    op_map["011101"] = "stq";
    op_map["111001"] = "beq";
    op_map["111101"] = "bne";
    op_map["011010"] = "jump";
    op_map["000100"] = "op on line 1 of input.txt";
    op_map["000101"] = "op on line 2 of input.txt";
    return op_map;
}

std::map <std::string, std::string> get_func_map() {
    std::map <std::string, std::string> func_map;
    func_map["0100000"] = "addq";
    func_map["0101001"] = "subq";
    return func_map;
}

std::map <std::string, std::string> get_comp_map() {
    std::map <std::string, std::string> comp_map;
    comp_map["0100000"] = "or/bis";
    comp_map["1000000"] = "xor";
    comp_map["0100100"] = "cmoveq";
    comp_map["1001101"] = "cmplt";
    return comp_map;
}

std::map <std::string, std::string> get_jump_map() {
    std::map <std::string, std::string> jump_map;
    jump_map["00"] = "jmp";
    jump_map["01"] = "jsr";
    jump_map["10"] = "ret";
    return jump_map;
}
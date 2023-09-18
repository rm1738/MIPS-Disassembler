#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <string> 

enum InstructionType {R_Type,I_Type,J_Type, Other_Type};

std::map<std::string, std::string> createRTypeMap() {
    std::map<std::string, std::string> R_type_map;

    // Initialize the map with key-value pairs
    R_type_map["100000"] = "add";
    R_type_map["100001"] = "addu";
    R_type_map["100100"] = "and";
    R_type_map["001101"] = "break";
    R_type_map["011010"] = "div";
    R_type_map["011011"] = "divu";
    R_type_map["001001"] = "jalr";
    R_type_map["001000"] = "jr";
    R_type_map["010000"] = "mfhi";
    R_type_map["010010"] = "mflo";
    R_type_map["010001"] = "mthi";
    R_type_map["010011"] = "mtlo";
    R_type_map["011000"] = "mult";
    R_type_map["011001"] = "multu";
    R_type_map["100111"] = "nor";
    R_type_map["100101"] = "or";
    R_type_map["000000"] = "sll";
    R_type_map["000100"] = "sllv";
    R_type_map["101010"] = "slt";
    R_type_map["101011"] = "sltu";
    R_type_map["000011"] = "sra";
    R_type_map["000111"] = "srav";
    R_type_map["000010"] = "srl";
    R_type_map["000110"] = "srlv";
    R_type_map["100010"] = "sub";
    R_type_map["100011"] = "subu";
    R_type_map["001100"] = "syscall";
    R_type_map["100110"] = "xor";

    return R_type_map;
}

// Define a function to create and initialize the Immediate_map
std::map<std::string, std::string> createImmediateMap() {
    std::map<std::string, std::string> Immediate_map;
    // Initialize the map with key-value pairs
    Immediate_map["001000"] = "addi";
    Immediate_map["001001"] = "addiu";
    Immediate_map["001100"] = "andi";
    Immediate_map["000100"] = "beq";
    Immediate_map["000001"] = "bgez";  // Note: rt is fixed to "00001"
    Immediate_map["000111"] = "bgtz";  // Note: rt is fixed to "00000"
    Immediate_map["000110"] = "blez";  // Note: rt is fixed to "00000"
    Immediate_map["000001"] = "bltz";  // Note: rt is fixed to "00000"
    Immediate_map["000101"] = "bne";
    Immediate_map["100000"] = "lb";
    Immediate_map["100100"] = "lbu";
    Immediate_map["100001"] = "lh";
    Immediate_map["100101"] = "lhu";
    Immediate_map["001111"] = "lui";
    Immediate_map["100011"] = "lw";
    Immediate_map["110001"] = "lwc1";
    Immediate_map["001101"] = "ori";
    Immediate_map["101000"] = "sb";
    Immediate_map["001010"] = "slti";
    Immediate_map["001011"] = "sltiu";
    Immediate_map["101001"] = "sh";
    Immediate_map["101011"] = "sw";
    Immediate_map["111001"] = "swc1";
    Immediate_map["001110"] = "xori";
    return Immediate_map;
}

// Define a function to create and initialize the JTypeMap
std::map<std::string, std::string> createJTypeMap() {
    std::map<std::string, std::string> JTypeMap;

    // Initialize the map with key-value pairs
    JTypeMap["000010"] = "j";
    JTypeMap["000011"] = "jal";

    return JTypeMap;
}

std::map<std::string, std::string> Register_Map() {
    std::map<std::string, std::string> Register_Map;

    Register_Map["00000"] = "$zero";
    Register_Map["00001"] = "$at";
    Register_Map["00010"] = "$v0";
    Register_Map["00011"] = "$v1";
    Register_Map["00100"] = "$a0";
    Register_Map["00101"] = "$a1";
    Register_Map["00110"] = "$a2";
    Register_Map["00111"] = "$a3";
    Register_Map["01000"] = "$t0";
    Register_Map["01001"] = "$t1";
    Register_Map["01010"] = "$t2";
    Register_Map["01011"] = "$t3";
    Register_Map["01100"] = "$t4";
    Register_Map["01101"] = "$t5";
    Register_Map["01110"] = "$t6";
    Register_Map["01111"] = "$t7";
    Register_Map["10000"] = "$s0";
    Register_Map["10001"] = "$s1";
    Register_Map["10010"] = "$s2";
    Register_Map["10011"] = "$s3";
    Register_Map["10100"] = "$s4";
    Register_Map["10101"] = "$s5";
    Register_Map["10110"] = "$s6";
    Register_Map["10111"] = "$s7";
    Register_Map["11000"] = "$t8";
    Register_Map["11001"] = "$t9";
    Register_Map["11010"] = "$k0";
    Register_Map["11011"] = "$k1";
    Register_Map["11100"] = "$gp";
    Register_Map["11101"] = "$sp";
    Register_Map["11110"] = "$fp";
    Register_Map["11111"] = "$ra";
    return Register_Map;
}

// Define and initialize the Hex_Map
std::map<char, std::string> Hex_Map() {
    std::map<char, std::string> Hex_Map;
    Hex_Map['0'] = "0000";
    Hex_Map['1'] = "0001";
    Hex_Map['2'] = "0010";
    Hex_Map['3'] = "0011";
    Hex_Map['4'] = "0100";
    Hex_Map['5'] = "0101";
    Hex_Map['6'] = "0110";
    Hex_Map['7'] = "0111";
    Hex_Map['8'] = "1000";
    Hex_Map['9'] = "1001";
    Hex_Map['a'] = "1010";
    Hex_Map['b'] = "1011";
    Hex_Map['c'] = "1100";
    Hex_Map['d'] = "1101";
    Hex_Map['e'] = "1110";
    Hex_Map['f'] = "1111";
    return Hex_Map;
}

std::string hex_to_binary(const std::string& hex_string, const std::map<char, std::string>& Hex_Map) {
    std::string binary_string;
    for (char hex_char : hex_string) {
        //Uses the map to find the 
        if (Hex_Map.find(hex_char) != Hex_Map.end()) {
            binary_string = binary_string + Hex_Map.at(hex_char);
        } else {
            std::cerr << "Invalid hexadecimal character: " << hex_char << std::endl;
        }
    }
    return binary_string;
}


InstructionType checkTheType(const std::string & binary_string)
{
   std::string opCode = binary_string.substr(0,6);
   InstructionType type; 
   std::map<std::string,std::string> IMap = createImmediateMap();
   if(opCode == "000000")
   {
     type = R_Type;
   }
   else if(IMap.find(opCode) != IMap.end())
   {
     type = I_Type;
   }
   else if(opCode == "000010" || opCode == "000011")
   {
     type = J_Type;
   }
   else{
    type = Other_Type;
   }
   return type;  // Add this line to fix the error.
}

void evaluateRType(const std::string& binary_input)
{
    

}


void processInstructionLine(const std::string& hex_input) {
    // Convert the hex_input to binary using hex_to_binary function
    std::string binary_input = hex_to_binary(hex_input, Hex_Map());
    // Determine the instruction type using checkTheType function
    InstructionType type = checkTheType(binary_input);
    // Print the results for each line
    std::cout << "Hexadecimal Input: " << hex_input << std::endl;
    std::cout << "Binary Output: " << binary_input << std::endl;

    switch (type) {
        case R_Type:
            std::cout << "Instruction Type: R-Type" << std::endl;
            break;
        case I_Type:
            std::cout << "Instruction Type: I-Type" << std::endl;
            break;
        case J_Type:
            std::cout << "Instruction Type: J-Type" << std::endl;
            break;
        case Other_Type:
            std::cout << "Instruction Type: Other" << std::endl;
            break;
    }
}

int main() {
    // Read the hexadecimal strings from the .obj file
    std::ifstream obj_file("test_case2.obj");
    if (!obj_file.is_open()) {
        std::cerr << "Failed to open .obj file." << std::endl;
        return 1;
    }
    std::string hex_input;
    while (obj_file >> hex_input) {
        // Process each line using the function
        processInstructionLine(hex_input);
    }
    obj_file.close();
    return 0;
}


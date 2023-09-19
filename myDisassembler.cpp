#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <string> 
#include <bitset>
#include <vector>
#include <algorithm> 

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
   return type;  
}

std::string int_to_hex_string(int value) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(4) << std::hex << value;
    return stream.str();
}

void evaluateRType(const std::string& binary_input, std::ofstream& output_file) {
    std::string src_reg1 = binary_input.substr(6, 5);
    std::string src_reg2 = binary_input.substr(11, 5);
    std::string dest_reg = binary_input.substr(16, 5);
    std::string shift_amount = binary_input.substr(21, 5);
    std::string function_code = binary_input.substr(26, 6);

    std::map<std::string, std::string> regMap = Register_Map();
    std::map<std::string, std::string> instructionMap = createRTypeMap();

    std::string op = instructionMap[function_code];
    std::string src_reg1_op = regMap[src_reg1];
    std::string src_reg2_op = regMap[src_reg2];
    std::string dest_reg_op = regMap[dest_reg];

    // Check if any of the registers are not found in the maps and print errors to the console
    if (op.empty()) {
        std::cerr << "Error: Invalid function code: " << function_code << std::endl;
    }
    if (src_reg1_op.empty()) {
        std::cerr << "Error: No Register Found for: " << src_reg1 << std::endl;
    }
    if (src_reg2_op.empty()) {
        std::cerr << "Error: No Register Found for: " << src_reg2 << std::endl;
    }
    if (dest_reg_op.empty()) {
        std::cerr << "Error: No destination register Found: " << dest_reg << std::endl;
    }

    // Check for "sll" and "srl" based on their function codes (e.g., "000000" for "sll" and "srl")
    if (function_code == "000000" || function_code == "000010") {
        // Convert the binary shift amount to decimal
        std::bitset<5> shift_bits(shift_amount);
        int shift_decimal = static_cast<int>(shift_bits.to_ulong());

        // Write the "sll" or "srl" instruction to the output file in the expected format
        output_file << op << " " << dest_reg_op << ", " << src_reg2_op << ", " << shift_decimal << std::endl;
    }
    // If all registers are found and it's not "sll" or "srl," write the information to the output file
    else if (!op.empty() && !src_reg1_op.empty() && !src_reg2_op.empty() && !dest_reg_op.empty()) {
        output_file << op << " " << dest_reg_op << ", " << src_reg1_op << ", " << src_reg2_op << std::endl;
    }
}

void evaluateIType(const std::string& binary_input, std::ofstream& output_file, int current_address, const std::vector<int>& branch_targets) {
    std::string opcode = binary_input.substr(0, 6);
    std::string src_reg1 = binary_input.substr(6, 5);
    std::string src_reg2 = binary_input.substr(11, 5);
    std::string immediate_value = binary_input.substr(16, 16);

    // Map for instruction opcodes and registers
    const std::map<std::string, std::string> instructionMap = createImmediateMap();
    const std::map<std::string, std::string> regMap = Register_Map();

    // Get the operation, source registers, and destination register
    const std::string operation = instructionMap.at(opcode);
    const std::string src_reg1_op = regMap.at(src_reg1);
    const std::string src_reg2_op = regMap.at(src_reg2);

    // Check if the operation and registers are found in the maps
    if (operation.empty()) {
        std::cerr << "Error: Invalid opcode: " << opcode << std::endl;
        return;
    }
    if (src_reg1_op.empty()) {
        std::cerr << "Error: Invalid source register: " << src_reg1 << std::endl;
        return;
    }
    if (src_reg2_op.empty()) {
        std::cerr << "Error: Invalid source register: " << src_reg2 << std::endl;
        return;
    }

    // Convert the immediate value from binary to decimal
    const int immediate_decimal = std::stoi(immediate_value, nullptr, 2);

    // Calculate the target address (PC') using the equation
    const int target_offset = immediate_decimal << 2; // Shift left by 2
    const int target_address = current_address + 4 + target_offset;

    // Special handling for "beq" and "bne" instructions
    if (operation == "beq" || operation == "bne") {
        // Check if the target address is in the list of branch targets
        if (std::find(branch_targets.begin(), branch_targets.end(), target_address) != branch_targets.end()) {
            // Output the label for the target address
            output_file << operation << " " << src_reg1_op << ", " << src_reg2_op << ", Addr_" << std::setfill('0') << std::setw(4) << int_to_hex_string(target_address).substr(2) << std::endl;
        } else {
            // Output the target offset directly if not found in branch targets
            output_file << operation << " " << src_reg1_op << ", " << src_reg2_op << ", " << target_offset << std::endl;
        }
    } else if (operation == "lw" || operation == "sw") {
        output_file << operation << " " << src_reg2_op << ", " << immediate_decimal << "(" << src_reg1_op << ")" << std::endl;
    } else {
        output_file << operation << " " << src_reg2_op << ", " << src_reg1_op << ", " << immediate_decimal << std::endl;
    }
}

bool is_hexadecimal(const std::string& str) {
    for (char c : str) {
        if (!std::isxdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

void generateLabels(const std::string& obj_file_name, std::ofstream& output_file) {
    std::ifstream obj_file(obj_file_name);
    if (!obj_file.is_open()) {
        std::cerr << "Failed to open .obj file." << std::endl;
        return;
    }

    std::map<int, std::string> address_to_label; // Map addresses to labels
    std::vector<int> branch_targets; // List of branch target addresses

    int current_address = 0;
    int line_number = 0; // Add this variable to track the line number

    while (obj_file.good()) {
        std::string hex_input;
        obj_file >> hex_input;
        line_number++; // Increment the line number

        if (hex_input.empty()) {
            break; // End of file
        }

        // Check if the input line contains exactly 8 hexadecimal digits
        if (hex_input.size() != 8 || !is_hexadecimal(hex_input)) {
            std::cerr << "Cannot disassemble '" << hex_input << "' at line " << line_number << std::endl;
            obj_file.close();  // Close the input file
            return; // Exit the function due to the error
        }

        std::string binary_input = hex_to_binary(hex_input, Hex_Map());
        InstructionType type = checkTheType(binary_input);

        if (type == I_Type && (binary_input.substr(0, 6) == "000100" || binary_input.substr(0, 6) == "000101")) {
            // Handle branch instructions with labels
            std::bitset<16> offset_bits(binary_input.substr(16, 16));
            int offset_decimal = static_cast<int>(offset_bits.to_ulong());

            // Calculate the target address (PC') using the equation
            int target_address = current_address + 4 + (offset_decimal << 2);

            // Record the branch target address
            branch_targets.push_back(target_address);

            // Output the label for the target address if it's not already present
            if (!address_to_label.count(target_address)) {
                output_file << "Addr_" << std::setfill('0') << std::setw(4) << int_to_hex_string(target_address).substr(2) << ":" << std::endl;
                address_to_label[target_address] = "Addr_" + int_to_hex_string(target_address).substr(2);
            }
        }

        current_address += 4;
    }

    obj_file.close();
    obj_file.open(obj_file_name);
    current_address = 0;

    while (obj_file.good()) {
        std::string hex_input;
        obj_file >> hex_input;
        line_number++; // Increment the line number

        if (hex_input.empty()) {
            break; // End of file
        }

        std::string binary_input = hex_to_binary(hex_input, Hex_Map());
        InstructionType type = checkTheType(binary_input);

        // Output the label for the current address if it's a branch target
        if (std::find(branch_targets.begin(), branch_targets.end(), current_address) != branch_targets.end()) {
            output_file << "Addr_" << std::setfill('0') << std::setw(4) << int_to_hex_string(current_address).substr(2) << ":" << std::endl;
        }

        // Handle branch instructions and other instructions as before
        switch (type) {
            case R_Type:
                evaluateRType(binary_input, output_file);
                break;
            case I_Type:
                evaluateIType(binary_input, output_file, current_address, branch_targets);
                break;
            case J_Type:
                // Handle J-type instructions here if needed
                break;
            case Other_Type:
                std::cerr << "Cannot disassemble '" << hex_input << "' at line " << line_number << std::endl;
                obj_file.close();  // Close the input file
                return; // Exit the function due to the error
        }
        current_address += 4;
    }
    obj_file.close();
}



int main() {
    std::ofstream output_file("output.s");
    if (!output_file.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return 1;
    }

    generateLabels("test_case3.obj", output_file);

    output_file.close();

    return 0;
}

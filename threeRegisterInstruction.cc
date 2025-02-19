#include "threeRegisterInstruction.h"

ThreeRegistersInstruction::ThreeRegistersInstruction(std::string instruction, int instructionNumber, std::vector<Token> arguments)
    : Instruction{instruction, instructionNumber}, arguments{std::move(arguments)} {
        for (int i = 0; i < arguments.size(); ++i) {
            this->arguments.emplace_back(arguments[i]);
        }
}

bool ThreeRegistersInstruction::verify(const std::unordered_map<std::string, uint32_t> &labelMap) {
    if (arguments.size() != 5) return false;

    for (int i = 0; i < arguments.size(); ++i) {
        if (i == 1 || i == 3) {
            if (arguments[i].getTokenType() != COMMA) return false;
        } else {
            if (arguments[i].getTokenType() != REG) return false;
            int registerValue = stoi(arguments[i].getLexeme().substr(arguments[i].getLexeme().find('$') + 1));
            if (registerValue < 0 && registerValue > 31) return false;
            parameters[parameterCount] = registerValue;
            parameterCount++;
        }
    }
    return true;
}

#include "automaton.h"
#include <iostream>
#include <random>
#include <iomanip>

Automaton::Automaton(int stateCount, int inputCount, int outputCount, int sequenceLength) {
    for (int i = 1; i <= stateCount; i++) {
        states.push_back("a" + std::to_string(i));
    }
    for (int i = 1; i <= inputCount; i++) {
        inputs.push_back("z" + std::to_string(i));
    }
    for (int i = 1; i <= outputCount; i++) {
        outputs.push_back("w" + std::to_string(i));
    }
    
    transitionTable.resize(inputCount, std::vector<int>(stateCount));
    outputTable.resize(inputCount, std::vector<int>(stateCount));
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> stateDist(0, stateCount - 1);
    std::uniform_int_distribution<> outputDist(0, outputCount - 1);
    std::uniform_int_distribution<> inputDist(0, inputCount - 1);
    
    for (int i = 0; i < inputCount; i++) {
        for (int j = 0; j < stateCount; j++) {
            transitionTable[i][j] = stateDist(gen);
            outputTable[i][j] = outputDist(gen);
        }
    }
    
    for (int i = 0; i < sequenceLength; i++) {
        inputSequence.push_back(inputDist(gen));
    }
}

void Automaton::displayTables() {
    std::cout << "Таблица перехода:\n";
    std::cout << "δ\t";
    for (const auto& state : states) {
        std::cout << state << "\t";
    }
    std::cout << "\n";
    
    for (int i = 0; i < inputs.size(); i++) {
        std::cout << inputs[i] << "\t";
        for (int j = 0; j < states.size(); j++) {
            std::cout << states[transitionTable[i][j]] << "\t";
        }
        std::cout << "\n";
    }
    
    std::cout << "\nВыходная таблица:\n";
    std::cout << "λ\t";
    for (const auto& state : states) {
        std::cout << state << "\t";
    }
    std::cout << "\n";
    
    for (int i = 0; i < inputs.size(); i++) {
        std::cout << inputs[i] << "\t";
        for (int j = 0; j < states.size(); j++) {
            std::cout << outputs[outputTable[i][j]] << "\t";
        }
        std::cout << "\n";
    }
}

void Automaton::displayInputSequence() {
    std::cout << "Входная последовательность: ";
    for (int input : inputSequence) {
        std::cout << inputs[input] << " ";
    }
    std::cout << "\n";
}
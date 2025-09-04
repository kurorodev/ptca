#include "moore.h"
#include <iostream>
#include <random>

MooreAutomaton::MooreAutomaton(int stateCount, int inputCount, int outputCount, int sequenceLength)
    : Automaton(stateCount, inputCount, outputCount, sequenceLength) {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> outputDist(0, outputCount - 1);
    
    for (int i = 0; i < stateCount; i++) {
        stateOutputs.push_back(outputDist(gen));
    }
}

void MooreAutomaton::displayTables() {
    Automaton::displayTables();
    
    for (int i = 0; i < getStates().size(); i++) {
        std::cout << getStates()[i] << ": " << getOutputs()[stateOutputs[i]] << "\n";
    }
}

std::string MooreAutomaton::getReaction() {
    std::string reaction;
    int currentStateIndex = 0;
    
    for (int input : getInputSequence()) {
        reaction += getOutputs()[stateOutputs[currentStateIndex]] + " ";
        
        currentStateIndex = getTransitionTable()[input][currentStateIndex];
    }
    
    return reaction;
}

std::string MooreAutomaton::getFinalState() {
    int currentStateIndex = 0;
    
    for (int input : getInputSequence()) {
        currentStateIndex = getTransitionTable()[input][currentStateIndex];
    }
    
    return getStates()[currentStateIndex];
}

std::string MooreAutomaton::getFinalOutput() {
    int currentStateIndex = 0;
    
    for (int input : getInputSequence()) {
        currentStateIndex = getTransitionTable()[input][currentStateIndex];
    }
    
    return getOutputs()[stateOutputs[currentStateIndex]];
}
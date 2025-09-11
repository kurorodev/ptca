#include "mealy.h"
#include <iostream>

MealyAutomaton::MealyAutomaton(int stateCount, int inputCount, int outputCount, int sequenceLength)
    : Automaton(stateCount, inputCount, outputCount, sequenceLength) {}

std::string MealyAutomaton::getReaction() {
    std::string reaction;
    int currentStateIndex = 0;
    
    for (int input : getInputSequence()) {
        int outputIndex = getOutputTable()[input][currentStateIndex];
        reaction += getOutputs()[outputIndex] + " ";
        
        currentStateIndex = getTransitionTable()[input][currentStateIndex];
    }
    
    return reaction;
}

std::string MealyAutomaton::getFinalState() {
    int currentStateIndex = 0;
    
    for (int input : getInputSequence()) {
        currentStateIndex = getTransitionTable()[input][currentStateIndex];
    }
    
    return getStates()[currentStateIndex];
}

std::string MealyAutomaton::getFinalOutput() {
    int currentStateIndex = 0;
    const auto& inputSeq = getInputSequence();
    
    for (int i = 0; i < inputSeq.size() - 1; i++) {
        currentStateIndex = getTransitionTable()[inputSeq[i]][currentStateIndex];
    }
    
    int finalInput = inputSeq.back();
    int outputIndex = getOutputTable()[finalInput][currentStateIndex];
    
    return getOutputs()[outputIndex];
}
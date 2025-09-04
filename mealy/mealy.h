#ifndef MEALY_H
#define MEALY_H

#include "../common/automaton.h"

class MealyAutomaton : public Automaton {
public:
    MealyAutomaton(int stateCount = 4, int inputCount = 4, int outputCount = 4, int sequenceLength = 8);
    
    std::string getReaction() override;
    std::string getFinalState() override;
    std::string getFinalOutput() override;
};

#endif // MEALY_H
#ifndef MOORE_H
#define MOORE_H

#include "../common/automaton.h"

class MooreAutomaton : public Automaton {
private:
    std::vector<int> stateOutputs;
    
public:
    MooreAutomaton(int stateCount = 4, int inputCount = 4, int outputCount = 4, int sequenceLength = 8);
    
    void displayTables() override;
    std::string getReaction() override;
    std::string getFinalState() override;
    std::string getFinalOutput() override;
};

#endif // MOORE_H
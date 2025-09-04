#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <vector>
#include <string>

class Automaton {
protected:
    std::vector<std::string> states;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
    std::vector<std::vector<int>> transitionTable;
    std::vector<std::vector<int>> outputTable;
    std::vector<int> inputSequence;
    
public:
    Automaton(int stateCount, int inputCount, int outputCount, int sequenceLength);
    virtual ~Automaton() = default;
    
    virtual void displayTables();
    virtual std::string getReaction() = 0;
    virtual std::string getFinalState() = 0;
    virtual std::string getFinalOutput() = 0;
    
    void displayInputSequence();
    
    // Геттеры для доступа к данным
    const std::vector<std::string>& getStates() const { return states; }
    const std::vector<std::string>& getInputs() const { return inputs; }
    const std::vector<std::string>& getOutputs() const { return outputs; }
    const std::vector<std::vector<int>>& getTransitionTable() const { return transitionTable; }
    const std::vector<std::vector<int>>& getOutputTable() const { return outputTable; }
    const std::vector<int>& getInputSequence() const { return inputSequence; }
};

#endif // AUTOMATON_H
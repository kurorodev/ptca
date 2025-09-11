#include <iostream>
#include "mealy.h"

int main() {
    std::cout << "=== Автомат Мили ===\n\n";
    MealyAutomaton mealy;
    mealy.displayTables();
    mealy.displayInputSequence();
    std::cout << "\nРезультаты:\n";
    std::cout << "Реакция: " << mealy.getReaction() << "\n";
    std::cout << "Финальное состояние: " << mealy.getFinalState() << "\n";
    std::cout << "Финальный выход: " << mealy.getFinalOutput() << "\n";
    
    return 0;
}
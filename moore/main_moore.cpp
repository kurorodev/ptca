#include <iostream>
#include "moore.h"

int main() {
    std::cout << "=== Автомат Мура ===\n\n";
    MooreAutomaton moore;
    moore.displayTables();
    moore.displayInputSequence();
    std::cout << "\nРезультаты:\n";
    std::cout << "Реакция: " << moore.getReaction() << "\n";
    std::cout << "Финальная состояние: " << moore.getFinalState() << "\n";
    std::cout << "Финальный выход: " << moore.getFinalOutput() << "\n";
    
    return 0;
}
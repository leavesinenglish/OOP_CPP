#include <iostream>
#include "game.hpp"

int main() {
    Game g(1, 10);
    g.restart();
    while (g.AnswerCount() < 10) {
        int userAnswer;
        g.generateNewTask();
        std::cout << g.showTask();
        std::cin >> userAnswer;
        while (!g.acceptUserAnswer(userAnswer)) {
            std::cout << "What?" << std::endl;
            std::cin >> userAnswer;
        }
        std::cout << "Right!" << std::endl;
    }
    std::cout << g.stopAndShowResults() << std::endl;
}
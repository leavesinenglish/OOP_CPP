#pragma once
#include <vector>
#include <string>
#include "task.hpp"
#include "arithmetic_operations.hpp"
#include <time.h>


class Game final {
public:
    Game(int _minNumber, int _maxNumber);
    void generateNewTask();
    bool acceptUserAnswer(int userAnswer);
    std::string showTask();
    std::string stopAndShowResults();
    void restart();

    [[nodiscard]] size_t correctAnswerCount() const { return correct_answers_amount; };
    [[nodiscard]] size_t AnswerCount() const { return answers_amount; };

private:
    time_t beginTime, endTime;
    size_t correct_answers_amount;
    size_t answers_amount;
    Task task;
    int minNumber, maxNumber;
    std::vector<std::string> operationSymbols{ "+", "-", "*", "/" };
};
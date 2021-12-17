#include "game.hpp"
#include <iostream>

Game::Game(int _minNumber, int _maxNumber) {
    minNumber = _minNumber;
    maxNumber = _maxNumber;
    answers_amount = 0;
    correct_answers_amount = 0;
    beginTime = 0;
    endTime = 0;
}

void Game::generateNewTask(){
    int firstNumber = minNumber + std::rand() % maxNumber;
    int secondNumber = minNumber + std::rand() % maxNumber;
    int operationIndex = std::rand() % operationSymbols.size();
    Task T(firstNumber, secondNumber, operationSymbols[operationIndex]);
    task = T;
}

bool Game::acceptUserAnswer(int userAnswer) {
    if (task.result == userAnswer) {
        correct_answers_amount++;
        answers_amount++;
        return true;
    } else {
        answers_amount++;
        return false;
    }
}

std::string Game::showTask()
{
    return task.show();
}
std::string Game::stopAndShowResults()
{
    time(&endTime);
    std::string output = std::to_string(( -beginTime + endTime) / correct_answers_amount) + " sec for 1 task";
    return output;
}
void Game::restart()
{
    beginTime = 0;
    endTime = 0;
    time(&beginTime);
    correct_answers_amount = 0;
    answers_amount = 0;
}
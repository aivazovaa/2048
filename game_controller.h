#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "game_model.h"
#include "game_view.h"
#include "game_rules.h"

#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <iostream>
#include <string>

// Добавляем структуру для хранения размеров консоли
struct ConsoleSize {
    int width;  // Ширина консоли
    int height; // Высота консоли
};

class GameController {
public:
    explicit GameController(const std::string& configPath);

    void startGame();       // Запуск игрового процесса
    void displayMenu();     // Отображение меню и управление выбором пользователя
    bool exitGame = false;
    void startNewGame();
    ConsoleSize getConsoleSize();
private:
    // Основные члены класса
    GameModel model;
    GameView view;
    GameRules rules;

    // Обработка ввода и утилиты
    Direction processInput();
    int processMenuInput();
    void setNonBlockingInput(bool enable);
    bool isKeyAvailable();
    bool isConsoleSizeSufficient(int gridSize);

    // Настройки игры
    void loadConfig(const std::string& configPath, int& size, int& targetValue);
    void changeSettings();  // Изменение параметров игры

};

#endif // GAME_CONTROLLER_H

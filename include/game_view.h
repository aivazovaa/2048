#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "game_model.h"
#include <vector>
#include <string>

class GameView {
public:
    virtual ~GameView() = default;

    virtual void display(const GameModel& model);       // Отображение игрового поля
    virtual void displayGameOver();                     // Сообщение о завершении игры
    virtual void displayVictory();                      // Сообщение о победе
    virtual void displayMenu(const std::vector<std::string>& options, int selectedOption, int width, int height);
    virtual void clearScreen();                         // Очистка экрана
    virtual void drawTile(int row, int col, int value); // Отображение отдельной ячейки
    virtual void drawScore(int score);                  // Отображение текущего счета
    virtual int getConsoleWidth();                      // Получение ширины консоли
    virtual int getConsoleHeight();                     // Получение высоты консоли

    // Добавляем объявление метода drawSingleCell
    virtual void drawSingleCell(const GameModel& model, int row, int col);
};

#endif // GAME_VIEW_H

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "game_model.h"

class GameView {
public:
    void display(const GameModel& model);       // Отображение игрового поля
    void displayGameOver();                     // Сообщение о завершении игры
    void displayVictory();                      // Сообщение о победе
    void displayMenu(const std::vector<std::string>& options, int selectedOption, int width, int height);
    void clearScreen();
    void drawTile(int row, int col, int value); // Отображение отдельной ячейки
    void drawScore(int score);                  // Отображение текущего счета
    void drawSingleCell(const GameModel& model, int row, int col); // Отрисовка одной клетки

    void displayMenu();                         // метод для отображения меню
    int getConsoleWidth();  // Возвращает ширину консоли
    int getConsoleHeight(); // Возвращает высоту консоли
};

#endif

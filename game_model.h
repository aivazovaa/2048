#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <vector>

class GameModel {
private:
    int size;          // Размер игрового поля
    int** grid;        // Игровая сетка
    int score;         // Текущий счёт
    bool gameOver;     // Флаг завершения игры
    int targetValue;   // Необходимое для победы значение

public:
    // Конструктор
    GameModel(int size, int targetValue);
    
    // Деструктор
    ~GameModel();

    void setTile(int row, int col, int value);
    void spawnTile();
    bool isGameOver();
    int getScore() const;
    int getTile(int x, int y) const;
    int getSize() const;
};

#endif // GAME_MODEL_H

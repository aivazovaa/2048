// game_model.h
#ifndef GAME_MODEL_H
#define GAME_MODEL_H
#include <vector>
#include <string>

class GameModel {
private:
    int size;
    std::vector<int> grid;
    int score;           // Храним текущий счёт
    bool gameOver;
    int targetValue;
    bool victoryNotified = false; // Флаг для отслеживания сообщения о победе

public:
    GameModel(int size, int targetValue);
    ~GameModel();

    void setTile(int row, int col, int value);
    void spawnTile();
    int getScore() const;            // Получение текущего счёта
    void addScore(int value);        // Метод для увеличения счёта
    int getTile(int x, int y) const;
    int getSize() const;
    int getMaxTile() const;
    int getTargetValue() const;
    void saveState(const std::string& filePath) const;  // Сохранение состояния
    void loadState(const std::string& filePath);       // Загрузка состояния
    void setGameOver(bool state); // Установка флага окончания игры
    bool isGameOver() const;      // Проверка, окончена ли игра
    void setVictoryNotified(bool notified) { victoryNotified = notified; }
    bool isVictoryNotified() const { return victoryNotified; }

};

#endif // GAME_MODEL_H

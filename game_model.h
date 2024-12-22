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

public:
    GameModel(int size, int targetValue);
    ~GameModel();

    void setTile(int row, int col, int value);
    void spawnTile();
    int getScore() const;            // Получение текущего счёта
    void addScore(int value);        // Метод для увеличения счёта
    int getTile(int x, int y) const;
    int getSize() const;
    void saveState(const std::string& filePath) const;  // Сохранение состояния
    void loadState(const std::string& filePath);       // Загрузка состояния

};

#endif // GAME_MODEL_H

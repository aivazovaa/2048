#include "game_model.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <stdexcept>

void GameModel::setGameOver(bool state) {
    gameOver = state;
}

bool GameModel::isGameOver() const {
    if (getMaxTile() >= getTargetValue()) {
        return true; // Победа должна считаться завершением игры
    }
    return gameOver;
}

void GameModel::saveState(const std::string& filePath) const {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл для сохранения.");
    }

    outFile << "size=" << size << "\n";
    outFile << "score=" << score << "\n";

    // Сохраняем игровое поле в строку
    outFile << "grid=";
    for (size_t i = 0; i < grid.size(); ++i) {
        outFile << grid[i];
        if (i < grid.size() - 1) {
            outFile << ",";
        }
    }
    outFile.close();
}

void GameModel::loadState(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл для загрузки.");
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (std::getline(is_line, value)) {
                if (key == "size") {
                    size = std::stoi(value);
                    grid.resize(size * size);
                } else if (key == "score") {
                    score = std::stoi(value);
                } else if (key == "grid") {
                    std::istringstream gridStream(value);
                    std::string cell;
                    for (size_t i = 0; std::getline(gridStream, cell, ','); ++i) {
                        grid[i] = std::stoi(cell);
                    }
                }
            }
        }
    }
}


void GameModel::addScore(int value) {
    score += value;  // Увеличиваем счёт на переданное значение
}


GameModel::GameModel(int size, int targetValue)
    : size(size), targetValue(targetValue), score(0), gameOver(false), victoryNotified(false) {
    grid.resize(size * size, 0);
    spawnTile();
}



GameModel::~GameModel() {
}

void GameModel::spawnTile() {
    if (gameOver) return;

    int x, y;
    do {
        x = rand() % size;
        y = rand() % size;
    } while (grid[x * size + y] != 0); // Ищем пустую клетку

    grid[x * size + y] = (rand() % 2 == 0) ? 2 : 4; // 50% вероятность появления 2 или 4
}


void GameModel::setTile(int row, int col, int value) {
    if (row >= 0 && row < size && col >= 0 && col < size) {
        grid[row * size + col] = value;
    }
}


int GameModel::getScore() const {
    return score;
}

int GameModel::getTile(int x, int y) const {
    if (x >= 0 && x < size && y >= 0 && y < size) {
        return grid[x * size + y];
    }
    return -1; // Возвращаем -1 для некорректных координат
}

int GameModel::getSize() const {
    return size;
}

int GameModel::getMaxTile() const {
    return *std::max_element(grid.begin(), grid.end());
}


int GameModel::getTargetValue() const {
    return targetValue;
}

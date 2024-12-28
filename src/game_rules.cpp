#include "game_rules.h"
#include "game_model.h"
#include <algorithm>
#include <iostream>

// Функция для сдвига плиток до упора
bool GameRules::slideTiles(std::vector<int>& line) {
    bool moved = false;
    int size = line.size();
    int lastEmpty = 0;

    for (int i = 0; i < size; ++i) {
        if (line[i] != 0) {
            if (i != lastEmpty) {
                std::swap(line[lastEmpty], line[i]);
                moved = true;  // Если плитка переместилась, фиксируем движение
            }
            lastEmpty++;
        }
    }
    return moved;
}

// Функция для объединения плиток
bool GameRules::combineTiles(int& a, int& b, GameModel& model) {
    if (a == b && a != 0) {
        int combinedValue = a * 2;  // Плитки объединяются
        a = combinedValue;
        b = 0;   // Очищаем вторую плитку
        model.addScore(combinedValue);  // Добавляем очки
        return true;
    }
    return false;
}
// Метод для сдвига и объединения плиток
void GameRules::slideAndCombine(std::vector<int>& line, GameModel& model) {
    for (int i = 0; i < line.size() - 1; ++i) {
        if (combineTiles(line[i], line[i + 1], model)) {
            i = -1;  // После каждого объединения проверяем с самого начала строки
        }
    }
    slideTiles(line);  // После объединения сдвигаем плитки до упора
}

// Основной метод перемещения плиток в зависимости от направления
void GameRules::move(GameModel& model, Direction dir) {
    int size = model.getSize();
    std::vector<int> line(size);
    bool moved = false;  // Флаг для отслеживания, было ли перемещение или слияние

    if (dir == LEFT || dir == RIGHT) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                line[j] = model.getTile(i, j);
            }

            if (dir == RIGHT) {
                std::reverse(line.begin(), line.end());  // Для перемещения вправо
            }

            // Сдвигаем плитки и объединяем их
            if (slideTiles(line)) {
                moved = true;
            }

            slideAndCombine(line, model);  // Передаем model для обновления счёта
            moved = true;  // Если было перемещение или объединение, зафиксируем это

            if (dir == RIGHT) {
                std::reverse(line.begin(), line.end());  // Возвращаем обратно
            }

            // Обновляем игровое поле
            for (int j = 0; j < size; ++j) {
                model.setTile(i, j, line[j]);
            }
        }
    } else {  // Перемещение вверх или вниз
        for (int j = 0; j < size; ++j) {
            for (int i = 0; i < size; ++i) {
                line[i] = model.getTile(i, j);
            }

            if (dir == DOWN) {
                std::reverse(line.begin(), line.end());  // Для перемещения вниз
            }

            if (slideTiles(line)) {
                moved = true;
            }

            slideAndCombine(line, model);  // Передаем model для обновления счёта
            moved = true;  // Зафиксируем перемещение

            if (dir == DOWN) {
                std::reverse(line.begin(), line.end());
            }

            // Обновляем игровое поле
            for (int i = 0; i < size; ++i) {
                model.setTile(i, j, line[i]);
            }
        }
    }

    if (moved) {
        spawnTile(model);  // Добавляем новую плитку
    } else {
        std::cout << "Ход невозможен. Попробуйте другое направление.\n";
    }
}

// Проверка, возможен ли ход (есть ли свободное место или возможность слияния)
bool GameRules::canMove(const GameModel& model) const {
    int size = model.getSize();

    // Проверка на наличие пустых ячеек или возможность слияния
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int currentTile = model.getTile(i, j);
            if (currentTile == 0) return true;  // Есть пустое место
            if (i < size - 1 && currentTile == model.getTile(i + 1, j)) return true;  // Можно объединить вниз
            if (j < size - 1 && currentTile == model.getTile(i, j + 1)) return true;  // Можно объединить вправо
        }
    }
    return false;
}

// Метод для добавления новой плитки на поле
void GameRules::spawnTile(GameModel& model) {
    std::vector<std::pair<int, int>> emptyTiles;
    int size = model.getSize();

    // Поиск всех пустых ячеек
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (model.getTile(i, j) == 0) {
                emptyTiles.emplace_back(i, j);
            }
        }
    }

    // Если есть пустые ячейки, добавляем новую плитку
    if (!emptyTiles.empty()) {
        int randomIndex = rand() % emptyTiles.size();
        int tileValue = (rand() % 2 == 0) ? 2 : 4;  // Вероятность появления 2 или 4
        model.setTile(emptyTiles[randomIndex].first, emptyTiles[randomIndex].second, tileValue);
    }
}

// Проверка окончания игры (нет свободных клеток и возможностей слияния)
bool GameRules::isGameOver(const GameModel& model) {
    int size = model.getSize();
    
    if (model.getMaxTile() >= model.getTargetValue()) {
        const_cast<GameModel&>(model).setGameOver(true); // Устанавливаем gameOver
        return true;
    }
    
    // Победа
    if (model.getMaxTile() >= model.getTargetValue()) {
        return true;
    }
    
    
    // Проход по всем клеткам игрового поля
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int currentTile = model.getTile(i, j);

            // Если есть хотя бы одна пустая клетка, игра не окончена
            if (currentTile == 0) {
                return false;
            }

            // Проверяем возможность слияния соседних плиток
            if (i < size - 1 && currentTile == model.getTile(i + 1, j)) {
                return false;  // Можно объединить вниз
            }
            if (j < size - 1 && currentTile == model.getTile(i, j + 1)) {
                return false;  // Можно объединить вправо
            }
        }
    }

    // Если нет пустых клеток и слияний, игра окончена
    return true;
}

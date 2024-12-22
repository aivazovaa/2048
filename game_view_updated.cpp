#include "game_view_updated.h"
#include <iostream>
#include <iomanip>

void GameViewUpdated::clearScreen() {
    // Перемещаем курсор в начало экрана и очищаем экран ниже
    std::cout << "\033[H\033[J";
}

void GameViewUpdated::display(const GameModel& model) {
    // Перемещаем курсор в начало экрана и очищаем
    clearScreen();

    int size = model.getSize();
    drawScore(model.getScore());

    // Рисуем игровое поле
    for (int i = 0; i < size; ++i) {
        // Рисуем верхнюю границу ячеек
        for (int j = 0; j < size; ++j) {
            std::cout << "+----";
        }
        std::cout << "+\n";

        // Рисуем содержимое ячеек
        for (int j = 0; j < size; ++j) {
            std::cout << "|";
            drawTile(i, j, model.getTile(i, j));
        }
        std::cout << "|\n";
    }

    // Нижняя граница игрового поля
    for (int j = 0; j < size; ++j) {
        std::cout << "+----";
    }
    std::cout << "+\n";

    // Вывод подсказки для управления
    std::cout << "Используйте W/A/S/D для управления. Нажмите 'M' для выхода в меню.\n";
}

void GameViewUpdated::displayMenu(const std::vector<std::string>& options, int selectedOption, int width, int height) {
    // Очищаем экран и позиционируем курсор
    clearScreen();

    int menuSize = options.size();
    int startRow = (height / 2) - (menuSize / 2);

    // Рисуем меню
    for (int i = 0; i < menuSize; ++i) {
        int col = (width / 2) - (options[i].size() / 2);
        std::cout << "\033[" << startRow + i << ";" << col << "H";
        if (i == selectedOption) {
            std::cout << "\033[1;32m> " << options[i] << " <\033[0m";
        } else {
            std::cout << options[i];
        }
    }

    // Подсказка внизу
    std::cout << "\033[" << height - 2 << ";" << (width / 2) - 20 << "H";
    std::cout << "Используйте W/S для навигации и Enter для выбора";
    std::cout.flush();
}

#include "game_view.h"
#include "game_model.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sys/ioctl.h> // Для получения размеров терминала
#include <unistd.h>    // Для работы с ioctl


int GameView::getConsoleWidth() {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        return w.ws_col; // Возвращаем количество столбцов (ширина консоли)
    }
    return 80; // Значение по умолчанию
}

int GameView::getConsoleHeight() {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        return w.ws_row; // Возвращаем количество строк (высота консоли)
    }
    return 24; // Значение по умолчанию
}


void GameView::displayMenu(const std::vector<std::string>& options, int selectedOption, int width, int height) {
    clearScreen(); // Очищаем экран перед отрисовкой

    int menuSize = options.size();
    int startRow = (height / 2) - (menuSize / 2); // Центровка по вертикали

    for (int i = 0; i < menuSize; ++i) {
        int col = (width / 2) - (options[i].size() / 2); // Центровка по горизонтали
        std::cout << "\033[" << startRow + i << ";" << col << "H"; // Позиционирование текста

        if (i == selectedOption) {
            std::cout << "\033[1;32m> " << options[i] << " <\033[0m"; // Выбранная опция выделяется цветом
        } else {
            std::cout << options[i];
        }
    }

    // Отрисовка подсказки внизу экрана
    std::cout << "\033[" << height - 2 << ";" << (width / 2) - 20 << "H";
    std::cout << "Используйте W/S для навигации и Enter для выбора";
    std::cout.flush();
}





void GameView::clearScreen() {
    std::cout << "\033[2J\033[H"; // Очистка экрана
}



void GameView::displayGameOver() {
    std::cout << "\033[31mИгра окончена! Попробуйте снова.\033[0m\n";
}

void GameView::displayVictory() {
    std::cout << "\033[32mПоздравляем! Вы победили!\033[0m\n";
}

void GameView::drawScore(int score) {
    std::cout << "Счёт: " << score << "\n";
}

void GameView::drawTile(int row, int col, int value) {
    std::string colorCode;

    // Определение цвета ячейки в зависимости от значения
    switch (value) {
        case 2: colorCode = "\033[32m"; break;    // Зеленый для 2
        case 4: colorCode = "\033[33m"; break;    // Желтый для 4
        case 8: colorCode = "\033[34m"; break;    // Синий для 8
        case 16: colorCode = "\033[35m"; break;   // Фиолетовый для 16
        case 32: colorCode = "\033[36m"; break;   // Голубой для 32
        case 64: colorCode = "\033[31m"; break;   // Красный для 64
        case 128: colorCode = "\033[91m"; break;  // Светло-красный для 128
        case 256: colorCode = "\033[92m"; break;  // Светло-зеленый для 256
        case 512: colorCode = "\033[93m"; break;  // Светло-желтый для 512
        case 1024: colorCode = "\033[94m"; break; // Светло-синий для 1024
        case 2048: colorCode = "\033[95m"; break; // Светло-фиолетовый для 2048
        default: colorCode = "\033[0m"; break;    // Белый для пустых или больших значений
    }

    // Отображение значения ячейки с выравниванием и цветом
    if (value != 0) {
        std::cout << colorCode << std::setw(4) << value << "\033[0m";
    } else {
        std::cout << "    "; // Пустая ячейка
    }
}

void GameView::display(const GameModel& model) {
    clearScreen();

    int size = model.getSize();

    // Отображение счета
    drawScore(model.getScore());
    std::cout << "Текущее состояние игрового поля:\n";

    for (int i = 0; i < size; ++i) {
        // Верхняя граница ячеек
        for (int j = 0; j < size; ++j) {
            std::cout << "+----";
        }
        std::cout << "+\n";

        // Содержимое ячеек
        for (int j = 0; j < size; ++j) {
            std::cout << "|";
            drawTile(i, j, model.getTile(i, j));
        }
        std::cout << "|\n";
    }

    // Нижняя граница ячеек
    for (int j = 0; j < size; ++j) {
        std::cout << "+----";
    }
    std::cout << "+\n";

    // Инструкция для пользователя
    std::cout << "Используйте W/A/S/D для управления. Нажмите 'M' для выхода в меню.\n";
}


void GameView::drawSingleCell(const GameModel& model, int row, int col) {
    // Рисует только одну ячейку с заданной позицией
    std::cout << "Обновление клетки [" << row << ", " << col << "]: ";
    drawTile(row, col, model.getTile(row, col));
    std::cout << std::endl;
}

#include "game_model.h"
#include "game_view.h"
#include "game_rules.h"
#include "game_controller.h"
#include <iostream>
#include <unistd.h>

int main() {
    try {
        GameController controller("config.txt");

        while (true) {
            // Получаем размеры консоли
            int width, height;
            ConsoleSize size = controller.getConsoleSize();
            width = size.width;
            height = size.height;

            // Обновляем интерфейс
            controller.displayMenu(); // Отображаем меню
            controller.startGame();   // Запуск игрового процесса

            // Пауза перед следующей итерацией для обновления
            usleep(100000);  // Задержка в 100 миллисекунд
        }

    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


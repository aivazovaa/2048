#include "game_model.h"
#include "game_view.h"
#include "game_rules.h"
#include "game_controller.h"
#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[]) {
    try {
        // Проверяем, что указан путь к конфигурационному файлу
        if (argc < 2) {
            std::cerr << "Ошибка: укажите путь к конфигурационному файлу как первый аргумент.\n";
            std::cerr << "Пример: ./Game2048 config.txt\n";
            return EXIT_FAILURE;
        }

        // Получаем путь к конфигурационному файлу из первого аргумента
        std::string configPath = argv[1];
        GameController controller(configPath);

        // Основной цикл игры
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

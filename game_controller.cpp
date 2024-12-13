#include "game_controller.h"
#include "game_view.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>


ConsoleSize GameController::getConsoleSize() {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        return {w.ws_col, w.ws_row};
    }
    return {80, 24}; // Значения по умолчанию, если размеры не удалось получить
}



bool GameController::isConsoleSizeSufficient(int gridSize) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        int requiredWidth = gridSize * 6 + 10;  // Учитываем ширину ячеек (+границы и дополнительное пространство)
        int requiredHeight = gridSize * 2 + 5;  // Учитываем высоту ячеек (+границы и счёт)

        // Если консоль слишком мала для отображения игрового поля
        if (w.ws_col < requiredWidth || w.ws_row < requiredHeight) {
            std::cerr << "Ошибка: Консоль слишком мала для отображения игрового поля "
                      << gridSize << "x" << gridSize << ". Требуется минимум "
                      << requiredWidth << "x" << requiredHeight << " пикселей. "
                      << "Увеличьте размер окна терминала.\n";
            return false;
        }
    }
    return true;
}


void GameController::displayMenu() {
    const std::vector<std::string> options = {
        "Продолжить игру",
        "Начать новую игру",
        "Изменить параметры игры",
        "Сохранить игру",
        "Загрузить игру",
        "Выйти"
    };

    int consoleWidth = view.getConsoleWidth();
    int consoleHeight = view.getConsoleHeight();

    int selectedOption = 0;
    setNonBlockingInput(true); // Устанавливаем неблокирующий режим

    while (true) {
        // Обновляем меню
        view.displayMenu(options, selectedOption, consoleWidth, consoleHeight);

        // Читаем ввод
        int input = processMenuInput();
        if (input == -1) {
            selectedOption = (selectedOption - 1 + options.size()) % options.size(); // Навигация вверх
        } else if (input == 1) {
            selectedOption = (selectedOption + 1) % options.size(); // Навигация вниз
        } else if (input == 0) {
            setNonBlockingInput(false); // Перед действием отключаем неблокирующий режим
            view.clearScreen();
            if (selectedOption == 0) {
                // Продолжить игру
                return; // Возврат в текущую игру
            } else if (selectedOption == 1) {
                startNewGame(); // Начать новую игру
                return;
            } else if (selectedOption == 2) {
                changeSettings();
                return;
            } else if (selectedOption == 3) {
                try {
                    model.saveState("savegame.txt");
                    std::cout << "Игра успешно сохранена!\n";
                } catch (const std::exception& e) {
                    std::cerr << e.what() << "\n";
                }
            } else if (selectedOption == 4) {
                try {
                    model.loadState("savegame.txt");
                    std::cout << "Игра успешно загружена!\n";
                } catch (const std::exception& e) {
                    std::cerr << e.what() << "\n";
                }
            } else if (selectedOption == 5) {
                std::cout << "Выход из игры.\n";
                exit(0); // Завершаем программу
            }

            setNonBlockingInput(true); // Включаем неблокирующий режим после действия
        }

        usleep(100000); // Задержка для предотвращения высокой нагрузки
    }
}


void GameController::changeSettings() {
    int newSize, newTargetValue;

    // Цикл ввода нового размера поля
    while (true) {
        std::cout << "Введите новый размер поля (не меньше 2): ";
        std::cin >> newSize;

        // Проверка размера консоли для указанного размера поля
        if (!isConsoleSizeSufficient(newSize)) {
            std::cout << "Ошибка: размер консоли слишком мал для указанного размера поля.\n";
            // Повторно запрашиваем ввод размера
            continue;
        }

        // Проверка, что размер поля больше 1
        if (newSize < 2) {
            std::cout << "Ошибка: размер поля не может быть меньше 2. Попробуйте снова.\n";
            // Повторно запрашиваем ввод размера
            continue;
        }

        // Если оба условия пройдены, выходим из цикла
        break;
    }

    // Запрос целевого значения
    std::cout << "Введите новое целевое значение: ";
    std::cin >> newTargetValue;

    // Попытка сохранить настройки в файл
    std::ofstream configFile("config.txt");
    if (configFile.is_open()) {
        configFile << "size=" << newSize << "\n";
        configFile << "targetValue=" << newTargetValue << "\n";
        configFile.close();
        std::cout << "Параметры успешно изменены!\n";  // Уведомление об успешном сохранении
    } else {
        std::cerr << "Ошибка: не удалось сохранить параметры.\n";  // Ошибка, если не удалось сохранить файл
        return;  // Возврат в меню, если не удалось сохранить файл
    }

    // Обновление модели с новыми параметрами
    model = GameModel(newSize, newTargetValue);

    // Возврат в меню после изменений
    displayMenu();
}



void GameController::loadConfig(const std::string& configPath, int& size, int& targetValue) {
    std::ifstream configFile(configPath);
    if (!configFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл конфигурации: " + configPath);
    }

    std::string line;
    while (std::getline(configFile, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) { // Чтение ключа
            std::string value;
            if (std::getline(is_line, value)) { // Чтение значения
                if (key == "size") {
                    size = std::stoi(value); // Преобразование строки в число
                } else if (key == "targetValue") {
                    targetValue = std::stoi(value);
                }
            }
        }
    }
}


GameController::GameController(const std::string& configPath) : model(4, 2048) {
    int size = 4;
    int targetValue = 2048;

    loadConfig(configPath, size, targetValue);

    // Обновляем параметры модели
    model = GameModel(size, targetValue);

    view = GameView();
    rules = GameRules();
}




// Настройка терминала для неблокирующего ввода
void GameController::setNonBlockingInput(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

// Проверка доступности ввода
bool GameController::isKeyAvailable() {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

// Обработка ввода пользователя
Direction GameController::processInput() {
    if (isKeyAvailable()) {
        char input;
        read(STDIN_FILENO, &input, 1);
        switch (input) {
            case 'w': return UP;
            case 's': return DOWN;
            case 'a': return LEFT;
            case 'd': return RIGHT;
            case 'M': // Клавиша для возврата в меню
            case 'm':
                return MENU;
            default:
                std::cout << "Некорректный ввод. Используйте w/a/s/d для движения или m для выхода в меню.\n";
                return NONE;
        }
    }
    return NONE;
}



int GameController::processMenuInput() {
    char input;
    if (isKeyAvailable()) {
        read(STDIN_FILENO, &input, 1);
        switch (input) {
            case 'w': return -1; // Наверх
            case 's': return 1;  // Вниз
            case '\n': return 0; // Выбор
            default: return 2;   // Некорректный ввод
        }
    }
    return 2; // Если ввода нет
}


// Основной игровой процесс
void GameController::startGame() {
    ConsoleSize consoleSize = getConsoleSize();
    int gridSize = model.getSize();

    int requiredWidth = gridSize * 6;  // Учитываем ширину ячеек
    int requiredHeight = gridSize * 2 + 4; // Учитываем высоту интерфейса

    if (consoleSize.width < requiredWidth || consoleSize.height < requiredHeight) {
        std::cerr << "Ошибка: Консоль слишком мала для отображения игрового поля. "
                  << "Увеличьте размер окна терминала.\n";
        return; // Завершаем выполнение метода
    }

    setNonBlockingInput(true);
    view.display(model);

    while (!rules.isGameOver(model)) {
        Direction dir = processInput();
        if (dir == MENU) {
            // Возвращаемся в меню
            return;
        } else if (dir != NONE) {
            if (rules.canMove(model)) {
                rules.move(model, dir);
                view.display(model);
            } else {
                std::cout << "Ход невозможен. Попробуйте другое направление.\n";
            }
        }
        usleep(100000);  // Задержка для плавности
    }

    view.displayGameOver();
    setNonBlockingInput(false);
};

void GameController::startNewGame() {
    int newSize = 4;  // Значение по умолчанию
    int newTargetValue = 2048;  // Значение по умолчанию

    // Загружаем параметры из конфигурационного файла
    loadConfig("config.txt", newSize, newTargetValue); // Загружаем сохранённые значения из config.txt

    // Перезагружаем модель игры с новыми параметрами
    model = GameModel(newSize, newTargetValue);

    // Отображаем начальное состояние игры
    view.display(model);

    std::cout << "Новая игра начата!" << std::endl;
};



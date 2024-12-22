cmake_minimum_required(VERSION 3.10)
project(Game2048)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)


# Подключение исполняемого файла
add_executable(Game2048 main.cpp game_model.cpp game_view.cpp game_rules.cpp game_controller.cpp game_view_updated.cpp)


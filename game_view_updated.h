#ifndef GAME_VIEW_UPDATED_H
#define GAME_VIEW_UPDATED_H

#include "game_view.h"

class GameViewUpdated : public GameView {
public:
    void clearScreen() override;  // Полная очистка экрана
    void display(const GameModel& model) override;  // Отображение игрового поля
    void displayMenu(const std::vector<std::string>& options, int selectedOption, int width, int height) override; // Отображение меню
};

#endif // GAME_VIEW_UPDATED_H

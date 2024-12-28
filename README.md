# 2048

## Introduction

The game 2048 was developed as an educational project for OOP practice at Bauman Moscow State Technical University. It serves as a simulation of the popular sliding tile puzzle game, where players aim to merge numbered tiles to achieve a target value.

The player uses W, A, S, D keys to slide the tiles in four directions: up, down, left, or right. When two tiles with the same number collide, they merge into one with double the value. The goal is to reach the target value, which defaults to 2048, but this can be configured. The game ends when no more valid moves are possible or the target value is achieved.

The program interface is implemented for the UNIX console and uses text-based graphics.

## Showcase

![gif]([https://github.com/dalatea/Plants_vs_zombies/assets/148526614/faa34b0f-9185-4c35-a66e-e04b52e442ad](https://github.com/aivazovaa/2048/blob/cc38576e78b59ac6401372bc12b4c8f88279394c/%D0%97%D0%B0%D0%BF%D0%B8%D1%81%D1%8C-%D1%8D%D0%BA%D1%80%D0%B0%D0%BD%D0%B0-2024-12-28-%D0%B2-04.08.26.gif))


## Installation

To install and run the game, follow these steps:

```bash
git clone https://github.com/aivazovaa/2048
cd 2048
cd build
cmake ..
make
./Game2048 config.txt
```

## Features
	1.	Configurable Board and Target:
	•	Board size and target tile value can be customized in the config.txt file.
	2.	Dynamic Console Resizing Check:
	•	Ensures the console size is sufficient for displaying the board.
	3.	Game Saving and Loading:
	•	Save your progress to a file (savegame.txt) and reload it later.
	4.	Intuitive Controls:
	•	W, A, S, D keys for movement.
	•	M key to return to the menu.
	5.	Score Tracking:
	•	The game dynamically updates the score based on merged tiles.
	6.	Graphical Updates:
	•	Color-coded tiles for better visualization.
	7.	Victory and Game Over:
	•	Notifications for achieving the target value or when no moves are left.
	8.	Menu Options:
	•	Start a new game, continue an existing one, change settings, save, load, or exit.

## Requirements
	•	Operating System: UNIX-based (Linux or macOS)
	•	Compiler: C++17 or higher
	•	Build Tool: CMake
	•	Terminal: Supports ANSI escape sequences for graphical display.

## Configuration

The config.txt file allows customization of:
	•	Board Size (size): Minimum value is 2.
	•	Target Value (targetValue): Default is 2048.


## Usage
	1.	Run the game using the executable:

./Game2048 config.txt

	2.	Navigate the menu using W/S to move up or down and Enter to select options.
	3.	During the game:
	•	Use W, A, S, D to move tiles.
	•	Press M to access the menu.


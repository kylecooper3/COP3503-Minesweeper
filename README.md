# Minesweeper

A desktop Minesweeper game written in C++ with [SFML](https://www.sfml-dev.org/), originally built as a class project for COP3503.

![Mid-game board](https://github.com/kylecooper3/COP3503-Minesweeper/assets/116681147/70fb9fcf-82b7-44c4-8b58-d67622a51b6d)

## Features

- Left-click to reveal tiles and right-click to place flags
- Mine counter and game timer
- Pause button and a smiley-face button to restart
- Debug button that shows where the mines are
- Leaderboard that saves the fastest times
- Board size and mine count set in a config file

## Screenshots

| Welcome screen | New game |
| --- | --- |
| ![Welcome screen asking for a name](https://github.com/kylecooper3/COP3503-Minesweeper/assets/116681147/63b0e031-962f-48bd-bf24-e9a3b2cea437) | ![New game with all tiles hidden](https://github.com/kylecooper3/COP3503-Minesweeper/assets/116681147/5e23e133-f611-4e2f-82ed-8547e356e1df) |

| Lost game | Leaderboard mid-game |
| --- | --- |
| ![Lost game after clicking a mine](https://github.com/kylecooper3/COP3503-Minesweeper/assets/116681147/b9d94891-38fd-425c-851d-18f874ec9d82) | ![Leaderboard opened during a game](https://github.com/kylecooper3/COP3503-Minesweeper/assets/116681147/678bda86-67a6-401f-af8e-e2e316585200) |

| Won game |
| --- |
| ![Won game with the player's name added to the leaderboard](https://github.com/kylecooper3/COP3503-Minesweeper/assets/116681147/c0a40a76-c620-4ff8-8dd2-ccde37efd637) |

## Building

Tested on Windows 10 with:

- SFML 2.5.1 (GCC 7.3.0 MinGW SEH 64-bit build)
- MinGW-w64 GCC 7.3.0, the compiler that SFML build requires
- CMake 3.25 (the project requires 3.24 or newer)

From the repo root:

```sh
cmake -S . -B build -G "MinGW Makefiles" -DSFML_DIR=C:/path/to/SFML/lib/cmake/SFML
cmake --build build
```

## Game files

The `files/` folder holds the images, font, and board config from the class project. To change the board size or mine count, edit `files/board_config.cfg`, which lists the width, height, and mine count, one per line.

Scores are saved to `files/leaderboard.txt`, which is created after your first win and is not tracked by git.

## Running

Start the game from the repo root, because it loads `files/` relative to the current directory:

```sh
./build/minesweeper.exe
```

MinGW's `bin` folder must be on your `PATH` so the game can find its runtime DLLs.

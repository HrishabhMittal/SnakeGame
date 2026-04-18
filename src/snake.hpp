#pragma once
#include "ansi.hpp"
#include "utils.hpp"
#include <random>

inline int randint(int a, int b) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(a, b);
    return distr(gen);
}

class Game {
    std::vector<std::vector<int>> board;
    int length = 5;
    int dirn = 0;
    int size;
    bool isOver = false;
    void move(int &x, int &y) {
        switch (dirn) {
        case 0:
            x--;
            break;
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y++;
            break;
        }
        if (x == -1 || x == size || y == -1 || y == size)
            isOver = true;
    }
    void input() {
        if (kbhit()) {
            char x = getchar();
            if (x == 27) {
                x = getchar();
                if (x == 91)
                    x = getchar();
            }
            switch (x) {
            case 65:
                x = 'w';
                break;
            case 68:
                x = 'a';
                break;
            case 66:
                x = 's';
                break;
            case 67:
                x = 'd';
                break;
            }
            switch (x) {
            case 'w':
            case 'W':
                dirn = 0;
                break;
            case 'a':
            case 'A':
                dirn = 1;
                break;
            case 's':
            case 'S':
                dirn = 2;
                break;
            case 'd':
            case 'D':
                dirn = 3;
                break;
            }
        }
    }
    void genApple() {
        int ax = randint(0, size - 1), ay = randint(0, size - 1);
        while (board[ax][ay] != 0) {
            ax = randint(0, size - 1);
            ay = randint(0, size - 1);
        }
        board[ax][ay] = -1;
    }
    void update() {

        input();
        int x, y;
        int max = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] > max)
                    x = i, y = j, max = board[i][j];
            }
        }

        move(x, y);

        if (isOver)
            return;

        if (board[x][y] == max - 1) {
            dirn = (dirn + 2) % 4;
            move(x, y);
            move(x, y);
        }

        if (board[x][y] == -1) {
            length++;
            genApple();
        }

        else if (board[x][y] != 0)
            isOver = true;

        else {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (board[i][j] > 0)
                        board[i][j]--;
                }
            }
        }
        if (isOver)
            return;
        board[x][y] = length;
    }
    void print() {
        setSize(size + 1, size * 2);
        std::string out = "\033[HSNAKE GAME              Score:" + std::to_string(length - 5) + '\n';
        std::string prevcol(RESET_COLOR);
        std::string apple = brgb(250, 0, 0);
        std::string snake = brgb(0, 250, 0);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == -1) {
                    if (prevcol != apple) {
                        out += apple;
                        prevcol = apple;
                    }
                } else if (board[i][j] == 0) {
                    if (prevcol != brgb(0, 0, 0)) {
                        out += brgb(0, 0, 0);
                        prevcol = brgb(0, 0, 0);
                    }
                } else {
                    if (prevcol != snake) {
                        out += snake;
                        prevcol = snake;
                    }
                }
                out += "  ";
            }
            out += '\n';
        }
        out.pop_back();
        out += RESET_COLOR;
        std::cout << out;
    }

  public:
    Game(int s) {
        size = s;
        board = std::vector(size, std::vector(size, 0));
        board[size / 2][size / 2] = length;
        genApple();
    }
    bool isGameOver() { return isOver; }
    void render() {
        update();
        print();
    }
};

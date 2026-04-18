#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <random>

#include <thread>
#include <chrono>

#include <stdio.h>
#include <termios.h>
#include "utils.hpp"

inline void no_echo() {
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), 0, &term);
}
inline void echo() {
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag |= ECHO;
    tcsetattr(fileno(stdin), 0, &term);
}

//basic
#include <iostream>
#include <string>
#include <vector>

//for random apples
#include <random>

// only for this_thread::sleepfor
#include <thread>

//made sure that code works on cmd powershell and bash
//by default virtual terminal processing is disbled in powershell and cmd
//(not when you open them in vscode)
//enabled on bash by default
using namespace std;
#if __has_include(<windows.h>)
#include <windows.h>
#include <conio.h>
int enableEscapeSquences() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return GetLastError();
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return GetLastError();
    return 0;
}
void no_echo() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
}
void echo() {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT);
}
#else
#include <stdio.h>
#include <termios.h>
#include "utils.h"
int enableEscapeSequences() {
    return 0;
}
void no_echo() {
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), 0, &term);
}
void echo() {
    struct termios term;
    tcgetattr(fileno(stdin), &term);
    term.c_lflag |= ECHO;
    tcsetattr(fileno(stdin), 0, &term);
}
#endif
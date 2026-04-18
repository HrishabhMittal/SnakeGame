#pragma once
#include "include.hpp"
#include <string_view>

constexpr std::string_view CURSOR_INVISIBLE = "\033[?25l";
constexpr std::string_view CURSOR_VISIBLE = "\033[?25h";
constexpr std::string_view RESET_COLOR = "\033[0m";

inline __attribute__((always_inline)) std::string frgb(int r,int g,int b) {
    return( "\033[38;2;"+std::to_string(r)+";"+std::to_string(g)+";"+std::to_string(b)+"m");
}
inline __attribute__((always_inline)) std::string brgb(int r,int g,int b) {
    return( "\033[48;2;"+std::to_string(r)+";"+std::to_string(g)+";"+std::to_string(b)+"m");
}
inline __attribute__((always_inline)) void setSize(int a,int b) {
    std::cout << "\033[8;"+std::to_string(a)+';'+std::to_string(b)+'t';
}

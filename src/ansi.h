#include "include.h"

// some basic functions for escape squences handling

#define CURSOR_INVISIBLE "\033[?25l"
#define CURSOR_VISIBLE "\033[?25h"
#define RESET_COLOR "\033[0m"
std::string frgb(int r,int g,int b) {
    return( "\033[38;2;"+std::to_string(r)+";"+std::to_string(g)+";"+std::to_string(b)+"m");
}
std::string brgb(int r,int g,int b) {
    return( "\033[48;2;"+std::to_string(r)+";"+std::to_string(g)+";"+std::to_string(b)+"m");
}
void setSize(int a,int b) {
    std::cout << "\033[8;"+std::to_string(a)+';'+std::to_string(b)+'t';
}
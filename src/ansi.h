#include "include.h"

// some basic functions for escape squences handling

#define CURSOR_INVISIBLE "\033[?25l"
#define CURSOR_VISIBLE "\033[?25h"
#define RESET_COLOR "\033[0m"
string frgb(int r,int g,int b) {
    return( "\033[38;2;"+to_string(r)+";"+to_string(g)+";"+to_string(b)+"m");
}
string brgb(int r,int g,int b) {
    return( "\033[48;2;"+to_string(r)+";"+to_string(g)+";"+to_string(b)+"m");
}
void setSize(int a,int b) {
    cout << "\033[8;"+to_string(a)+';'+to_string(b)+'t';
}
#include "snake.cpp"
#define FPS 4
int main() {
    //disable keyboard input from showing up on the screen
    //also make cursor invisible bcoz it looks annoying
    system("clear");
    enableEscapeSequences();
    cout << CURSOR_INVISIBLE;
    no_echo();

    //game loop
    Game g(20);
    while (!g.isGameOver()) {
        g.render();
        this_thread::sleep_for(1000ms/FPS);
    }

    //reset changes made earlier
    echo();
    cout << CURSOR_VISIBLE;
    system("clear");
}

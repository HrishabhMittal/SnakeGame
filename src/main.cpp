#include "snake.cpp"
#define FPS 4
int main() {
    //disable keyboard input from showing up on the screen
    //also make cursor invisible bcoz it looks annoying
    system("clear");
    enableEscapeSequences();
    std::cout << CURSOR_INVISIBLE;
    no_echo();

    //game loop
    Game g(20);
    while (!g.isGameOver()) {
        g.render();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)/FPS);
    }

    //reset changes made earlier
    echo();
    std::cout << CURSOR_VISIBLE;
    system("clear");
}

#include "snake.cpp"
#include <iostream>
#define FPS 10
int main() {
    enableEscapeSequences();
    std::cout<<"\033[H\033[2J";
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
    std::cout<<"\033[H\033[2J";
}

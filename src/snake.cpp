#include "ansi.h"
int randint(int a,int b) {
    std::random_device rd;
    std::uniform_int_distribution<int> x(a,b);
    return x(rd);
}
// handles everything about the game
class Game {
    std::vector<std::vector<int>> board;
    int length=5;
    int dirn=0;
    int size;
    bool isOver=false;
    void move(int&x,int&y) {
        // simply move in some direction according to
        //   0
        //   |
        //1--+--3
        //   |
        //   2
        switch (dirn) {
            case 0: x--;break;
            case 1: y--;break;
            case 2: x++;break;
            case 3: y++;break;
        }
        if (x==-1 || x==size || y==-1 || y==size) isOver=true; 
    }
    void input() {
        //pretty straightforward
        if (kbhit()) {
            //handling arrow keys
            #ifdef _WINDOWS_
            char x=_getch();
            // on cmd 
            // arrow keys give 0 <keycode>
            // on powershell
            // arrow keys give {some negative nos.} <keycode>
            //    72
            // 75 80 77
            if (x<=0) {
                while (x<=0) x=_getch();
            }
            switch (x) {
                case 72:
                    x='w'; break;
                case 75:
                    x='a'; break;
                case 80:
                    x='s'; break;
                case 77:
                    x='d'; break;
            }
            #else
            char x=getchar();
            // on bash
            // arrow keys give 
            // 27(ESC) 91([) then
            //    65 
            // 68 66 67
            if (x==27) {
                x=getchar();
                if (x==91) x=getchar();
            }
            switch (x) {
                case 65:
                    x='w'; break;
                case 68:
                    x='a'; break;
                case 66:
                    x='s'; break;
                case 67:
                    x='d'; break;
            }
            #endif
            //wasd input ==>
            switch (x) {
                case 'w': case 'W':
                    dirn=0; break;
                case 'a': case 'A':
                    dirn=1;break;
                case 's': case 'S':
                    dirn=2; break;
                case 'd': case 'D':
                    dirn=3; break;  
            }
        }
    }
    void genApple() {
        int ax=randint(0,size-1),ay=randint(0,size-1);
        //not an ideal way but works for now
        //TO CHANGE IN THE FUTURE (PROBABLY)
        while (board[ax][ay]!=0) {
            ax=randint(0,size-1);
            ay=randint(0,size-1);
        }
        //new apple :)
        board[ax][ay]=-1;
    }
    void update() {
        // update according to the current key being pressed
        input();
        int x,y;
        int max=0;
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                if (board[i][j]>max) x=i,y=j,max=board[i][j];
            }
        }
        // move x,y to the position snake is moving to
        move(x,y);
        // if out of bouds return
        if (isOver) return;
        // if moving to the last head position keep moving in the some direction
        if (board[x][y]==max-1) {
            dirn=(dirn+2)%4;
            move(x,y);
            move(x,y);
        }
        // if apple==eaten length++, make new apple
        // no need to decrement length of body
        if (board[x][y]==-1) {
            length++;
            genApple();
        }
        // if colliding w itself
        else if (board[x][y]!=0) isOver=true;
        // decrement the vals of all body positions, this way
        // tail vanishes without even keeping track of it
        else {
            for (int i=0;i<size;i++) {
                for (int j=0;j<size;j++) {
                    if (board[i][j]>0) board[i][j]--;
                }
            }
        }
        if (isOver) return;
        //new head position
        board[x][y]=length;
    }
    void print() {
        setSize(size+1,size*2);
        // better for performance to store the entire thing in a string first
        // than to make so many cout calls
        // although due to low frame rate this doesnt matter here
        std::string out="\033[HSNAKE GAME              Score:"+std::to_string(length-5)+'\n';
        std::string prevcol=RESET_COLOR;
        std::string apple=brgb(250,0,0);
        std::string snake=brgb(0,250,0);
        for (int i=0;i<size;i++) {
            for (int j=0;j<size;j++) {
                if (board[i][j]==-1) {
                    if (prevcol!=apple) {
                        out+=apple;
                        prevcol=apple;
                    }
                } else if (board[i][j]==0) {
                    if (prevcol!=brgb(0,0,0)) {
                        out+=brgb(0,0,0);
                        prevcol=brgb(0,0,0);
                    }
                }
                else {
                    if (prevcol!=snake) {
                        out+=snake;
                        prevcol=snake;
                    }
                }
                out+="  ";
            }
            out+='\n';
        }
        out.pop_back();
        out+=RESET_COLOR;
        std::cout << out;
    }
public:
    Game(int s) {
        size=s;
        board=std::vector(size,std::vector(size,0));
        board[size/2][size/2]=length;
        genApple();
    }
    bool isGameOver() {
        return isOver;
    }
    void render() {
        update();
        print();
    }
};
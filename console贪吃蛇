# include <bits/stdc++.h>
# include <conio.h>
# include <windows.h>
# define W 26
# define H 20
using namespace std;

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    null
} status[H][W];

int delay = 250;
int score = 0;

HANDLE hOutput, hOutBuf;//控制台屏幕缓冲区句柄
HANDLE *houtpoint;//显示指针
COORD coord = { 0,0 };
//双缓冲处理显示
DWORD bytes = 0;
bool showcircle = false;

char mp[H][W] = {
    "#########################",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#          **           #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#                       #",
    "#########################"
};

pair<int,int> head = {9,12};
pair<int,int> tail = {9,11};

void init() {
    for (int i = 1; i <= 18; ++i) {
        for (int j = 1; j <= 23; ++j) {
            status[i][j] = null;
        }
    }
    status[9][12] = RIGHT;
    status[9][11] = RIGHT;
    while (true) {
        int rx = 1 + rand()%23;
        int ry = 1 + rand()%18;
        if (mp[rx][ry] == ' ') {
            mp[rx][ry] = 'O';
            return ;
        }
    }
}


void display() {
    showcircle = !showcircle;
    if (showcircle) {
        houtpoint = &hOutput;
    }
    else {
        houtpoint = &hOutBuf;
    }
    for (int i = 0; i < H; ++i) {
        coord.X = 0;
        coord.Y = i;
        WriteConsoleOutputCharacterA(*houtpoint, (char*)mp[i], W, coord, &bytes);
    }
    //设置新的缓冲区为活动显示缓冲
    SetConsoleActiveScreenBuffer(*houtpoint);
    Sleep(delay);
}

void dfs(int hx,int hy) {
    if (status[hx][hy] == UP) {
        mp[hx][hy] = mp[hx+1][hy];
        if (mp[hx][hy] == ' ') {
            tail = {hx-1,hy};
            status[hx][hy] = null;
            return ;
        }
        dfs(hx+1,hy);
    }
    else if (status[hx][hy] == DOWN) {
        mp[hx][hy] = mp[hx-1][hy];
        if (mp[hx][hy] == ' ') {
            tail = {hx+1,hy};
            status[hx][hy] = null;
            return ;
        }
        dfs(hx-1,hy);
    }
    else if (status[hx][hy] == LEFT) {
        mp[hx][hy] = mp[hx][hy+1];
        if (mp[hx][hy] == ' ') {
            tail = {hx,hy-1};
            status[hx][hy] = null;
            return ;
        }
        dfs(hx,hy+1);
    }
    else if (status[hx][hy] == RIGHT) {
        mp[hx][hy] = mp[hx][hy-1];
        if (mp[hx][hy] == ' ') {
            tail = {hx,hy+1};
            status[hx][hy] = null;
            return ;
        }
        dfs(hx,hy-1);
    }
}

void operation() {
    while (true) {
        int hx = head.first; // 蛇头x坐标
        int hy = head.second; // 蛇头y坐标
        // 键盘相应事件
        if (kbhit()) {
            char ch = getch();
            if (ch == 'w' && status[hx][hy] != DOWN) { // 往上
                --hx;
                status[hx][hy] = UP;
            }
            else if (ch == 's' && status[hx][hy] != UP) { // 往下
                ++hx;
                status[hx][hy] = DOWN;
            }
            else if (ch == 'a' && status[hx][hy] != RIGHT) { // 往左
                --hy;
                status[hx][hy] = LEFT;
            }
            else if (ch == 'd' && status[hx][hy] != LEFT) { // 往右
                ++hy;
                status[hx][hy] = RIGHT;
            }
            else {
                goto T1;
            }
        } else {
            T1:
            if (status[hx][hy] == UP) {
                --hx;
                status[hx][hy] = UP;
            }
            if (status[hx][hy] == DOWN) {
                ++hx;
                status[hx][hy] = DOWN;
            }
            if (status[hx][hy] == LEFT) {
                --hy;
                status[hx][hy] = LEFT;
            }
            if (status[hx][hy] == RIGHT) {
                ++hy;
                status[hx][hy] = RIGHT;
            }
        }
        if (mp[hx][hy] == '#' || mp[hx][hy] == '*') {
            printf("\a");
            printf("You lose! Get %d points",score);
            exit(0);
        }
        // ----------------
        if (mp[hx][hy] == 'O') {
            int tx = tail.first;
            int ty = tail.second;
            if (status[tx][ty] == UP) {
                ++tx;
                status[tx][ty] = UP;
                mp[tx][ty] = '*';
            }
            if (status[tx][ty] == DOWN) {
                --tx;
                status[tx][ty] = DOWN;
                mp[tx][ty] = '*';
            }
            if (status[tx][ty] == LEFT) {
                ++ty;
                status[tx][ty] = LEFT;
                mp[tx][ty] = '*';
            }
            if (status[tx][ty] == RIGHT) {
                --ty;
                status[tx][ty] = RIGHT;
                mp[tx][ty] = '*';
            }
            tail = {tx,ty};
            while (true) {
                int rx = 1 + rand()%23;
                int ry = 1 + rand()%18;
                if (mp[rx][ry] == ' ') {
                    mp[rx][ry] = 'O';
                    break;
                }
            }
            delay -= 10; // 运动加速，但不得少于100
            delay = delay > 100 ? delay : 100;
            score += 10; // 得分增加
        }
        dfs(hx,hy); // 新蛇头，进行蛇蠕动
        head = {hx,hy};
        display();
    }
}

int main() {
    init();

    //创建新的控制台缓冲区
    hOutBuf = CreateConsoleScreenBuffer(
        GENERIC_WRITE,//定义进程可以往缓冲区写数据
        FILE_SHARE_WRITE,//定义缓冲区可共享写权限
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    hOutput = CreateConsoleScreenBuffer(
        GENERIC_WRITE,//定义进程可以往缓冲区写数据
        FILE_SHARE_WRITE,//定义缓冲区可共享写权限
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    //隐藏两个缓冲区的光标
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = 0;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hOutput, &cci);
    SetConsoleCursorInfo(hOutBuf, &cci);

    operation();
    getchar();
    return 0;
}

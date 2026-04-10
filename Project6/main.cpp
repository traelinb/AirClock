#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <ctime>
#include <cmath>
using namespace std;
const double PI= acos(-1.0);
IMAGE imgBackground;
IMAGE imgApple;

struct Clock{
            int x, y, r; 
            void init(int _x, int _y, int _r)
            {
                x = _x;
                y = _y;
                r = _r;
            }
            // 绘制表盘函数
            void drawFace()
            {
                
                putimage(320-660, 350 -500, &imgApple, SRCAND);
                settextcolor(RED);
                settextstyle(40, 0, "Jokerman");
                setbkmode(TRANSPARENT);
                //文字背景透明       

                for (int i = 1; i <= 12 ; i++) {
                    //角度
                    double angle = i * (PI / 6);

                    //坐标
                    int numX = x + (int)(r * 0.8 * sin(angle));
                    int numY = y - (int)(r * 0.8 * cos(angle));

                    //将数字转为字符串
                    char s[3];
                    sprintf_s(s, "%d", i);

                    //数字居中
                    outtextxy(numX - textwidth(s) /    2, numY - textheight(s) / 2, s);
                }
            }

            
            void drawHands(int h, int m, int s)
            {
                double s_angle = s * (PI / 30);
                double m_angle = (m + s / 60.0) * (PI / 30);
                double h_angle = (h % 12 + m / 60.0) * (PI / 6);

                // 时针
                setcolor(WHITE);
                setlinestyle(PS_SOLID,8);
                line(x, y, x + (int)(r * 0.5 * sin(h_angle)), y - (int)(r * 0.5 * cos(h_angle)));

                // 分针
                setlinestyle(PS_SOLID,4);
                line(x, y, x + (int)(r * 0.7 * sin(m_angle)), y - (int)(r * 0.7 * cos(m_angle)));

                // 秒针
                setcolor(RED);
                setlinestyle(PS_SOLID,2);
                line(x, y, x + (int)(r * 0.9 * sin(s_angle)), y - (int)(r * 0.9 * cos(s_angle)));

                setfillcolor(LIGHTGRAY);
                solidcircle(x, y, 5);//画中心点盖住交汇处
            }
};

int main()
{
    initgraph(640, 720);
    loadimage(&imgBackground, ("abc.jpg"), 640, 720);
    loadimage(&imgApple, ("apple.png"), 1300, 700);
    Clock clock;
    clock.init(300, 250, 100); //一个半径 100 的时钟

    //防止画面闪烁
    BeginBatchDraw();

    while (!_kbhit()) // 无键盘操作时进入循环
    {
        //不停获取当前时间
        struct tm t;
        time_t now;
        time(&now);
        localtime_s(&t, &now);

        //清除上一帧画面
        cleardevice();
        putimage(  0, 0 , &imgBackground);
        //重新绘制表盘和数字
        clock.drawFace();

        //根据新时间绘制指针
        clock.drawHands(t.tm_hour, t.tm_min, t.tm_sec);

        FlushBatchDraw();
        Sleep(100);
    }

    EndBatchDraw();
    closegraph();
    return 0;
}
#include <cstdlib>
#include <Windows.h>
#include <ctime>
#include <conio.h>
#include <iostream>
#include "PlayField.h"
#include "painter.h"

int speed;
double interval;
bool pause;

void set_speed(int nspeed)
{
    if (nspeed <= 0||nspeed>50)
        return;
    speed = nspeed;
    interval = 1000.0 / speed;
}

PlayField well;

void init() 
{
    well = PlayField();
    well.init();

    srand(time(0));
    set_speed(3);
    pause = false;
}

int main(){
    init();
    int key_id,las_mov_time=clock();
    while (1) {//main message loop
        if (_kbhit()) {
            key_id = _getch();
            if (key_id == 'p' || key_id == 'P') {
                if (pause) {
                    pause = false;
                    paint_at_center(PlayField::T_WIDTH / 2.0, PlayField::T_HEIGHT + 1,NORMAL,"          ");
                }
                else {
                    pause = true;
                    paint_at_center(PlayField::T_WIDTH / 2.0, PlayField::T_HEIGHT + 1, NORMAL, "paused");
                }
            }
            else if (key_id == 'r' || key_id == 'R') {
                init();
                las_mov_time = clock();
                continue;
            }
            if (!pause && !well.failed()) {
                switch (key_id) {

                case 'a':case 'A':
                    well.move(-1);
                    break;
                case 'd':case 'D':
                    well.move(1);
                    break;
                case 'q':case 'Q':
                    well.rotate(-1);
                    break;
                case 'e':case 'E':
                    well.rotate(1);
                    break;
                case 's':case 'S':
                    well.fast_fall();
                    las_mov_time = clock();
                    break;
                }
            }
        }
        if (!pause && !well.failed()) {
            int tim = clock();
            if (tim - las_mov_time > interval) {
                well.fall();
                las_mov_time = tim;
            }
            set_speed(3 + well.get_score() / 400);
        }
        Sleep(1);
    }
}

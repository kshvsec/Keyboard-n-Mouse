#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include "controllers.h"

void moveMouse(int x, int y){
    SetCursorPos(x, y);
}

void lefiClick(){
    INPUT input;
    input.type = 0;
    input.mi.

}
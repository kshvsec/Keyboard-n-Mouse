#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include "controllers.h"

void moveMouse(int x, int y){
    SetCursorPos(x, y);
}

void leftClick(){
    INPUT input;
    input.type = 0;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

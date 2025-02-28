#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include "controllers.h"

void moveMouse(int x, int y){
    SetCursorPos(x, y);
}

void leftClick() {
    INPUT input;
    input.type = 0;
    input.mi.dwFlags = 0x0002; //MOUSEEVENTF_LEFTDOWN
    SendInput(1, &input, sizeof(INPUT));
    sleepInMs(100);
    input.mi.dwFlags = 0x0004; //MOUSEEVENTF_LEFTUP
    SendInput(1, &input, sizeof(INPUT));
}

void holdLeftClick(int time){
    INPUT input;
    input.type = 0;
    input.mi.dwFlags = 0x0002; //MOUSEEVENTF_LEFTDOWN
    SendInput(1, &input, sizeof(INPUT));
    sleepInS(time);
    input.type = 0;
    input.mi.dwFlags = 0x0004; //MOUSEEVENTF_LEFTUP
    SendInput(1, &input, sizeof(INPUT));
}

void rightClick() {
    INPUT input;
    input.type = 0;
    input.mi.dwFlags = 0x0008; //MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    input.mi.dwFlags = 0x0010; // MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}

void holdRightClick() {
    INPUT input;
    input.type = 0;
    input.mi.dwFlags = 0x0008; //MOUSEEVENTF_RIGHTDOWN
    SendInput(1, &input, sizeof(INPUT));
    sleepInS(time);
    input.type = 0;
    input.mi.dwFlags = 0x0010; //MOUSEEVENTF_RIGHTUP
    SendInput(1, &input, sizeof(INPUT));
}

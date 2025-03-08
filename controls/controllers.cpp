#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include "controllers.hpp"
#include <iostream>
#include <algorithm>

/*
1 = Input as keyboard
0 = Input as mouse

0 on .dwFlags for keyboard = press
*/

void moveMouse(int x, int y){
    SetCursorPos(x, y);
}

void leftClick() {
    INPUT input = {0};
    input.type = 0;
    input.mi.dwFlags = 0x0002; //MOUSEEVENTF_LEFTDOWN
    
    SendInput(1, &input, sizeof(INPUT));
    sleepInMs(100);
    input.mi.dwFlags = 0x0004; //MOUSEEVENTF_LEFTUP
    
    SendInput(1, &input, sizeof(INPUT));
}

void holdLeftClick(int time){
    INPUT input = {0};
    input.type = 0;
    input.mi.dwFlags = 0x0002; //MOUSEEVENTF_LEFTDOWN
    
    SendInput(1, &input, sizeof(INPUT));
    sleepInS(time);
    input.type = 0;
    input.mi.dwFlags = 0x0004; //MOUSEEVENTF_LEFTUP
    
    SendInput(1, &input, sizeof(INPUT));
}

void rightClick() {
    INPUT input = {0};
    input.type = 0;
    input.mi.dwFlags = 0x0008; //MOUSEEVENTF_RIGHTDOWN;
    
    SendInput(1, &input, sizeof(INPUT));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    input.mi.dwFlags = 0x0010; // MOUSEEVENTF_RIGHTUP;
    
    SendInput(1, &input, sizeof(INPUT));
}

void holdRightClick(int time) {
    INPUT input = {0};
    input.type = 0;
    input.mi.dwFlags = 0x0008; //MOUSEEVENTF_LEFTDOWN
    
    SendInput(1, &input, sizeof(INPUT));
    
    sleepInS(time);
    input.type = 0;
    input.mi.dwFlags = 0x0010; //MOUSEEVENTF_LEFTUP
    
    SendInput(1, &input, sizeof(INPUT));
}

void SpecialKeys(std::string key){
    dict specialKeys;

    specialKeys["ENTER"] = VK_RETURN;
    specialKeys["SPACE"] = VK_SPACE;
    specialKeys["TAB"] = VK_TAB;
    specialKeys["BACKSPACE"] = VK_BACK;
    specialKeys["ESC"] = VK_ESCAPE;
    specialKeys["DEL"] = VK_DELETE;
    specialKeys["UP"] = VK_UP;
    specialKeys["DOWN"] = VK_DOWN;
    specialKeys["LEFT"] = VK_LEFT;
    specialKeys["RIGHT"] = VK_RIGHT;
    specialKeys["F1"] = VK_F1;
    specialKeys["F2"] = VK_F2;
    specialKeys["F3"] = VK_F3;
    specialKeys["F4"] = VK_F4;
    specialKeys["F5"] = VK_F5;
    specialKeys["F6"] = VK_F6;
    specialKeys["F7"] = VK_F7;
    specialKeys["F8"] = VK_F8;
    specialKeys["F9"] = VK_F9;
    specialKeys["F10"] = VK_F10;
    specialKeys["F11"] = VK_F11;
    specialKeys["F12"] = VK_F12;

    int sizeofkeys = specialKeys.size();
    int i = 0;
    auto item = specialKeys.begin();

    while (i < sizeofkeys){
        if (item->first == key) {
            INPUT input = {0};
            input.type = 1;
            input.ki.dwFlags = 0;
            input.ki.wVk = item->second;

            SendInput(1, &input, sizeof(INPUT));

            input.ki.dwFlags = KEYEVENTF_KEYUP;

            SendInput(1, &input, sizeof(INPUT));
        }
        i++;
        item++;
    }
}

void typeString(const std::string& text) {
    for (char key : text) {
        SHORT vkCode = VkKeyScan(key);
        bool isShiftRequired = (vkCode & 0x0100);

        INPUT inputs[4] = {};  
        int inputCount = 0;

        if (isShiftRequired) {
            inputs[inputCount].type = INPUT_KEYBOARD;
            inputs[inputCount].ki.wVk = VK_SHIFT;
            inputCount++;
        }

        inputs[inputCount].type = INPUT_KEYBOARD;
        inputs[inputCount].ki.wVk = LOBYTE(vkCode);
        inputCount++;

        inputs[inputCount].type = INPUT_KEYBOARD;
        inputs[inputCount].ki.wVk = LOBYTE(vkCode);
        inputs[inputCount].ki.dwFlags = KEYEVENTF_KEYUP;
        inputCount++;

        if (isShiftRequired) {
            inputs[inputCount].type = INPUT_KEYBOARD;
            inputs[inputCount].ki.wVk = VK_SHIFT;
            inputs[inputCount].ki.dwFlags = KEYEVENTF_KEYUP;
            inputCount++;
        }

        SendInput(inputCount, inputs, sizeof(INPUT));
    }
}

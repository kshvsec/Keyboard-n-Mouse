#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include "controllers.hpp"

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
            INPUT input;
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

void typeString(std::string text) {
    dict alphabetKeys;

    alphabetKeys["A"] = 0x41;
    alphabetKeys["B"] = 0x42;
    alphabetKeys["C"] = 0x43;
    alphabetKeys["D"] = 0x44;
    alphabetKeys["E"] = 0x45;
    alphabetKeys["F"] = 0x46;
    alphabetKeys["G"] = 0x47;
    alphabetKeys["H"] = 0x48;
    alphabetKeys["I"] = 0x49;
    alphabetKeys["J"] = 0x4A;
    alphabetKeys["K"] = 0x4B;
    alphabetKeys["L"] = 0x4C;
    alphabetKeys["M"] = 0x4D;
    alphabetKeys["N"] = 0x4E;
    alphabetKeys["O"] = 0x4F;
    alphabetKeys["P"] = 0x50;
    alphabetKeys["Q"] = 0x51;
    alphabetKeys["R"] = 0x52;
    alphabetKeys["S"] = 0x53;
    alphabetKeys["T"] = 0x54;
    alphabetKeys["U"] = 0x55;
    alphabetKeys["V"] = 0x56;
    alphabetKeys["W"] = 0x57;
    alphabetKeys["X"] = 0x58;
    alphabetKeys["Y"] = 0x59;
    alphabetKeys["Z"] = 0x5A;

    alphabetKeys["a"] = 0x41;
    alphabetKeys["b"] = 0x42;
    alphabetKeys["c"] = 0x43;
    alphabetKeys["d"] = 0x44;
    alphabetKeys["e"] = 0x45;
    alphabetKeys["f"] = 0x46;
    alphabetKeys["g"] = 0x47;
    alphabetKeys["h"] = 0x48;
    alphabetKeys["i"] = 0x49;
    alphabetKeys["j"] = 0x4A;
    alphabetKeys["k"] = 0x4B;
    alphabetKeys["l"] = 0x4C;
    alphabetKeys["m"] = 0x4D;
    alphabetKeys["n"] = 0x4E;
    alphabetKeys["o"] = 0x4F;
    alphabetKeys["p"] = 0x50;
    alphabetKeys["q"] = 0x51;
    alphabetKeys["r"] = 0x52;
    alphabetKeys["s"] = 0x53;
    alphabetKeys["t"] = 0x54;
    alphabetKeys["u"] = 0x55;
    alphabetKeys["v"] = 0x56;
    alphabetKeys["w"] = 0x57;
    alphabetKeys["x"] = 0x58;
    alphabetKeys["y"] = 0x59;
    alphabetKeys["z"] = 0x5A;

    // ISSUE FIX : space character
    alphabetKeys[" "] = VK_SPACE;

    int i = 0;

    while (i < text.size()) {
        std::string key(1, text[i]);
        bool isUpper = isupper(text[i]);

        if (alphabetKeys.find(key) != alphabetKeys.end()) {
            WORD vkCode = alphabetKeys[key];

            INPUT input = {};
            input.type = INPUT_KEYBOARD;

            if (isUpper) {
                INPUT shiftPress = {};
                shiftPress.type = INPUT_KEYBOARD;
                shiftPress.ki.wVk = VK_SHIFT;
                shiftPress.ki.dwFlags = 0;
                SendInput(1, &shiftPress, sizeof(INPUT));
            }

            input.ki.wVk = vkCode;
            input.ki.dwFlags = 0;
            SendInput(1, &input, sizeof(INPUT));

            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));

            if (isUpper) {
                INPUT shiftRelease = {};
                shiftRelease.type = INPUT_KEYBOARD;
                shiftRelease.ki.wVk = VK_SHIFT;
                shiftRelease.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &shiftRelease, sizeof(INPUT));
            }
        }
        i++;
    }
}

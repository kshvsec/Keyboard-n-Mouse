#ifndef controllers_h
#define controllers_h

#include <windows.h>
#include <string>
#include <thread>
#include <chrono>

void moveMouse(int x, int y);
void leftClick();
void rightClick();
void pressKey(std::string key);
void typeString(const std::string text);

#endif
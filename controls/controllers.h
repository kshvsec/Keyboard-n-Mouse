#ifndef controllers_h
#define controllers_h

#include <windows.h>
#include <string>
#include <thread>
#include <chrono>

// oneline defined functions for thread sleep management

#define sleepInS(x) std::this_thread::sleep_for(std::chrono::seconds(x));
#define sleepInMs(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

void moveMouse(int x, int y);

void leftClick();
void holdLeftClick(int time); // in seconds

void rightClick();
void holdRightClick(int time); // in seconds

void pressKey(std::string key);
void typeString(const std::string text);

#endif

#ifndef controllers_h
#define controllers_h

#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <algorithm>

// oneline defined functions for thread sleep management

typedef std::unordered_map<std::string, WORD> dict; // for adding and removing specialkeys

#define sleepInS(x) std::this_thread::sleep_for(std::chrono::seconds(x));
#define sleepInMs(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

void moveMouse(int x, int y);

void leftClick();
void holdLeftClick(int time); // in seconds

void rightClick();
void holdRightClick(int time); // in seconds

void SpecialKeys(std::string key);
void typeString(std::string text);

#endif
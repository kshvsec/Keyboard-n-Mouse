#include "controls/controllers.h"
#include <iostream>

// g++ server.cpp controls/controllers.cpp -o server

int main(){
    // testing
    std::this_thread::sleep_for(1000ms);
    SpecialKeys("BACKSPACE");
}

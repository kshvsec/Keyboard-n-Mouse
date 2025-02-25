#include "controls/controllers.h"
#include <iostream>

// cd "e:\codes\remote\" ; if ($?) { g++ server.cpp controls/controllers.cpp -o server } ; if ($?) { .\server }

using namespace std;

int main(){
    std::this_thread::sleep_for(5000ms);
    leftClick();
}

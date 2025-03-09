#include "modules.hpp"

void executeSysCommands(std::string command) {
    std::string cmdCommand = "cmd /c " + command;
    system(cmdCommand.c_str());
}

void openlink(std::string link) {
    std::string command = "start "+link;
    system(command.c_str());
}
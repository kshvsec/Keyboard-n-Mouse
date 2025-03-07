#include "controls/controllers.h"
#include <iostream>

// cd "e:\codes\remote\" ; if ($?) { g++ server.cpp controls/controllers.cpp -o server } ; if ($?) { .\server }

using namespace std;

void installModule(){
    const char *command = R"(
        powershell -ExecutionPolicy Bypass -NoProfile -Command 
        "Install-Module -Name BurntToast"
    )";
    system(command);
}

void clear(){
    system("clear || cls");
}

int main(){

    std::cout << "This application uses BurntToast to display Windows Toast Notifications, Installing it right now..." << std::endl;
    sleepInS(2);
    installModule();

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

    std::string inputCommand(1024, '\0');
    recv(clientSocket, &inputCommand[0], sizeof(inputCommand), 0);
    std::cout << "Received: " << inputCommand << std::endl;

    if (inputCommand == "mouse"){

    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}

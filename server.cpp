#include "controls/controllers.hpp"
#include <iostream>
#include <string>

// cd "e:\codes\remote\" ; if ($?) { g++ server.cpp controls/controllers.cpp -o server -lws2_32} ; if ($?) { .\server }

#define CLIENT_LIMIT 1

using namespace std;

void showNotification(const std::string& title, const std::string& des) {
    std::string command = "python modules/ntf/ntf.py \"" + title + "\" \"" + des + "\" ";
    system(command.c_str());
}

void clear(){
    system("clear || cls");
}

int main() {

    std::string ipportstring;

    std::cout << "Enter IP:Port: ";
    std::cin >> ipportstring;

    int position = ipportstring.find(":");

    std::string ipaddress = ipportstring.substr(0, position);
    int port = std::stoi(ipportstring.substr(position+1));

    //return 0; //debug
    // std::cout << position; // debug
    // return 0; // debug

    showNotification("Getting ready", "Your system is getting ready to look for the remote client to connect, please wait..");

    // wsadata
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // socket (initial + config)
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ipaddress.c_str());
    serverAddr.sin_port = htons(port);

    // bind and listen
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, CLIENT_LIMIT); // <--- change this value as per needs

    // loading connection address
    clear();
    std::cout << "Hosting on " << ipaddress << ":" << port;
    showNotification("Ready", "Please enter the address in your remote client and connect to the system.");

    // accepting client
    SOCKET clientSocket;
    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

    clear();
    std::cout << "Client connected";

    while (true) {
        // Handling client
        std::string inputCommand(1024, '\0');
        int bytesReceived = recv(clientSocket, &inputCommand[0], inputCommand.size(), 0);

        if (bytesReceived <= 0) continue;  // Handle disconnection or errors

        // std::cout << "Received: " << inputCommand << std::endl; // debug, comment out

        /*
        
        PARSING THE COMMANDS
        
        */
        if (strncmp(inputCommand.c_str(), "movemouse", 9) == 0) {
            showNotification("Mouse Engaged", "Please send the coordinates for the mouse");

            std::string coordinates(1024, '\0');
            int bytesReceivedCoords = recv(clientSocket, &coordinates[0], coordinates.size(), 0);

            int x, y;
            sscanf(coordinates.c_str(), "%d %d", &x, &y);
            moveMouse(x, y);
            std::cout << "Moved cursor to " << x << ", " << y << std::endl;
        }

        if (strncmp(inputCommand.c_str(), "leftclick", 9) == 0){
            showNotification("Left Click", "Left Click Initiated");
            leftClick();
            std::cout << "Left Click done" << std::endl;
        }

        if (strncmp(inputCommand.c_str(), "rightclick", 10) == 0){
            showNotification("Right Click", "Right Click Initiated");
            rightClick();
            std::cout << "Right Click done" << std::endl;
        }

        if (strncmp(inputCommand.c_str(), "specialkey", 10) == 0){
            showNotification("Locked Special Keys", "Please send the special key you want to send");
            
            std::string specialkeyinput(1024, '\0');
            int bytesReceivedCoords = recv(clientSocket, &specialkeyinput[0], specialkeyinput.size(), 0);
            
            SpecialKeys(specialkeyinput);
            std::cout << "Special Key Input" << std::endl; 
        }

        if (strncmp(inputCommand.c_str(), "type", 4) == 0){
            showNotification("Locked Keyboard", "Please send a string to type next");

            std::string typeoutstring;
            int bytesReceivedCoords = recv(clientSocket, &typeoutstring[0], typeoutstring.size(), 0);

            typeString(typeoutstring);
            std::cout << "typed string" << std::endl;
        }
    }

    // bye bye client (do not need this because the client is gonna be connected forever)
    /*
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    */
}

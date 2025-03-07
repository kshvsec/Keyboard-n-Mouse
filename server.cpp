#include "controls/controllers.hpp"
#include <iostream>
#include <string>

// cd "e:\codes\remote\" ; if ($?) { g++ server.cpp controls/controllers.cpp -o server -lws2_32} ; if ($?) { .\server }

#define CLIENT_LIMIT 1

using namespace std;

void showNotification(const std::string& title, const std::string& des) {
    std::string command = "python ntf/ntf.py \"" + title + "\" \"" + des + "\" ";
    system(command.c_str());
}

void clear(){
    system("clear || cls");
}

int main(){
    
    showNotification("Getting ready", "Your system is getting ready to look for the remote client to connect, please wait..");

    // wsadata
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // socket (initial + config)
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(4567); // TODO : bind the same port to client

    // bind and listen
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, CLIENT_LIMIT); // <--- change this value as per needs

    // loading connection address
    char h[1024];
    gethostname(h, sizeof(h));
    struct addrinfo *r;
    clear();
    
    std::cout << "Machine connection address: " << inet_ntoa(*(struct in_addr*)gethostbyname(h)->h_addr) << std::endl;
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

        std::cout << "Received: " << inputCommand << std::endl;

        // Mouse movement
        if (strncmp(inputCommand.c_str(), "movemouse", 9) == 0) {
            showNotification("Mouse Engaged", "Please send the coordinates for the mouse");

            std::string coordinates(1024, '\0');
            int bytesReceivedCoords = recv(clientSocket, &coordinates[0], coordinates.size(), 0);

            if (bytesReceivedCoords > 0) {
                int x, y;
                sscanf(coordinates.c_str(), "%d %d", &x, &y);
                moveMouse(x, y);
                std::cout << "Moved cursor to " << x << ", " << y << std::endl;
            }
        }
    }

    // bye bye client (do not need this because the client is gonna be connected forever)
    /*
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    */
}

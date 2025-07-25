#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

bool initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void InteractWithClient(SOCKET clientSocket, vector<SOCKET>& clients) {
    char buffer[4096];
    while (1) {
        int bytesrecd = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesrecd > 0) {
            buffer[bytesrecd] = '\0'; // Null terminate
            string message(buffer);
            cout << "Message from client: " << message << endl;

            // Send response to client
            string reply = "Message received: " + message;
            send(clientSocket, reply.c_str(), (int)reply.size(), 0);

            // Forward message to all other clients
            for (auto client : clients) {
                if (client != clientSocket) {
                    send(client, message.c_str(), (int)message.length(), 0);
                }
            }
        }
        else {
            cout << "Receive failed or connection closed" << endl;
            break; // Exit loop if client disconnects
        }
    }

    // Remove the client from vector
    auto it = find(clients.begin(), clients.end(), clientSocket);
    if (it != clients.end()) {
        clients.erase(it);
    }

    closesocket(clientSocket);
}

int main() {
    if (!initialize()) {
        cout << "Winsock initialization failed" << endl;
        return 1;
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        cout << "Failed socket creation" << endl;
        WSACleanup();
        return 1;
    }

    int port = 12345;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    // Corrected InetPton usage
    if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
        cout << "Setting address structure failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (bind(listenSocket, (sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR) {
        cout << "Bind failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Listen failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server started listening on port: " << port << endl;
    vector<SOCKET> clients;

    // Accept clients in loop
    while (1) {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            cout << "Invalid client socket" << endl;
            continue;
        }

        clients.push_back(clientSocket);
        thread t1(InteractWithClient, clientSocket, ref(clients));
        t1.detach(); // Detach thread so it runs independently
    }

    closesocket(listenSocket);
    WSACleanup();


    return 0;
}

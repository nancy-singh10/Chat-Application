#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <string>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

bool initialize();
void SendChatMessage(SOCKET s);
void ReceiveChatMessage(SOCKET s);

bool initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void SendChatMessage(SOCKET s) {
    cout << "Enter your chat name: ";
    string name;
    getline(cin, name);

    string message;
    while (1) {
        getline(cin, message);
        string msg = name + " : " + message;
        int bytesent = send(s, msg.c_str(), (int)msg.length(), 0);
        if (bytesent == SOCKET_ERROR) {
            cout << "Error sending message" << endl;
            break;
        }
        if (message == "quit") {
            cout << "Stopping the application..." << endl;
            break;
        }
    }
    closesocket(s);
    WSACleanup();
}

void ReceiveChatMessage(SOCKET s) {
    char buffer[4096];
    while (1) {
        int bytesrecd = recv(s, buffer, sizeof(buffer) - 1, 0);
        if (bytesrecd > 0) {
            buffer[bytesrecd] = '\0';
            cout << buffer << endl;
        }
        else {
            cout << "Disconnected from the server" << endl;
            break;
        }
    }
    closesocket(s);
    WSACleanup();
}

int main() {
    if (!initialize()) {
        cout << "Winsock initialization failed" << endl;
        return 1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        cout << "Invalid socket" << endl;
        WSACleanup();
        return 1;
    }

    int port = 12345;
    string serverIP = "127.0.0.1";

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, serverIP.c_str(), &(serverAddr.sin_addr)) <= 0) {
        cout << "Invalid address" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    if (connect(s, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Unable to connect to server" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    cout << "Connected to server successfully" << endl;

    // ✅ Renamed to avoid WinAPI conflict
    thread senderthread(SendChatMessage, s);
    thread receiverthread(ReceiveChatMessage, s);

    senderthread.join();
    receiverthread.join();

    return 0;
}

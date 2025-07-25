# Real-Time Chat Application (C++ | Winsock | Multithreading)

This is a **real-time chat application** built using **C++**, **Winsock API**, and **multithreading**, supporting multiple clients connected to a server for **bidirectional communication**.

---
![Project Screenshot](Screenshot%20(3).png)

## ⚡ Features
- **Real-Time Messaging** between multiple clients.
- **Multithreaded Server**: Handles multiple clients concurrently.
- **Client-Server Architecture** using **TCP/IP sockets**.
- **Message Broadcasting**: Messages sent by one client are forwarded to all others.
- **Error Handling** for stable connections and graceful client disconnection.

---

## 🛠️ Tech Stack
- **Language**: C++
- **Networking**: Winsock API (Windows Sockets)
- **Concurrency**: `std::thread`
- **Protocol**: TCP/IP

---



---

## ▶️ How It Works
1. **Server**:
    - Initializes Winsock.
    - Creates a listening socket on `port 12345`.
    - Accepts client connections and spawns threads for each client.
    - Forwards messages from one client to all others.

2. **Client**:
    - Connects to the server using IP (`127.0.0.1` for local testing).
    - Sends messages with username prefix.
    - Listens for messages from other clients using a dedicated thread.

---

## ⚙️ Installation & Run

### **1. Clone the Repository**
```bash
git clone https://github.com/nancy-singh10/Chat-Application.git
cd Chat-Application

## 📂 Project Structure

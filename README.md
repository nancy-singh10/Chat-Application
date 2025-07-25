# **Emergency LAN Chat System**  
*(C++ | Winsock | Multithreading)*

This is a **LAN-based real-time chat application** built using **C++**, **Winsock API**, and **multithreading**, designed to provide **reliable communication even during internet outages**. The system supports **multiple clients connected to a server** for **bidirectional messaging** over a local network.

---

## 📸 **Project Screenshot**
![Project Screenshot](assets/screenshot.png)  
*(Replace with your actual image path)*

---

## ⚡ **Features**
- ✅ Real-Time Messaging between multiple clients  
- ✅ **Multithreaded Server** – Handles multiple clients concurrently  
- ✅ **Client-Server Architecture** using **TCP/IP sockets**  
- ✅ **Message Broadcasting** – One client’s message is sent to all others  
- ✅ **Robust Error Handling** for stable connections and graceful disconnections  

---

## 🛠️ **Tech Stack**
- **Language:** C++  
- **Networking:** Winsock API (Windows Sockets)  
- **Concurrency:** `std::thread`  
- **Protocol:** TCP/IP  

---

## ▶️ **How It Works**
### **Server**
- Initializes Winsock  
- Creates a listening socket on **port 12345**  
- Accepts client connections and spawns **a new thread for each client**  
- Broadcasts messages to all connected clients  

### **Client**
- Connects to server using IP (`127.0.0.1` for local testing)  
- Sends messages with **username prefix**  
- Listens for incoming messages in a **separate thread**  

---

## ⚙️ **Installation & Run**
### 1️⃣ Clone the Repository
```bash
git clone https://github.com/nancy-singh10/nancy-singh10-Emergency-LAN-Chat-System-.git
cd nancy-singh10-Emergency-LAN-Chat-System-

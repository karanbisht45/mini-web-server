# 🖥️ Mini Web Server (C + Winsock)

> ⚡ A lightweight HTTP server built entirely in C using the Winsock API for Windows — capable of serving web pages, handling dynamic routes, and redirecting to real websites 🌍

---

## ✨ Features

| ✅ Feature | Description |
|-------------|--------------|
| 🌐 **Static File Hosting** | Serves `index.html`, `about.html`, and `style.css` |
| ⚙️ **Dynamic Routes** | Handles `/hello`, `/time`, and `/status` |
| 🔁 **External Redirects** | Opens Google, YouTube, GitHub, and Wikipedia directly |
| 🧾 **JSON API Support** | Returns JSON data for `/status` route |
| 🧠 **Smart Request Parsing** | Detects route type and responds accordingly |
| 🧰 **Lightweight & Fast** | Written in pure C using the Winsock API |
| 💬 **Logs Requests** | Displays client IP and request path in terminal |

---

## 📂 Project Structure

mini_web_server/
│
├── server.c # Main server logic (C code)
├── server.h # Header file with declarations
├── index.html # Homepage served by the server
├── about.html # About page
├── style.css # Website styling
└── mini_server.exe # Compiled executable (after build)

---


---

## ⚙️ Tech Stack

| Component | Technology Used |
|------------|------------------|
| 💻 **Language** | C |
| 🔌 **Networking** | Winsock2 API |
| 🧱 **Build Tool** | MinGW / GCC |
| 🌐 **Frontend** | HTML + CSS |
| 🧰 **Platform** | Windows |

---

## 🧩 Key Routes

| Route | Description | Type |
|--------|--------------|------|
| `/` | Home Page | Static |
| `/about.html` | About Page | Static |
| `/hello` | Returns Greeting | Dynamic |
| `/time` | Displays Server Time | Dynamic |
| `/status` | Returns Server Info (JSON) | API |
| `/google` | Redirects to Google | Redirect |
| `/youtube` | Redirects to YouTube | Redirect |
| `/github` | Redirects to GitHub | Redirect |
| `/wikipedia` | Redirects to Wikipedia | Redirect |

---

## ⚙️ Tech Stack

| Component | Technology Used |
|------------|------------------|
| 💻 **Language** | C |
| 🔌 **Networking** | Winsock2 API |
| 🧱 **Build Tool** | MinGW / GCC |
| 🌐 **Frontend** | HTML + CSS |
| 🧰 **Platform** | Windows |

---

## 🧩 Key Routes

| Route | Description | Type |
|--------|--------------|------|
| `/` | Home Page | Static |
| `/about.html` | About Page | Static |
| `/hello` | Returns Greeting | Dynamic |
| `/time` | Displays Server Time | Dynamic |
| `/status` | Returns Server Info (JSON) | API |
| `/google` | Redirects to Google | Redirect |
| `/youtube` | Redirects to YouTube | Redirect |
| `/github` | Redirects to GitHub | Redirect |
| `/wikipedia` | Redirects to Wikipedia | Redirect |

---

## 🛠️ How to Run

### 🧩 Step 1 — Install MinGW (C Compiler)
Download the setup: [MinGW Installer](https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe)

After installation, verify it:
```bash
gcc --version


# Gym & Padel Management System 🏋️🎾

Welcome to our university Data Structures project!

This project is a C++ console-based management system for gym and padel members, subscriptions, bookings, and workouts.

---

## ✅ How to Run the Project (for Windows & macOS)

Follow the steps below to get the project up and running on your machine using **Visual Studio Code (VS Code)**.

---

### 💻 1. Install Requirements

#### Windows:
- Install [MinGW](https://www.mingw-w64.org/downloads/)
- Add MinGW `bin` folder to your system `PATH`
    > Example: `C:\MinGW\bin`
- Install **VS Code**
- Install the **C++ Extension** in VS Code (by Microsoft)

#### macOS:
- Install **Xcode Command Line Tools**  
```bash
xcode-select --install
```

---

### 📦 2. Clone the Repository

```bash
git clone <your-repo-url>
cd gym-padel-management-system
```

---

### 🧠 3. Open the Folder in VS Code

- Open VS Code
- Go to `File → Open Folder...`
- Select the folder you just cloned

---

### ⚙️ 4. Build the Project

- Press `Ctrl + Shift + B` (Windows) or `Cmd + Shift + B` (Mac)
- This will compile:
  - `main.cpp`
  - `utils/json_utils.cpp`
  - `utils/utils.cpp`
- You should see `main` or `main.exe` generated

---

### ▶️ 5. Run the Project

- Click the ▶️ **Run** button in the top right of VS Code  
  OR  
- Go to the **Run & Debug** tab → Click **Run Project**

Output will appear in the **Debug Console**  
You can also enter inputs using `cin` from there.

---

## ⚠️ Troubleshooting

### 🛠️ VS Code says "Build Project" is not found?
- Make sure `.vscode/tasks.json` is present in the folder
- Open the Command Palette: `Ctrl+Shift+P` → `Tasks: Configure Default Build Task` → select `Build Project`

### 🛠️ Getting "g++ not found"?
- Make sure you installed MinGW (Windows) or Xcode tools (macOS)
- Make sure `g++` is in your system PATH

---

## ✅ Project Structure

```
gym-padel-management-system/
├── main.cpp
├── includes/           # All class headers
├── utils/              # JSON and time helpers
│   ├── json_utils.cpp
│   ├── utils.cpp
├── .vscode/            # VS Code config (build + run)
│   ├── tasks.json
│   └── launch.json
```

---

Made with ❤️ by Team Gym & Padel
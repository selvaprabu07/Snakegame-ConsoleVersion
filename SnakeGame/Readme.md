# 🐍 Snake Game in C – Console Version

A classic **Snake Game** implemented in pure **C**, designed to run in the terminal (console). This game lets you control a snake that grows longer every time it eats food, with the goal of surviving as long as possible without crashing into walls or itself.

---

## 🧩 Features

- Move using keyboard keys: `W`, `A`, `S`, `D`
- Eat fruit to grow and score points
- Game over on wall or self collision
- Player name input at start
- Final score saved to a file (`scores.txt`)
- Smooth animation with delay control

---

## 💻 Technologies Used

- **Language:** C
- **Libraries:**  
  - `stdio.h` – Input/Output  
  - `stdlib.h` – Random numbers, memory functions  
  - `string.h` – String operations  
  - `conio.h` – Keyboard input (`_kbhit`, `_getch`)  
  - `windows.h` – Delay function (`Sleep`)  
  - `time.h` – Seed random number generator

> ⚠️ Note: This version is **Windows-only** due to the use of Windows-specific console functions. A cross-platform version using `ncurses` or similar libraries can be added upon request!

---

## 📁 File Structure

```plaintext
/snake-game-c/
│
├── snake.c         # Main source code
├── scores.txt      # Stores player names and scores
└── README.md       # Project documentation
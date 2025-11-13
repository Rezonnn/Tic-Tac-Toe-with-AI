# 🎮 Tic-Tac-Toe with AI (C++ Console Game)

A clean, self-contained **C++ console mini-game** where you play Tic-Tac-Toe against a simple **AI powered by minimax**.

My Project showcases:

- C++17
- Basic **game logic**
- Simple **AI search (minimax)**
- Clean structuring with classes (`Board`, `Game`)

---

## 🧠 Features

- 3x3 Tic-Tac-Toe board
- You play as **X**, computer is **O**
- Input as `row col` (both between 0 and 2)
- Computer uses a minimax-based strategy:
  - Tries to win when it can
  - Blocks obvious wins
  - Plays optimally for such a small game

---

## ▶️ How to Build & Run

### Option 1 – Using `g++` directly

From the project folder:

```bash
g++ -std=c++17 -O2 -o tictactoe_ai main.cpp
./tictactoe_ai     # On Windows: tictactoe_ai.exe
```

---

### Option 2 – Using CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
./tictactoe_ai     # On Windows: tictactoe_ai.exe
```

---

## 🎮 How to Play

When the program starts, you'll see:

- A 3x3 board labeled with row and column indices.
- You are prompted:

```text
Your move (row col):
```

Enter moves like:

```text
0 2
1 1
2 0
```

The computer will respond with its own moves.  
The game ends with:

- **You win! 🎉**
- **Computer wins. 🤖**
- or **It's a draw.**

You can then choose to **play again**.

---

## 📁 Project Structure

```text
cpp_tictactoe_ai/
├─ main.cpp        # Game logic + AI
├─ CMakeLists.txt  # CMake build file
└─ README.md       # Project documentation (this file)
```

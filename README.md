# C++ Chess Engine

![Gameplay Demo](gameplay.gif)

A simple chess engine that features bot vs. player and a bot vs. bot mode. The bots use a standard Minimax algorithm and evaluate the board solely on the basis of material.

## Features

* **Standard Piece Mechanics:** Full validation for standard piece movements.
* **Game State Detection:** Identifies Check, Checkmate, and Stalemate conditions.
* **Draw Conditions:** Automatically detects and enforces "Insufficient Material" and 300+ move draws.
* **Object-Oriented Design:** Uses polymorphic piece classes and a 2D pointer array for clean, memory-efficient board management.

## Prerequisites

This project utilizes modern C++ features (such as structured bindings), so you will need a compiler that supports **C++17** or higher.

* **GCC:** `g++` 7.0 or later
* **Clang:** `clang++` 5.0 or later

You will also need **Raylib** installed and properly linked to compile the graphical components.

### Compilation Instructions

**For macOS:**
Navigate to the project directory in your terminal and run the following command to compile with all the necessary Raylib frameworks:

```bash
clang++ -std=c++17 src/*.cpp -o bin/main -I include -L lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -framework CoreAudio
```

**For Linux:**
Navigate to the project directory and run:

```bash
g++ -std=c++17 src/*.cpp -o bin/main -I include -L lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

**Running the Engine:**
Once the compilation is complete, you can launch the game by running the generated executable:

```bash
./bin/main
```

### Customizing the Bot
By default, the bots evaluate the board strictly based on material value. You can change the way the bots play and make them smarter (for example, by adding piece-square tables for positional bonuses, or factoring in king safety) by modifying the evaluateBoard function located in src/bots.cpp.

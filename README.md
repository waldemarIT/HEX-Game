# Hex Game Analyzer (C / Game Logic Engine)

This project implements a command-line logic engine for the board game **Hex**, capable of parsing board states, processing queries, validating rules, and simulating outcomes based on given positions.

## 🎮 Game Overview

Hex is a two-player connection game played on a hexagonal grid:
- Players: Red (`r`) and Blue (`b`)
- Turn order: Red always starts first
- Goal: Connect opposite board edges (top-to-bottom for Red, left-to-right for Blue)
- A move: placing a pawn on an empty hex cell

More info: [Wikipedia - Hex (game)](https://en.wikipedia.org/wiki/Hex_(board_game))

---

## 🧩 Project Features

- Parses custom board drawings with indentation and variable sizes (1×1 up to 11×11)
- Supports **graph-based analysis** to detect connectivity
- Validates **rules of the game** and **correctness of board state**
- Evaluates **end-game conditions**
- Answers strategic questions using tree-based simulation (e.g., Can Red win in 2 moves?)
- Implements **MiniMax evaluation** for optimal vs naive opponent decisions

---

## 🧪 Supported Query Types

Each input may be followed by one or more queries. For each, the program returns a single-line answer:

| Query                                 | Output Example      | Description |
|--------------------------------------|---------------------|-------------|
| `BOARD_SIZE`                         | `11`                | Returns size of the board (1–11) |
| `PAWNS_NUMBER`                       | `84`                | Total number of placed pawns |
| `IS_BOARD_CORRECT`                  | `YES` / `NO`        | Validates balance of turns between players |
| `IS_GAME_OVER`                      | `YES RED` / `YES BLUE` / `NO` | Detects if any player has already won |
| `IS_BOARD_POSSIBLE`                | `YES` / `NO`        | Ensures board is correct and no win was skipped |
| `CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT` | `YES` / `NO` | Simulates whether red can win in 1 move against a naive (worst-move) opponent |
| `CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT` | `YES` / `NO` | Minimax-based analysis with perfect opponent logic (depth 4) |

> ❗ For queries 3–7, if the board is invalid (`IS_BOARD_CORRECT = NO`), then the answer must always be `NO` per spec.

---

## 🧠 Algorithms Used

- Union-Find or DFS/BFS for path detection
- MiniMax (depth-limited) for move forecasting
- Rule-based game logic to enforce correct turn sequence and win conditions

---

## ⚙️ Build & Run

To compile:

```bash
g++ -std=c++17 -O2 hex_analyzer.cpp -o hex_analyzer

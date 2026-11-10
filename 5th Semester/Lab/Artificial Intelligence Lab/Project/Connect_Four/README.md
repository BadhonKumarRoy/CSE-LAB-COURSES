# Connect Four AI (Human vs AI)
**Artificial Intelligence Lab Project | 5th Semester**

An interactive Connect Four game developed in **Python** using **Pygame**, featuring an intelligent AI opponent powered by the **Minimax Algorithm** optimized with **Alpha-Beta Pruning**.

---

## 📌 1. Project Overview

| Attribute | Details |
| :--- | :--- |
| **Project Type** | AI Board Game |
| **Game Mode** | Human (Red) vs AI (Yellow) |
| **Language & Library** | Python 3 + Pygame |
| **Core Algorithm** | Minimax |
| **Optimization** | Alpha-Beta Pruning & Center-first Move Ordering |
| **Board Grid** | 6 Rows × 7 Columns |
| **Winning Condition** | First player to align 4 consecutive discs (horizontally, vertically, or diagonally) |

---

## 🚀 2. Features

- **🎮 Smooth Visual Animations:**
  - **Gravity Drop Animation:** Discs fall realistically down the column slots.
  - **Winning Highlight:** The 4 winning discs pulse with a glowing emerald border.
  - **Interactive Button Animations:** Buttons smoothly glow and expand on hover; the *Restart* button pulses when the game ends.
  - **Mouse Preview:** A floating red disc follows the cursor across columns showing exactly where it will land.
- **⚙️ Distinct Difficulty Levels:**
  - **Easy (Casual / Beginner):** AI plays casually with human-like blunders (~45% casual moves) and occasionally overlooks blocks (~50%), giving the human player frequent opportunities to win!
  - **Medium (Balanced / Fair):** AI uses 3-ply Minimax. Defends direct 1-move threats reliably, but does not calculate deep multi-turn diagonal traps.
  - **Hard (Master AI):** 5-ply Alpha-Beta Minimax. Ruthless, zero-blunder optimal play with aggressive center column dominance.
- **📊 Real-Time AI Metrics:**
  - Displays search depth, nodes explored, branch cutoffs, and execution time in milliseconds after every AI turn.
- **⚡ In-Game Algorithm Comparison Tool:**
  - Press the **Compare AI Algorithms** button (or press `C`) on any board state to benchmark **Alpha-Beta Pruning vs Pure Minimax**. Shows the exact number of nodes saved and percentage reduction in search space!

---

## 📂 3. Project Structure

```text
Connect_Four/
├── main.py       # Pygame GUI, animations, user input, and main game loop
├── board.py      # Grid representation, gravity drops, and win/draw detection
├── ai.py         # Minimax, Alpha-Beta Pruning, and heuristic evaluation functions
├── utils.py      # Constants, color palette, dimensions, and animated Button component
└── README.md     # Lab documentation and presentation notes
```

---

## 🧠 4. How the AI Algorithm Works

### 4.1 Minimax Algorithm
Minimax is a backtracking decision-making algorithm used in two-player zero-sum games. It assumes both players make optimal moves:
- **Maximizing Player (AI):** Chooses the move that maximizes the board evaluation score.
- **Minimizing Player (Human):** Chooses the move that minimizes the AI's score.

```text
               [AI: Maximize]
              /              \
       [Human: Min]       [Human: Min]
       /          \       /          \
     +100         -10   -120        +10
```

### 4.2 Alpha-Beta Pruning
Standard Minimax explores every possible branch up to a fixed depth $d$, resulting in $O(b^d)$ time complexity (where $b \approx 7$ is the branching factor).

**Alpha-Beta Pruning** maintains two values:
- $\alpha$ (Alpha): The best score guaranteed for the Maximizer so far (initially $-\infty$).
- $\beta$ (Beta): The best score guaranteed for the Minimizer so far (initially $+\infty$).

**Cutoff Rule:**
Whenever $\beta \le \alpha$, the opponent would never allow this branch to be reached. The algorithm immediately stops exploring that sub-tree (pruning), **without changing the final decision**.

### 4.3 Move Ordering Optimization
By exploring columns from the **center outwards** (`[3, 2, 4, 1, 5, 0, 6]`), strong tactical moves are evaluated first. This triggers early cutoffs and approaches optimal Alpha-Beta performance:
$$\text{Time Complexity: } O(b^{d/2})$$

---

## 📐 5. Heuristic Evaluation Function

When the search reaches depth 0, the board is evaluated by checking all possible **4-cell windows** (horizontal, vertical, and both diagonals):

| Board Situation | Heuristic Score | Rationale |
| :--- | :---: | :--- |
| **AI connects 4 discs** | `+100,000` | Terminal win state for AI |
| **Human connects 4 discs** | `-100,000` | Terminal win state for Human |
| **AI has 3 discs + 1 empty** | `+100` | Strong offensive threat |
| **Human has 3 discs + 1 empty** | `-120` | Critical defensive block (penalty prioritized over offense) |
| **AI has 2 discs + 2 empty** | `+10` | Promising setup |
| **Human has 2 discs + 2 empty** | `-10` | Opponent setup |
| **Center Column Disc (Col 3)** | `+6 (AI) / -4 (Human)` | Center dominance controls more winning diagonals and rows |

---

## 🔬 6. Experimental Benchmark (Minimax vs Alpha-Beta)

Empirical results measured on an active board position:

| Search Depth | Pure Minimax Nodes | Alpha-Beta Nodes | Nodes Pruned | Efficiency Gain |
| :---: | :---: | :---: | :---: | :---: |
| **Depth 1** | 7 | 7 | 0 | 0.0% |
| **Depth 2** | 49 | 25 | 24 | **49.0%** |
| **Depth 3** | 343 | 74 | 269 | **78.4%** |
| **Depth 4** | 2,150 | 98 | 2,052 | **95.4%** |

> **Conclusion:** Alpha-Beta Pruning evaluates **over 95% fewer nodes at depth 4** while choosing the **exact same move and score** as exhaustive Minimax.

---

## 💻 7. Installation & How to Run

### Step 1: Open Terminal in Project Directory
Open your terminal or command prompt inside the `Connect_Four` project folder:
```bash
cd Connect_Four
```

### Step 2: Activate Virtual Environment
```powershell
# On Windows (PowerShell)
.\.venv\Scripts\Activate.ps1

# On Windows (Command Prompt - CMD)
.\.venv\Scripts\activate.bat

# On macOS / Linux
source .venv/bin/activate
```

### Step 3: Install Dependencies
```bash
pip install pygame
```

### Step 4: Run the Game
```bash
python main.py
```

---

## ⌨️ 8. Keyboard Shortcuts & Controls

- **Left Mouse Click:** Drop disc into selected column
- **`R`**: Restart match
- **`1`**: Set AI Difficulty to **Easy** (Depth 2)
- **`2`**: Set AI Difficulty to **Medium** (Depth 4)
- **`3`**: Set AI Difficulty to **Hard** (Depth 5)
- **`C`**: Run & view the **Algorithm Comparison** popup
- **`ESC`**: Quit the game / close modal

---

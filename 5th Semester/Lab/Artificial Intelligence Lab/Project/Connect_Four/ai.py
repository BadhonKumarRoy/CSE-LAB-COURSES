import time
import random
from utils import ROWS, COLS, EMPTY, HUMAN, AI
from board import (
    get_next_open_row,
    drop_piece,
    check_winner,
    is_board_full,
    get_valid_moves,
)


# -------------------------------------------------------------------------
# Heuristic Scoring (Evaluation Function)
# -------------------------------------------------------------------------
def evaluate_window(window):
    """
    Scores a 4-cell window based on the project specification:
    - AI connects 4:       +100,000
    - AI has 3 + 1 empty:  +100
    - AI has 2 + 2 empty:  +10
    - Human has 3 + 1 empty: -120 (encourage AI to block human)
    - Human has 2 + 2 empty: -10
    """
    score = 0
    ai_count = window.count(AI)
    human_count = window.count(HUMAN)
    empty_count = window.count(EMPTY)

    # AI evaluation
    if ai_count == 4:
        score += 100000
    elif ai_count == 3 and empty_count == 1:
        score += 100
    elif ai_count == 2 and empty_count == 2:
        score += 10

    # Human threat evaluation (negative scores force AI to block)
    if human_count == 3 and empty_count == 1:
        score -= 120
    elif human_count == 2 and empty_count == 2:
        score -= 10

    return score


def score_position(board):
    """
    Evaluates the whole board by summing up heuristic scores of all
    possible 4-cell windows (horizontal, vertical, diagonals) plus center column.
    """
    score = 0

    # 1. Center Column Preference:
    # Controlling the center column gives more strategic opportunities.
    center_column = [board[r][COLS // 2] for r in range(ROWS)]
    score += center_column.count(AI) * 6
    score -= center_column.count(HUMAN) * 4

    # 2. Horizontal Windows
    for r in range(ROWS):
        for c in range(COLS - 3):
            window = [board[r][c + i] for i in range(4)]
            score += evaluate_window(window)

    # 3. Vertical Windows
    for c in range(COLS):
        for r in range(ROWS - 3):
            window = [board[r + i][c] for i in range(4)]
            score += evaluate_window(window)

    # 4. Diagonal Down-Right Windows (\)
    for r in range(ROWS - 3):
        for c in range(COLS - 3):
            window = [board[r + i][c + i] for i in range(4)]
            score += evaluate_window(window)

    # 5. Diagonal Up-Right Windows (/)
    for r in range(3, ROWS):
        for c in range(COLS - 3):
            window = [board[r - i][c + i] for i in range(4)]
            score += evaluate_window(window)

    return score


# -------------------------------------------------------------------------
# Minimax with Alpha-Beta Pruning
# -------------------------------------------------------------------------
def minimax(board, depth, alpha, beta, maximizing_player, stats):
    """
    Minimax search with Alpha-Beta Pruning.
    - maximizing_player: AI (seeks highest score)
    - minimizing_player: Human (seeks lowest score)
    - alpha: best score the maximizer can guarantee
    - beta: best score the minimizer can guarantee
    """
    stats["nodes"] += 1

    # Base Cases (Terminal States)
    if check_winner(board, AI):
        return None, 100000 + depth   # Win for AI (prefer faster wins)
    if check_winner(board, HUMAN):
        return None, -100000 - depth  # Win for Human (delay loss)
    if is_board_full(board):
        return None, 0                # Draw

    if depth == 0:
        return None, score_position(board)

    valid_moves = get_valid_moves(board, center_first=True)
    if not valid_moves:
        return None, 0

    if maximizing_player:
        max_eval = -float("inf")
        best_col = random.choice(valid_moves)

        for col in valid_moves:
            row = get_next_open_row(board, col)
            drop_piece(board, row, col, AI)  # Place AI piece

            _, current_score = minimax(board, depth - 1, alpha, beta, False, stats)

            # Backtrack (undo move)
            board[row][col] = EMPTY

            if current_score > max_eval:
                max_eval = current_score
                best_col = col

            # Update alpha
            alpha = max(alpha, current_score)

            # Alpha-Beta Pruning: skip further branches
            if beta <= alpha:
                stats["prunes"] += 1
                break

        return best_col, max_eval

    else:
        min_eval = float("inf")
        best_col = random.choice(valid_moves)

        for col in valid_moves:
            row = get_next_open_row(board, col)
            drop_piece(board, row, col, HUMAN)  # Place Human piece

            _, current_score = minimax(board, depth - 1, alpha, beta, True, stats)

            # Backtrack (undo move)
            board[row][col] = EMPTY

            if current_score < min_eval:
                min_eval = current_score
                best_col = col

            # Update beta
            beta = min(beta, current_score)

            # Alpha-Beta Pruning: skip further branches
            if beta <= alpha:
                stats["prunes"] += 1
                break

        return best_col, min_eval


# -------------------------------------------------------------------------
# Pure Minimax (Without Pruning) - Used for Demonstration & Comparison
# -------------------------------------------------------------------------
def minimax_pure(board, depth, maximizing_player, stats):
    """
    Standard Minimax without Alpha-Beta bounds.
    Explores all nodes in the tree to show why Alpha-Beta pruning is needed.
    """
    stats["nodes"] += 1

    if check_winner(board, AI):
        return None, 100000 + depth
    if check_winner(board, HUMAN):
        return None, -100000 - depth
    if is_board_full(board):
        return None, 0

    if depth == 0:
        return None, score_position(board)

    valid_moves = get_valid_moves(board, center_first=True)
    if not valid_moves:
        return None, 0

    if maximizing_player:
        max_eval = -float("inf")
        best_col = random.choice(valid_moves)

        for col in valid_moves:
            row = get_next_open_row(board, col)
            drop_piece(board, row, col, AI)

            _, current_score = minimax_pure(board, depth - 1, False, stats)

            board[row][col] = EMPTY  # Undo

            if current_score > max_eval:
                max_eval = current_score
                best_col = col

        return best_col, max_eval

    else:
        min_eval = float("inf")
        best_col = random.choice(valid_moves)

        for col in valid_moves:
            row = get_next_open_row(board, col)
            drop_piece(board, row, col, HUMAN)

            _, current_score = minimax_pure(board, depth - 1, True, stats)

            board[row][col] = EMPTY  # Undo

            if current_score < min_eval:
                min_eval = current_score
                best_col = col

        return best_col, min_eval


# -------------------------------------------------------------------------
# AI Public Functions
# -------------------------------------------------------------------------
def get_ai_move(board, depth=4, difficulty="Medium"):
    """
    Finds the AI move tailored to the selected difficulty level:
    - Easy: Casual / beginner play. Makes mistakes, occasionally overlooks blocks,
            giving the player plenty of opportunities to win!
    - Medium: Balanced play (depth 3). Plays solid defense against direct threats,
              but doesn't set deep multi-turn traps.
    - Hard: Master AI (depth 5). Full Minimax + Alpha-Beta, ruthless and optimal.
    """
    stats = {"nodes": 0, "prunes": 0}
    start_time = time.perf_counter()

    valid_moves = get_valid_moves(board, center_first=False)
    if not valid_moves:
        return None, stats

    # ─────────────────────────────────────────────────────────────
    # 1. EASY MODE (Casual / Beginner)
    # ─────────────────────────────────────────────────────────────
    if difficulty == "Easy":
        # 1a. AI takes immediate win if available (75% chance)
        for col in valid_moves:
            row = get_next_open_row(board, col)
            drop_piece(board, row, col, AI)
            if check_winner(board, AI):
                board[row][col] = EMPTY
                if random.random() < 0.75:
                    elapsed = (time.perf_counter() - start_time) * 1000
                    stats.update({"time_ms": elapsed, "score": 100000, "depth": 1})
                    return col, stats
            board[row][col] = EMPTY

        # 1b. 45% chance to make a casual / random move (gives player easy openings!)
        if random.random() < 0.45:
            col = random.choice(valid_moves)
            elapsed = (time.perf_counter() - start_time) * 1000
            stats.update({"time_ms": elapsed, "score": 0, "depth": 1, "nodes": 1})
            return col, stats

        # 1c. 50% chance to overlook blocking a human win (allows player to score 4-in-a-row!)
        human_threat_col = None
        for col in valid_moves:
            row = get_next_open_row(board, col)
            drop_piece(board, row, col, HUMAN)
            if check_winner(board, HUMAN):
                human_threat_col = col
            board[row][col] = EMPTY

        if human_threat_col is not None and random.random() < 0.50:
            # Overlook the block and play somewhere else so human can win!
            other_moves = [c for c in valid_moves if c != human_threat_col]
            if other_moves:
                col = random.choice(other_moves)
                elapsed = (time.perf_counter() - start_time) * 1000
                stats.update({"time_ms": elapsed, "score": 0, "depth": 1, "nodes": 1})
                return col, stats

        # Otherwise run shallow depth (depth 2)
        search_depth = 2

    # ─────────────────────────────────────────────────────────────
    # 2. MEDIUM MODE (Balanced / Intermediate)
    # ─────────────────────────────────────────────────────────────
    elif difficulty == "Medium":
        # Always take immediate win
        for col in valid_moves:
            row = get_next_open_row(board, col)
            drop_piece(board, row, col, AI)
            if check_winner(board, AI):
                board[row][col] = EMPTY
                elapsed = (time.perf_counter() - start_time) * 1000
                stats.update({"time_ms": elapsed, "score": 100000, "depth": 1})
                return col, stats
            board[row][col] = EMPTY

        # Search depth 3 (tactical, but doesn't calculate deep 5-ply forks)
        search_depth = 3

    # ─────────────────────────────────────────────────────────────
    # 3. HARD MODE (Master AI / Full Alpha-Beta Minimax)
    # ─────────────────────────────────────────────────────────────
    else:
        search_depth = max(5, depth)

    # Execute Minimax with Alpha-Beta Pruning
    best_col, score = minimax(
        board,
        depth=search_depth,
        alpha=-float("inf"),
        beta=float("inf"),
        maximizing_player=True,
        stats=stats
    )

    elapsed_ms = (time.perf_counter() - start_time) * 1000
    stats["time_ms"] = elapsed_ms
    stats["score"] = score
    stats["depth"] = search_depth

    return best_col, stats


def compare_algorithms(board, depth=3):
    """
    Runs both Alpha-Beta and Pure Minimax on the same board state
    to demonstrate search efficiency and node reduction.
    """
    # 1. Run Alpha-Beta
    ab_stats = {"nodes": 0, "prunes": 0}
    t0 = time.perf_counter()
    ab_col, ab_score = minimax(board, depth, -float("inf"), float("inf"), True, ab_stats)
    ab_time = (time.perf_counter() - t0) * 1000

    # 2. Run Pure Minimax
    pure_stats = {"nodes": 0}
    t1 = time.perf_counter()
    pure_col, pure_score = minimax_pure(board, depth, True, pure_stats)
    pure_time = (time.perf_counter() - t1) * 1000

    saved_nodes = max(0, pure_stats["nodes"] - ab_stats["nodes"])
    reduction_pct = (saved_nodes / pure_stats["nodes"] * 100) if pure_stats["nodes"] > 0 else 0

    return {
        "depth": depth,
        "ab_col": ab_col,
        "ab_nodes": ab_stats["nodes"],
        "ab_prunes": ab_stats["prunes"],
        "ab_time_ms": ab_time,
        "ab_score": ab_score,
        "pure_col": pure_col,
        "pure_nodes": pure_stats["nodes"],
        "pure_time_ms": pure_time,
        "pure_score": pure_score,
        "saved_nodes": saved_nodes,
        "reduction_pct": reduction_pct,
    }

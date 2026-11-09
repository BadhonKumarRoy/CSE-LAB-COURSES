"""
board.py - Connect Four Board Logic.
Kept simple, clear, and easy to explain during lab viva/defense.
"""

from utils import ROWS, COLS, EMPTY, HUMAN, AI


def create_board():
    """
    Creates a 6x7 grid initialized with zeros (EMPTY).
    Row 0 is the TOP row, Row 5 is the BOTTOM row.
    """
    return [[EMPTY for _ in range(COLS)] for _ in range(ROWS)]


def is_valid_location(board, col):
    """
    Checks if a column has room for at least one more disc.
    Returns True if the top row (row 0) is empty.
    """
    if 0 <= col < COLS:
        return board[0][col] == EMPTY
    return False


def get_next_open_row(board, col):
    """
    Simulates gravity: finds the lowest open row in the selected column.
    Starts from row 5 (bottom) and moves upwards to row 0.
    Returns the row index, or None if the column is full.
    """
    for r in range(ROWS - 1, -1, -1):
        if board[r][col] == EMPTY:
            return r
    return None


def drop_piece(board, row, col, piece):
    """Places a disc into the board grid."""
    board[row][col] = piece


def make_move(board, col, piece):
    """
    Drops a piece into the given column at the lowest available row.
    Returns the row where the piece landed, or None if column was full.
    """
    row = get_next_open_row(board, col)
    if row is not None:
        drop_piece(board, row, col, piece)
        return row
    return None


def get_valid_moves(board, center_first=True):
    """
    Returns a list of all column numbers that can still accept a disc.
    Ordering from center outwards ([3, 2, 4, 1, 5, 0, 6]) helps Alpha-Beta
    prune suboptimal branches earlier, improving performance!
    """
    if center_first:
        order = [3, 2, 4, 1, 5, 0, 6]
        return [c for c in order if is_valid_location(board, c)]
    else:
        return [c for c in range(COLS) if is_valid_location(board, c)]


def is_board_full(board):
    """Returns True if every column is full (draw condition)."""
    return all(board[0][c] != EMPTY for c in range(COLS))


def check_winner(board, player):
    """
    Checks if the specified player has 4 discs in a row:
    - Horizontally
    - Vertically
    - Diagonally (down-right and up-right)
    """
    # 1. Horizontal Check (4 consecutive discs in any row)
    for r in range(ROWS):
        for c in range(COLS - 3):
            if (board[r][c] == player and
                board[r][c + 1] == player and
                board[r][c + 2] == player and
                board[r][c + 3] == player):
                return True

    # 2. Vertical Check (4 consecutive discs in any column)
    for r in range(ROWS - 3):
        for c in range(COLS):
            if (board[r][c] == player and
                board[r + 1][c] == player and
                board[r + 2][c] == player and
                board[r + 3][c] == player):
                return True

    # 3. Diagonal Check (down-right: \)
    for r in range(ROWS - 3):
        for c in range(COLS - 3):
            if (board[r][c] == player and
                board[r + 1][c + 1] == player and
                board[r + 2][c + 2] == player and
                board[r + 3][c + 3] == player):
                return True

    # 4. Diagonal Check (up-right: /)
    for r in range(3, ROWS):
        for c in range(COLS - 3):
            if (board[r][c] == player and
                board[r - 1][c + 1] == player and
                board[r - 2][c + 2] == player and
                board[r - 3][c + 3] == player):
                return True

    return False


def get_winning_cells(board, player):
    """
    Finds the exact 4 (row, col) coordinates that form the winning connection.
    Used for the winning highlight animation.
    """
    # Horizontal
    for r in range(ROWS):
        for c in range(COLS - 3):
            if all(board[r][c + i] == player for i in range(4)):
                return [(r, c + i) for i in range(4)]

    # Vertical
    for r in range(ROWS - 3):
        for c in range(COLS):
            if all(board[r + i][c] == player for i in range(4)):
                return [(r + i, c) for i in range(4)]

    # Diagonal down-right (\)
    for r in range(ROWS - 3):
        for c in range(COLS - 3):
            if all(board[r + i][c + i] == player for i in range(4)):
                return [(r + i, c + i) for i in range(4)]

    # Diagonal up-right (/)
    for r in range(3, ROWS):
        for c in range(COLS - 3):
            if all(board[r - i][c + i] == player for i in range(4)):
                return [(r - i, c + i) for i in range(4)]

    return []

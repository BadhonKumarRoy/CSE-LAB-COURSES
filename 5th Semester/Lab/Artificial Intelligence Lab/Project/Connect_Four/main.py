import sys
import math
import pygame

from utils import (
    ROWS, COLS, CELL, RADIUS,
    BOARD_W, PANEL_W, WIN_W,
    HEADER_H, BOARD_H, WIN_H,
    EMPTY, HUMAN, AI,
    DIFFICULTIES,
    C_BG, C_PANEL, C_CARD, C_BORDER, C_BORDER_HI,
    C_RACK, C_RACK_EDGE,
    C_RED, C_RED_HI, C_RED_RIM,
    C_YEL, C_YEL_HI, C_YEL_RIM,
    C_WIN, C_WHITE, C_MUTED, C_ACCENT,
    C_BTN_GREEN, C_BTN_GREEN_H, C_BTN_GREEN_BORDER,
    C_BTN_PURPLE, C_BTN_PURPLE_H, C_BTN_PURPLE_BORDER,
    C_BTN_RED, C_BTN_RED_H, C_BTN_RED_BORDER,
    C_BTN_DIFF, C_BTN_DIFF_H, C_BTN_ACTIVE,
    lerp_color,
    Button,
)
from board import (
    create_board, is_valid_location,
    get_next_open_row, drop_piece,
    check_winner, get_winning_cells, is_board_full,
)
from ai import get_ai_move, compare_algorithms


class ConnectFourApp:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((WIN_W, WIN_H))
        pygame.display.set_caption("Connect Four AI - Minimax & Alpha-Beta Pruning")
        self.clock = pygame.time.Clock()

        # Clean typography stack
        self.f_title = pygame.font.SysFont("Segoe UI, Arial, sans-serif", 22, bold=True)
        self.f_heading = pygame.font.SysFont("Segoe UI, Arial, sans-serif", 15, bold=True)
        self.f_body = pygame.font.SysFont("Segoe UI, Arial, sans-serif", 13)
        self.f_body_bold = pygame.font.SysFont("Segoe UI, Arial, sans-serif", 13, bold=True)
        self.f_small = pygame.font.SysFont("Segoe UI, Arial, sans-serif", 11)
        self.f_code = pygame.font.SysFont("Consolas, Courier New, monospace", 13)

        # Game State
        self.board = create_board()
        self.turn = HUMAN
        self.game_over = False
        self.winner = None
        self.winning_cells = []
        self.status_message = "Your Turn"
        self.is_ai_thinking = False

        # Difficulty Setup
        self.difficulty_name = "Medium"
        self.depth = DIFFICULTIES[self.difficulty_name]

        # Algorithm comparison popup state
        self.show_comparison_modal = False
        self.comparison_data = None
        self.last_board_before_ai = None

        # Animation ticker
        self.anim_tick = 0.0

        # Pre-build rack surface with transparent holes for falling disc
        self._rack_surf = self._create_rack_surface()

        # Initialize UI buttons with exact, non-overlapping coordinates
        self._init_ui_buttons()

    def _create_rack_surface(self):
        """
        Creates a rack surface with transparent holes.
        """
        surf = pygame.Surface((BOARD_W, BOARD_H), pygame.SRCALPHA)
        surf.fill((*C_RACK, 255))

        for r in range(ROWS):
            for c in range(COLS):
                cx = c * CELL + CELL // 2
                cy = r * CELL + CELL // 2
                # Inset rack edge ring
                pygame.draw.circle(surf, (*C_RACK_EDGE, 255), (cx, cy), RADIUS + 4)
                # Punch transparent hole
                pygame.draw.circle(surf, (0, 0, 0, 0), (cx, cy), RADIUS + 1)

        return surf

    def _init_ui_buttons(self):
        """
        Calculates exact layout positions for all buttons to guarantee ZERO overlap.
        """
        bx = BOARD_W + 16        # Left edge inside side panel (646 px)
        bw = PANEL_W - 32        # Width of cards and buttons (268 px)

        # 1. Difficulty selector buttons (Row at y = 230, height = 40)
        dw = (bw - 16) // 3      # ~84 px each
        d_gap = 8
        dy = 230
        self.diff_buttons = {
            "Easy": Button(
                (bx, dy, dw, 40), "Easy (2)", size=13, radius=8,
                active=(self.difficulty_name == "Easy")
            ),
            "Medium": Button(
                (bx + dw + d_gap, dy, dw, 40), "Med (3)", size=13, radius=8,
                active=(self.difficulty_name == "Medium")
            ),
            "Hard": Button(
                (bx + 2 * (dw + d_gap), dy, dw, 40), "Hard (5)", size=13, radius=8,
                active=(self.difficulty_name == "Hard")
            ),
        }

        # 2. Action buttons (Comfortably spaced at y = 328, 390, 452; height = 48)
        btn_h = 48
        btn_gap = 14

        self.btn_restart = Button(
            (bx, 328, bw, btn_h), "Restart Game  [R]",
            bg=C_BTN_GREEN, hover=C_BTN_GREEN_H, border_color=C_BTN_GREEN_BORDER,
            size=14, radius=8
        )

        self.btn_compare = Button(
            (bx, 328 + (btn_h + btn_gap), bw, btn_h), "Compare Search  [C]",
            bg=C_BTN_PURPLE, hover=C_BTN_PURPLE_H, border_color=C_BTN_PURPLE_BORDER,
            size=14, radius=8
        )

        self.btn_quit = Button(
            (bx, 328 + 2 * (btn_h + btn_gap), bw, btn_h), "Quit Game  [ESC]",
            bg=C_BTN_RED, hover=C_BTN_RED_H, border_color=C_BTN_RED_BORDER,
            size=14, radius=8
        )

        # 3. Modal close button
        self.btn_modal_close = Button(
            (0, 0, 130, 36), "Close  [ESC]",
            bg=C_BTN_DIFF, hover=C_BTN_DIFF_H, size=13, radius=8
        )

    def set_difficulty(self, name):
        """Sets the AI search depth and updates active button."""
        if name in DIFFICULTIES:
            self.difficulty_name = name
            self.depth = DIFFICULTIES[name]
            for key, btn in self.diff_buttons.items():
                btn.active = (key == name)

    def reset_game(self):
        """Resets the game state for a new round."""
        self.board = create_board()
        self.turn = HUMAN
        self.game_over = False
        self.winner = None
        self.winning_cells = []
        self.status_message = "Your Turn"
        self.is_ai_thinking = False
        self.show_comparison_modal = False
        self.btn_restart.pulse = False
        self.last_board_before_ai = None

    # ─────────────────────────────────────────────────────────
    # Vector Disc Drawing (5-layer Glossy Sphere)
    # ─────────────────────────────────────────────────────────
    def draw_disc(self, surf, cx, cy, main, hi, rim, r=RADIUS):
        """Draws a glossy 3D sphere disc with specular highlight."""
        cx, cy = int(cx), int(cy)
        pygame.draw.circle(surf, rim, (cx, cy), r)
        pygame.draw.circle(surf, main, (cx, cy), r - 2)

        # Mid-tone curvature
        mid = lerp_color(main, hi, 0.32)
        pygame.draw.circle(surf, mid, (cx + 2, cy + 2), r - 7)

        # Upper-left shine
        sx, sy, sr = cx - r // 3, cy - r // 3, r // 3 + 2
        pygame.draw.circle(surf, hi, (sx, sy), sr)
        pygame.draw.circle(surf, lerp_color(hi, main, 0.5), (sx, sy), sr, width=max(1, sr // 2))

        # Specular pinpoint sparkle
        pygame.draw.circle(surf, (255, 255, 255), (cx - r // 2 + 2, cy - r // 2 + 2), 3)

    def get_disc_colors(self, player):
        return (C_RED, C_RED_HI, C_RED_RIM) if player == HUMAN else (C_YEL, C_YEL_HI, C_YEL_RIM)

    def draw_placed_discs(self):
        """Draws all discs currently on the board."""
        for r in range(ROWS):
            for c in range(COLS):
                piece = self.board[r][c]
                if piece != EMPTY:
                    cx = c * CELL + CELL // 2
                    cy = HEADER_H + r * CELL + CELL // 2
                    self.draw_disc(self.screen, cx, cy, *self.get_disc_colors(piece))

    def draw_winning_rings(self):
        """Draws animated glowing emerald pulse rings around the winning 4 discs."""
        if not (self.game_over and self.winning_cells):
            return

        pulse = math.sin(self.anim_tick * 4) * 4
        glow_r = int(RADIUS + 7 + pulse)
        alpha = int(185 + math.sin(self.anim_tick * 4) * 55)

        ring_surf = pygame.Surface((BOARD_W, WIN_H), pygame.SRCALPHA)
        for wr, wc in self.winning_cells:
            cx = wc * CELL + CELL // 2
            cy = HEADER_H + wr * CELL + CELL // 2
            pygame.draw.circle(ring_surf, (*C_WIN, alpha), (cx, cy), glow_r, width=4)
            pygame.draw.circle(self.screen, (255, 255, 255), (cx, cy), 5)

        self.screen.blit(ring_surf, (0, 0))

    def draw_preview_disc(self):
        """Draws the floating preview disc in the header that tracks the mouse column."""
        if self.game_over or self.turn != HUMAN or self.is_ai_thinking:
            return

        mx, _ = pygame.mouse.get_pos()
        if not (0 <= mx < BOARD_W):
            return

        col = max(0, min(COLS - 1, mx // CELL))
        cx = col * CELL + CELL // 2

        # Vertical guide column strip
        col_strip = pygame.Surface((CELL, WIN_H), pygame.SRCALPHA)
        col_strip.fill((96, 165, 250, 16))
        self.screen.blit(col_strip, (col * CELL, 0))

        if not is_valid_location(self.board, col):
            txt = self.f_heading.render("FULL", True, (248, 113, 113))
            self.screen.blit(txt, txt.get_rect(center=(cx, HEADER_H // 2)))
            return

        # Floating bouncing disc
        bounce = math.sin(self.anim_tick * 3.5) * 5
        cy = int(HEADER_H // 2 + bounce)

        temp_surf = pygame.Surface((RADIUS * 2 + 10, RADIUS * 2 + 10), pygame.SRCALPHA)
        dc = RADIUS + 5
        self.draw_disc(temp_surf, dc, dc, C_RED, C_RED_HI, C_RED_RIM)
        temp_surf.set_alpha(220)
        self.screen.blit(temp_surf, (cx - dc, cy - dc))

        # Thin guide drop line
        guide_line = pygame.Surface((2, BOARD_H), pygame.SRCALPHA)
        guide_line.fill((*C_RED, 45))
        self.screen.blit(guide_line, (cx - 1, HEADER_H))

    # ─────────────────────────────────────────────────────────
    # Redesigned Side Panel (Clean, Pixel-Perfect Layout)
    # ─────────────────────────────────────────────────────────
    def draw_side_panel(self):
        bx = BOARD_W + 16        # 646 px
        bw = PANEL_W - 32        # 268 px

        # 1. Panel Background & Separator
        panel_rect = pygame.Rect(BOARD_W, 0, PANEL_W, WIN_H)
        pygame.draw.rect(self.screen, C_PANEL, panel_rect)
        pygame.draw.line(self.screen, C_BORDER, (BOARD_W, 0), (BOARD_W, WIN_H), 2)

        # 2. Header Section (y = 16 to 56)
        title_txt1 = self.f_title.render("CONNECT FOUR", True, C_WHITE)
        title_txt2 = self.f_title.render(" AI", True, C_ACCENT)
        self.screen.blit(title_txt1, (bx, 16))
        self.screen.blit(title_txt2, (bx + title_txt1.get_width(), 16))

        sub_txt = self.f_small.render("Minimax Search + Alpha-Beta Pruning", True, C_MUTED)
        self.screen.blit(sub_txt, (bx, 42))
        pygame.draw.line(self.screen, C_BORDER, (bx, 62), (bx + bw, 62), 1)

        # 3. Status Banner Card (y = 74 to 126, height = 52)
        status_rect = pygame.Rect(bx, 74, bw, 52)
        pygame.draw.rect(self.screen, C_CARD, status_rect, border_radius=8)
        pygame.draw.rect(self.screen, C_BORDER, status_rect, width=1, border_radius=8)

        # Determine accent color based on turn or winner
        if self.game_over:
            if self.winner == HUMAN:
                accent_col = C_WIN
            elif self.winner == AI:
                accent_col = C_YEL
            else:
                accent_col = C_ACCENT
        else:
            accent_col = C_RED if self.turn == HUMAN else C_YEL

        # Left rounded vertical accent stripe
        pygame.draw.rect(self.screen, accent_col, pygame.Rect(bx + 1, 75, 4, 50), border_radius=4)

        # Vector Status Disc Icon (replaces emojis that fail to render on Windows)
        icon_cx = bx + 24
        icon_cy = 100
        pulse_r = int(7 + math.sin(self.anim_tick * 4) * 1.5)
        pygame.draw.circle(self.screen, accent_col, (icon_cx, icon_cy), pulse_r)
        pygame.draw.circle(self.screen, C_WHITE, (icon_cx, icon_cy), 3)

        # Status text (with animated thinking dots if AI)
        if self.is_ai_thinking:
            dot_count = int(self.anim_tick * 2) % 4
            text_str = f"AI is Thinking{'.' * dot_count}"
        else:
            text_str = self.status_message

        status_surf = self.f_heading.render(text_str, True, C_WHITE)
        self.screen.blit(status_surf, (bx + 42, 100 - status_surf.get_height() // 2))

        # 4. Player Identity Legend Card (y = 138 to 176, height = 38)
        legend_rect = pygame.Rect(bx, 138, bw, 38)
        pygame.draw.rect(self.screen, C_CARD, legend_rect, border_radius=8)
        pygame.draw.rect(self.screen, C_BORDER, legend_rect, width=1, border_radius=8)

        # Human indicator (Red)
        pygame.draw.circle(self.screen, C_RED, (bx + 18, 157), 8)
        pygame.draw.circle(self.screen, C_RED_HI, (bx + 16, 154), 3)
        h_label = self.f_body.render("You: Red", True, C_WHITE)
        self.screen.blit(h_label, (bx + 32, 157 - h_label.get_height() // 2))

        # AI indicator (Yellow)
        mid_x = bx + bw // 2 + 10
        pygame.draw.circle(self.screen, C_YEL, (mid_x, 157), 8)
        pygame.draw.circle(self.screen, C_YEL_HI, (mid_x - 2, 154), 3)
        ai_label = self.f_body.render("AI: Yellow", True, C_WHITE)
        self.screen.blit(ai_label, (mid_x + 14, 157 - ai_label.get_height() // 2))

        # 5. Difficulty Section Label (y = 206)
        diff_label = self.f_small.render("DIFFICULTY LEVEL", True, C_ACCENT)
        self.screen.blit(diff_label, (bx, 206))

        depth_hint = self.f_small.render(f"depth = {self.depth}", True, C_MUTED)
        self.screen.blit(depth_hint, (bx + bw - depth_hint.get_width(), 206))

        # Draw 3 Difficulty Buttons (y = 230 to 270)
        for btn in self.diff_buttons.values():
            btn.draw(self.screen, self.anim_tick)

        # Divider line
        pygame.draw.line(self.screen, C_BORDER, (bx, 292), (bx + bw, 292), 1)

        # 6. Action Controls Label & Buttons (y = 306 to 500)
        action_label = self.f_small.render("GAME CONTROLS", True, C_ACCENT)
        self.screen.blit(action_label, (bx, 306))

        self.btn_restart.pulse = self.game_over
        self.btn_restart.draw(self.screen, self.anim_tick)
        self.btn_compare.draw(self.screen, self.anim_tick)
        self.btn_quit.draw(self.screen, self.anim_tick)

        # 7. Footer (y = 612)
        footer_txt = self.f_small.render("Artificial Intelligence Lab  |  5th Semester", True, (100, 116, 139))
        self.screen.blit(footer_txt, footer_txt.get_rect(center=(BOARD_W + PANEL_W // 2, 616)))

    # ─────────────────────────────────────────────────────────
    # Algorithm Comparison Modal
    # ─────────────────────────────────────────────────────────
    def draw_comparison_modal(self):
        if not self.show_comparison_modal or not self.comparison_data:
            return

        d = self.comparison_data

        # Darkened transparent backdrop
        backdrop = pygame.Surface((WIN_W, WIN_H), pygame.SRCALPHA)
        backdrop.fill((0, 0, 0, 185))
        self.screen.blit(backdrop, (0, 0))

        # Modal Window Card
        mw, mh = 570, 410
        mx = (WIN_W - mw) // 2
        my = (WIN_H - mh) // 2
        modal_rect = pygame.Rect(mx, my, mw, mh)

        pygame.draw.rect(self.screen, C_CARD, modal_rect, border_radius=12)
        pygame.draw.rect(self.screen, (139, 92, 246), modal_rect, width=2, border_radius=12)

        title = self.f_title.render("Algorithm Comparison: Minimax vs Alpha-Beta", True, C_WHITE)
        self.screen.blit(title, (mx + 22, my + 18))

        if d.get("is_last_move"):
            sub_text = f"Benchmarked on AI's Last Move at Search Depth {d['depth']}"
            col_label = "AI Selected Column"
        else:
            sub_text = f"Evaluated on current board at Search Depth {d['depth']}"
            col_label = "Best Next Column"

        sub = self.f_small.render(sub_text, True, C_MUTED)
        self.screen.blit(sub, (mx + 22, my + 44))
        pygame.draw.line(self.screen, C_BORDER, (mx + 18, my + 64), (mx + mw - 18, my + 64), 1)

        # Table Column Headers
        col_x = [mx + 22, mx + 210, mx + 380]
        self.screen.blit(self.f_heading.render("Metric", True, C_ACCENT), (col_x[0], my + 72))
        self.screen.blit(self.f_heading.render("Pure Minimax", True, (248, 113, 113)), (col_x[1], my + 72))
        self.screen.blit(self.f_heading.render("Alpha-Beta", True, (74, 222, 128)), (col_x[2], my + 72))

        pygame.draw.line(self.screen, C_BORDER, (mx + 18, my + 94), (mx + mw - 18, my + 94), 1)

        # Table Rows
        rows = [
            ("Nodes Explored", f"{d['pure_nodes']:,}", f"{d['ab_nodes']:,}"),
            ("Pruned Branches", "0 (None)", f"{d['ab_prunes']:,}"),
            ("Time Elapsed", f"{d['pure_time_ms']:.2f} ms", f"{d['ab_time_ms']:.2f} ms"),
            (col_label, f"Column {d['pure_col'] + 1}", f"Column {d['ab_col'] + 1} (Identical)"),
            ("Board Score", str(d["pure_score"]), str(d["ab_score"])),
            ("Search Reduction", "Baseline", f"{d['reduction_pct']:.1f}% fewer nodes"),
        ]

        row_y = my + 104
        for lbl, v1, v2 in rows:
            self.screen.blit(self.f_body.render(lbl, True, C_WHITE), (col_x[0], row_y))
            self.screen.blit(self.f_code.render(v1, True, (252, 165, 165)), (col_x[1], row_y))

            v2_color = (74, 222, 128) if "fewer" in v2 or lbl == "Nodes Explored" else C_WHITE
            self.screen.blit(self.f_code.render(v2, True, v2_color), (col_x[2], row_y))

            pygame.draw.line(self.screen, C_BORDER, (mx + 18, row_y + 20), (mx + mw - 18, row_y + 20), 1)
            row_y += 26

        # Highlight takeaway box
        sum_box = pygame.Rect(mx + 18, row_y + 8, mw - 36, 52)
        pygame.draw.rect(self.screen, C_BG, sum_box, border_radius=6)

        t1 = self.f_body_bold.render(
            f"Alpha-Beta Pruning saved {d['saved_nodes']:,} nodes ({d['reduction_pct']:.1f}% reduction)!",
            True, (134, 239, 172)
        )
        t2 = self.f_small.render(
            "It guarantees the exact same optimal decision while exploring a fraction of the search tree.",
            True, C_MUTED
        )
        self.screen.blit(t1, (mx + 26, row_y + 14))
        self.screen.blit(t2, (mx + 26, row_y + 36))

        # Close button
        self.btn_modal_close.rect.centerx = mx + mw // 2
        self.btn_modal_close.rect.y = my + mh - 48
        self.btn_modal_close.draw(self.screen, self.anim_tick)

    # ─────────────────────────────────────────────────────────
    # Frame Rendering & Drop Animation
    # ─────────────────────────────────────────────────────────
    def draw_frame(self, falling_disc=None):
        """
        Renders complete frame in correct z-order:
        1. Dark background
        2. Falling disc (drawn behind the rack)
        3. Rack surface (punched transparent holes reveal the disc behind)
        4. Placed discs inside holes
        5. Winning highlight rings
        6. Header preview disc
        7. Redesigned side panel
        8. Modal dialog (if active)
        """
        self.screen.fill(C_BG)

        # In-flight falling disc (behind rack)
        if falling_disc is not None:
            cx, fy, main, hi, rim, sx, sy = falling_disc
            diam = (RADIUS + 8) * 2
            temp_surf = pygame.Surface((diam, diam), pygame.SRCALPHA)
            self.draw_disc(temp_surf, diam // 2, diam // 2, main, hi, rim)

            sw = max(1, int(diam * sx))
            sh = max(1, int(diam * sy))
            scaled = pygame.transform.smoothscale(temp_surf, (sw, sh))
            self.screen.blit(scaled, (int(cx) - sw // 2, int(fy) - sh // 2))

        # Rack with transparent holes
        self.screen.blit(self._rack_surf, (0, HEADER_H))

        # Accent bar across top of rack
        pygame.draw.line(self.screen, (96, 165, 250), (0, HEADER_H), (BOARD_W, HEADER_H), 3)

        # Placed discs, highlights, preview, and panel
        self.draw_placed_discs()
        self.draw_winning_rings()
        self.draw_preview_disc()
        self.draw_column_labels()
        self.draw_side_panel()
        self.draw_comparison_modal()

        pygame.display.flip()

    def draw_column_labels(self):
        """Draws clear column numbers 1 to 7 right above the rack."""
        for c in range(COLS):
            cx = c * CELL + CELL // 2
            is_hovered = False
            if not self.game_over and self.turn == HUMAN and not self.is_ai_thinking:
                mx, _ = pygame.mouse.get_pos()
                if 0 <= mx < BOARD_W and mx // CELL == c:
                    is_hovered = True

            lbl_color = (147, 197, 253) if is_hovered else (148, 163, 184)
            num_surf = self.f_small.render(f"Col {c + 1}", True, lbl_color)
            self.screen.blit(num_surf, num_surf.get_rect(center=(cx, HEADER_H - 12)))

    def animate_disc_drop(self, col, target_row, player):
        """Smooth gravity drop with squash landing."""
        main, hi, rim = self.get_disc_colors(player)
        cx = col * CELL + CELL // 2
        target_y = float(HEADER_H + target_row * CELL + CELL // 2)
        y = 10.0
        vel = 2.0
        gravity = 2.5

        # Fall phase
        while y < target_y:
            y += vel
            vel += gravity
            if y >= target_y:
                y = target_y

            self.anim_tick += 0.05
            self.draw_frame(falling_disc=(cx, y, main, hi, rim, 1.0, 1.0))
            self.clock.tick(60)

        # Squash landing phase (6 frames)
        for frame in range(6):
            t = frame / 6
            sx = 1.0 + 0.22 * math.sin(t * math.pi)
            sy = 1.0 - 0.18 * math.sin(t * math.pi)
            self.anim_tick += 0.05
            self.draw_frame(falling_disc=(cx, target_y, main, hi, rim, sx, sy))
            self.clock.tick(60)

    # ─────────────────────────────────────────────────────────
    # Move Handling & Game Logic
    # ─────────────────────────────────────────────────────────
    def handle_human_move(self, col):
        """Processes human move, checks outcomes, and triggers AI."""
        if self.game_over or self.turn != HUMAN or self.is_ai_thinking:
            return

        if not is_valid_location(self.board, col):
            return

        row = get_next_open_row(self.board, col)
        if row is None:
            return

        # Animate drop and place piece
        self.animate_disc_drop(col, row, HUMAN)
        drop_piece(self.board, row, col, HUMAN)

        if check_winner(self.board, HUMAN):
            self.game_over = True
            self.winner = HUMAN
            self.winning_cells = get_winning_cells(self.board, HUMAN)
            self.status_message = "You Won!"
            self.btn_restart.pulse = True
            return

        if is_board_full(self.board):
            self.game_over = True
            self.status_message = "Draw Game!"
            self.btn_restart.pulse = True
            return

        # Trigger AI move
        self.turn = AI
        self.status_message = "AI is Thinking..."
        self.draw_frame()
        self.handle_ai_move()

    def handle_ai_move(self):
        """Computes AI move with Minimax + Alpha-Beta and executes it."""
        self.is_ai_thinking = True
        self.status_message = "AI is Thinking..."
        self.draw_frame()

        # Save the board state right before AI moves for accurate comparison benchmarking
        self.last_board_before_ai = [row[:] for row in self.board]

        col, stats = get_ai_move(self.board, depth=self.depth, difficulty=self.difficulty_name)

        if col is not None and is_valid_location(self.board, col):
            row = get_next_open_row(self.board, col)
            self.animate_disc_drop(col, row, AI)
            drop_piece(self.board, row, col, AI)

            if check_winner(self.board, AI):
                self.game_over = True
                self.winner = AI
                self.winning_cells = get_winning_cells(self.board, AI)
                self.status_message = "AI Won!"
                self.btn_restart.pulse = True
            elif is_board_full(self.board):
                self.game_over = True
                self.status_message = "Draw Game!"
                self.btn_restart.pulse = True
            else:
                self.turn = HUMAN
                self.status_message = "Your Turn"

        self.is_ai_thinking = False

    def run_benchmark(self):
        """Runs the algorithm comparison modal."""
        self.status_message = "Comparing..."
        self.draw_frame()

        depth = min(3, self.depth)
        # Benchmark the board state where AI made its last move (if available), else current board
        target_board = self.last_board_before_ai if self.last_board_before_ai is not None else self.board
        is_last_move = (self.last_board_before_ai is not None)

        self.comparison_data = compare_algorithms(target_board, depth=depth)
        self.comparison_data["is_last_move"] = is_last_move
        self.show_comparison_modal = True
        self.status_message = "Comparison Ready!"

    # ─────────────────────────────────────────────────────────
    # Main Event Loop
    # ─────────────────────────────────────────────────────────
    def run(self):
        running = True
        while running:
            self.clock.tick(60)
            self.anim_tick += 0.05

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                # Handle Modal interaction
                if self.show_comparison_modal:
                    if self.btn_modal_close.clicked(event):
                        self.show_comparison_modal = False
                    elif event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                        self.show_comparison_modal = False
                    elif event.type == pygame.MOUSEBUTTONDOWN:
                        mw, mh = 570, 410
                        mr = pygame.Rect((WIN_W - mw) // 2, (WIN_H - mh) // 2, mw, mh)
                        if not mr.collidepoint(event.pos):
                            self.show_comparison_modal = False
                    continue

                # Keyboard Shortcuts
                if event.type == pygame.KEYDOWN:
                    k = event.key
                    if k == pygame.K_ESCAPE:
                        running = False
                    elif k == pygame.K_r:
                        self.reset_game()
                    elif k == pygame.K_1:
                        self.set_difficulty("Easy")
                    elif k == pygame.K_2:
                        self.set_difficulty("Medium")
                    elif k == pygame.K_3:
                        self.set_difficulty("Hard")
                    elif k == pygame.K_c:
                        self.run_benchmark()

                # Difficulty Button clicks
                for name, btn in self.diff_buttons.items():
                    if btn.clicked(event):
                        self.set_difficulty(name)

                # Action Button clicks
                if self.btn_restart.clicked(event):
                    self.reset_game()
                elif self.btn_compare.clicked(event):
                    self.run_benchmark()
                elif self.btn_quit.clicked(event):
                    running = False

                # Board drop click
                if (event.type == pygame.MOUSEBUTTONDOWN and event.button == 1
                        and not self.game_over and not self.is_ai_thinking
                        and self.turn == HUMAN):
                    mx, _ = event.pos
                    if 0 <= mx < BOARD_W:
                        self.handle_human_move(mx // CELL)

            self.draw_frame()

        pygame.quit()
        sys.exit()


if __name__ == "__main__":
    ConnectFourApp().run()

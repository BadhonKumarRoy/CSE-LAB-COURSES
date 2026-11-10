import pygame
import math

# ─────────────────────────────────────────────────────────────
# GRID & WINDOW DIMENSIONS
# ─────────────────────────────────────────────────────────────
ROWS     = 6
COLS     = 7
CELL     = 90                  # Pixel size per grid cell
RADIUS   = 36                  # Disc radius

BOARD_W  = COLS * CELL         # 630 px
PANEL_W  = 300                 # 300 px
WIN_W    = BOARD_W + PANEL_W   # 930 px
HEADER_H = 90                  # Drop preview zone
BOARD_H  = ROWS * CELL         # 540 px
WIN_H    = HEADER_H + BOARD_H  # 630 px

# Player Tokens
EMPTY = 0
HUMAN = 1   # Red
AI    = 2   # Yellow

# AI Search Depths
DIFFICULTIES = {"Easy": 2, "Medium": 3, "Hard": 5}

# ─────────────────────────────────────────────────────────────
# COLOR PALETTE
# ─────────────────────────────────────────────────────────────
C_BG          = (13, 17, 28)       # Deep slate canvas
C_PANEL       = (18, 24, 38)       # Side panel background
C_CARD        = (25, 33, 52)       # Card background
C_CARD_HOVER  = (32, 42, 66)
C_BORDER      = (42, 56, 86)       # Subtle card / panel border
C_BORDER_HI   = (65, 85, 130)      # Highlighted border

# Connect Four Rack
C_RACK        = (28, 62, 155)      # Vibrant royal blue rack
C_RACK_EDGE   = (18, 40, 105)      # Deep rack shadow
C_HOLE        = (9, 13, 23)        # Empty slot dark shade

# Player Discs (Glossy Sphere)
C_RED         = (235, 55, 55)
C_RED_HI      = (255, 140, 140)
C_RED_RIM     = (135, 20, 20)

C_YEL         = (248, 195, 25)
C_YEL_HI      = (255, 242, 155)
C_YEL_RIM     = (170, 120, 5)

# Win Indicator
C_WIN         = (34, 197, 94)      # Vibrant emerald green

# Typography Colors
C_WHITE       = (248, 250, 252)
C_MUTED       = (148, 163, 184)
C_ACCENT      = (96, 165, 250)     # Sky blue

# Action Button Colors
C_BTN_GREEN       = (16, 165, 105)
C_BTN_GREEN_H     = (22, 195, 125)
C_BTN_GREEN_BORDER = (5, 130, 80)

C_BTN_PURPLE      = (124, 58, 237)
C_BTN_PURPLE_H    = (139, 92, 246)
C_BTN_PURPLE_BORDER = (90, 35, 190)

C_BTN_RED         = (225, 29, 72)
C_BTN_RED_H       = (244, 63, 94)
C_BTN_RED_BORDER  = (170, 15, 50)

# Difficulty Selector Button Colors
C_BTN_DIFF        = (27, 36, 58)
C_BTN_DIFF_H      = (38, 51, 82)
C_BTN_ACTIVE      = (37, 99, 235)


# ─────────────────────────────────────────────────────────────
# COLOR INTERPOLATION HELPERS
# ─────────────────────────────────────────────────────────────
def lerp(a, b, t):
    t = max(0.0, min(1.0, t))
    return a + (b - a) * t


def lerp_color(c1, c2, t):
    return (int(lerp(c1[0], c2[0], t)),
            int(lerp(c1[1], c2[1], t)),
            int(lerp(c1[2], c2[2], t)))


# ─────────────────────────────────────────────────────────────
# BUTTON COMPONENT
# ─────────────────────────────────────────────────────────────
class Button:

    SPEED = 0.18

    def __init__(self, rect, text,
                 bg=C_BTN_DIFF, hover=C_BTN_DIFF_H,
                 border_color=None, fg=C_WHITE,
                 size=14, radius=8, active=False):
        self.rect         = pygame.Rect(rect)
        self.text         = text
        self.bg           = bg
        self.hover        = hover
        self.border_color = border_color
        self.fg           = fg
        self.radius       = radius
        self.active       = active
        self.pulse        = False
        self._t           = 0.0
        self.font         = pygame.font.SysFont("Segoe UI, Arial, sans-serif", size, bold=True)

    def draw(self, surf, tick=0.0):
        hovered  = self.rect.collidepoint(pygame.mouse.get_pos())
        target_t = 1.0 if hovered else 0.0
        self._t += (target_t - self._t) * self.SPEED
        self._t  = max(0.0, min(1.0, self._t))

        # Base color selection
        if self.active:
            body_color = lerp_color(C_BTN_ACTIVE, (59, 130, 246), self._t * 0.3)
            bdr_color  = (147, 197, 253)
        else:
            body_color = lerp_color(self.bg, self.hover, self._t)
            if self.border_color:
                bdr_color = self.border_color
            else:
                bdr_color = lerp_color(C_BORDER, C_BORDER_HI, self._t)

        # Draw main button body
        pygame.draw.rect(surf, body_color, self.rect, border_radius=self.radius)

        # Draw crisp border
        border_width = 2 if self.active else 1
        pygame.draw.rect(surf, bdr_color, self.rect, width=border_width, border_radius=self.radius)

        # Breathing green border when game is finished (calls attention to restart)
        if self.pulse:
            pw = max(1, int(2 + math.sin(tick * 5) * 1.5))
            pygame.draw.rect(surf, C_WIN, self.rect, width=pw, border_radius=self.radius)

        # Render button label cleanly centered
        label = self.font.render(self.text, True, self.fg)
        surf.blit(label, label.get_rect(center=self.rect.center))

    def clicked(self, event):
        return (event.type == pygame.MOUSEBUTTONDOWN
                and event.button == 1
                and self.rect.collidepoint(event.pos))

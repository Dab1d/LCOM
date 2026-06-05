#!/usr/bin/env python3
"""
Extract first-row cars from pixellab (intact) and ddasdas (burning) images,
generate intermediate damage states and exploded states, and output XPM files.

Output structure:
  proj/src/assets/xpm/elements/cars/carN/pP/sS.xpm
  N = 1..4 (car design), P = 1 (blue/p1) or 2 (red/p2), S = 1..4 (damage state)
"""

import os
import colorsys
import numpy as np
from PIL import Image

PROJ_ROOT = os.path.dirname(os.path.abspath(__file__))
PIXELLAB_PNG = os.path.join(PROJ_ROOT, "proj", "pixellab-pixel-art-red-car--view-from-a-1780353289912.png")
DDASDAS_PNG  = os.path.join(PROJ_ROOT, "proj", "ddasdas.png")
OUT_BASE     = os.path.join(PROJ_ROOT, "proj", "src", "assets", "xpm", "elements", "cars")

CELL_W = 64
CELL_H = 64
N_CARS = 4   # first 4 cars from row 0


# ── colour helpers ────────────────────────────────────────────────────────────

def red_to_blue(arr: np.ndarray) -> np.ndarray:
    """Hue-shift an RGBA image: red -> blue (player-1 variant)."""
    result = arr.copy().astype(np.float32)
    for y in range(arr.shape[0]):
        for x in range(arr.shape[1]):
            r, g, b, a = arr[y, x]
            if a < 128:
                continue
            h, s, v = colorsys.rgb_to_hsv(r / 255.0, g / 255.0, b / 255.0)
            if s > 0.20:           # only shift saturated colours
                h = (h + 0.65) % 1.0
            nr, ng, nb = colorsys.hsv_to_rgb(h, s, v)
            result[y, x] = [nr * 255, ng * 255, nb * 255, a]
    return result.astype(np.uint8)


def generate_damaged(intact: np.ndarray, burning: np.ndarray) -> np.ndarray:
    """
    Intermediate damage state:
    - fire pixels from burning overlaid at 40% on intact
    - dark/scorch pixels from burning darken intact by 35%
    """
    result = intact.copy().astype(np.float32)
    b = burning.astype(np.float32)
    i = intact.astype(np.float32)

    fire_mask  = (burning[:,:,0] > 150) & (burning[:,:,1] < 150) & (burning[:,:,3] > 50)
    scorch_mask = (burning[:,:,0] < 80)  & (burning[:,:,1] < 80)  & \
                  (burning[:,:,2] < 80)  & (burning[:,:,3] > 50)

    result[fire_mask, :3]   = i[fire_mask,  :3] * 0.60 + b[fire_mask,  :3] * 0.40
    result[scorch_mask, :3] = i[scorch_mask,:3] * 0.65
    result[:,:,3] = i[:,:,3]   # keep original alpha

    return np.clip(result, 0, 255).astype(np.uint8)


def generate_exploded(burning: np.ndarray) -> np.ndarray:
    """Very dark/charred version of the burning state."""
    result = burning.copy().astype(np.float32)
    mask = burning[:,:,3] > 50
    result[mask, :3] *= 0.25
    result[:,:,3] = burning[:,:,3]
    return np.clip(result, 0, 255).astype(np.uint8)


# ── XPM writer ────────────────────────────────────────────────────────────────

_XPM_CHARS = (
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "!#$%&()*+,-./:;<=>?@[]^_{|}~"
)


def _make_key(idx: int, cpp: int) -> str:
    base = len(_XPM_CHARS)
    if cpp == 1:
        return _XPM_CHARS[idx]
    return _XPM_CHARS[idx // base] + _XPM_CHARS[idx % base]


def to_xpm(arr: np.ndarray, var_name: str) -> str:
    h, w = arr.shape[:2]

    # Build palette (RGBA → key)
    colour_map: dict[tuple, str] = {}
    palette_lines: list[str] = []

    def add_colour(rgba):
        if rgba in colour_map:
            return
        idx = len(colour_map)
        cpp = 2  # always use 2 chars/pixel for safety
        key = _make_key(idx, cpp)
        colour_map[rgba] = key
        r, g, b, a = rgba
        if a < 128:
            palette_lines.append(f'"{key}\tc None"')
        else:
            palette_lines.append(f'"{key}\tc #{r:02x}{g:02x}{b:02x}"')

    # First pass: collect colours
    for y in range(h):
        for x in range(w):
            r, g, b, a = arr[y, x]
            add_colour((int(r), int(g), int(b), int(a)))

    n_colours = len(colour_map)
    cpp = 2

    # Pixel rows
    pixel_lines = []
    for y in range(h):
        row = ""
        for x in range(w):
            r, g, b, a = arr[y, x]
            row += colour_map[(int(r), int(g), int(b), int(a))]
        pixel_lines.append(f'"{row}"')

    lines = [f'/* XPM */\nstatic char *{var_name}[] = {{']
    lines.append(f'"{w} {h} {n_colours} {cpp}",')
    lines.extend(l + "," for l in palette_lines)
    for i, pl in enumerate(pixel_lines):
        if i < len(pixel_lines) - 1:
            lines.append(pl + ",")
        else:
            lines.append(pl)
    lines.append("};")
    return "\n".join(lines) + "\n"


# ── main ──────────────────────────────────────────────────────────────────────

def write_xpm(arr: np.ndarray, var_name: str, path: str):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    content = to_xpm(arr, var_name)
    with open(path, "w") as f:
        f.write(content)
    print(f"  wrote {path}")


def main():
    intact_img  = Image.open(PIXELLAB_PNG).convert("RGBA")
    burning_img = Image.open(DDASDAS_PNG).convert("RGBA")

    intact_arr  = np.array(intact_img)
    burning_arr = np.array(burning_img)

    for car_idx in range(N_CARS):
        car_n = car_idx + 1
        print(f"\n=== car{car_n} ===")

        x0 = car_idx * CELL_W
        s1_red = intact_arr [0:CELL_H, x0:x0+CELL_W]   # normal  (pixellab)
        s3_red = burning_arr[0:CELL_H, x0:x0+CELL_W]   # burning (ddasdas)
        s2_red = generate_damaged (s1_red, s3_red)       # intermediate
        s4_red = generate_exploded(s3_red)               # exploded (charred)

        s1_blue = red_to_blue(s1_red)
        s2_blue = red_to_blue(s2_red)
        s3_blue = red_to_blue(s3_red)
        s4_blue = red_to_blue(s4_red)

        states_p1 = [s1_blue, s2_blue, s3_blue, s4_blue]
        states_p2 = [s1_red,  s2_red,  s3_red,  s4_red ]

        for player_idx, states in enumerate([states_p1, states_p2]):
            p = player_idx + 1
            for state_idx, arr in enumerate(states):
                s = state_idx + 1
                var_name = f"car{car_n}_p{p}_s{s}"
                path = os.path.join(OUT_BASE, f"car{car_n}", f"p{p}", f"s{s}.xpm")
                write_xpm(arr, var_name, path)

    print("\nDone. 32 XPM files generated.")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""
img_to_xpm.py — converte uma imagem para XPM 64x64 usando a paleta de palette.c

Uso:
    python3 img_to_xpm.py <imagem> <output.xpm> [<nome_variavel>]

Exemplo:
    python3 img_to_xpm.py car_blue.png ../src/assets/xpm/cars/car_blue.xpm car_blue

Dependências:
    pip install Pillow
"""

import re
import sys
import os
from PIL import Image

PALETTE_C = os.path.join(os.path.dirname(__file__),
                         "../src/controller/palette/palette.c")

TARGET_W = 64
TARGET_H = 64
TRANSPARENT_RGB = (0xFF, 0x00, 0xFF)


def load_palette(path):
    """Extrai os 256 triplos RGB do GAME_PALETTE em palette.c."""
    with open(path) as f:
        src = f.read()

    # Apanha todos os { 0xRR, 0xGG, 0xBB }
    entries = re.findall(r'\{(0x[0-9A-Fa-f]{2}),\s*(0x[0-9A-Fa-f]{2}),\s*(0x[0-9A-Fa-f]{2})\}', src)
    if len(entries) != 256:
        raise ValueError(f"Esperava 256 entradas na paleta, encontrei {len(entries)}")
    return [(int(r, 16), int(g, 16), int(b, 16)) for r, g, b in entries]


def nearest_index(palette, r, g, b):
    """Devolve o índice da cor mais próxima na paleta (igual ao palette_find_index em C)."""
    if (r, g, b) == TRANSPARENT_RGB:
        return 255  # PAL_TRANSPARENT
    best_i, best_d = 0, 0x7FFFFFFF
    for i, (pr, pg, pb) in enumerate(palette[:255]):  # ignora o slot 255 (transparente)
        d = (r - pr)**2 + (g - pg)**2 + (b - pb)**2
        if d < best_d:
            best_d, best_i = d, i
            if d == 0:
                break
    return best_i


def index_to_chars(i):
    """Converte índice 0-255 em código de 2 chars para XPM (aa, ab, …, zz)."""
    chars = "abcdefghijklmnopqrstuvwxyz"
    return chars[i // 26] + chars[i % 26]


def convert(img_path, out_path, var_name, palette):
    img = Image.open(img_path).convert("RGBA").resize(
        (TARGET_W, TARGET_H), Image.LANCZOS)

    pixels = []
    used = {}  # índice → cor original

    for y in range(TARGET_H):
        row = []
        for x in range(TARGET_W):
            r, g, b, a = img.getpixel((x, y))
            if a < 128:
                r, g, b = TRANSPARENT_RGB  # força transparente
            idx = nearest_index(palette, r, g, b)
            row.append(idx)
            if idx not in used:
                used[idx] = palette[idx]
        pixels.append(row)

    num_colors = len(used)
    chars_per_pixel = 2

    lines = []
    lines.append("/* XPM */")
    lines.append(f"static char *{var_name}[] = {{")
    lines.append(f'"{TARGET_W} {TARGET_H} {num_colors} {chars_per_pixel}",')

    # Definições de cores
    for idx in sorted(used):
        pr, pg, pb = used[idx]
        if idx == 255:
            lines.append(f'"{index_to_chars(idx)} c None",')
        else:
            lines.append(f'"{index_to_chars(idx)} c #{pr:02X}{pg:02X}{pb:02X}",')

    lines.append("/* pixels */")
    for y, row in enumerate(pixels):
        s = "".join(index_to_chars(i) for i in row)
        comma = "," if y < TARGET_H - 1 else ""
        lines.append(f'"{s}"{comma}')

    lines.append("};")

    os.makedirs(os.path.dirname(out_path) or ".", exist_ok=True)
    with open(out_path, "w") as f:
        f.write("\n".join(lines) + "\n")

    print(f"OK: {out_path}  ({TARGET_W}x{TARGET_H}, {num_colors} cores)")


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        sys.exit(1)

    img_path = sys.argv[1]
    out_path = sys.argv[2]
    var_name = sys.argv[3] if len(sys.argv) >= 4 else \
               os.path.splitext(os.path.basename(out_path))[0]

    palette = load_palette(PALETTE_C)
    convert(img_path, out_path, var_name, palette)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Gera os 3 tiles de desert em falta: tile_road_desert, tile_sand, tile_divider."""

import re, os, sys

PALETTE_C = os.path.join(os.path.dirname(__file__),
                         "../src/controller/palette/palette.c")
OUT_DIR   = os.path.join(os.path.dirname(__file__),
                         "../src/assets/xpm/tiles")

W, H = 64, 64

# ── Paleta ────────────────────────────────────────────────────────────────────

def load_palette(path):
    with open(path) as f: src = f.read()
    entries = re.findall(
        r'\{(0x[0-9A-Fa-f]{2}),\s*(0x[0-9A-Fa-f]{2}),\s*(0x[0-9A-Fa-f]{2})\}', src)
    assert len(entries) == 256, f"Esperava 256, encontrei {len(entries)}"
    return [(int(r,16), int(g,16), int(b,16)) for r,g,b in entries]

def nearest(palette, r, g, b):
    if (r,g,b) == (0xFF,0x00,0xFF): return 255
    best_i, best_d = 0, 0x7FFFFFFF
    for i,(pr,pg,pb) in enumerate(palette[:255]):
        d = (r-pr)**2+(g-pg)**2+(b-pb)**2
        if d < best_d:
            best_d, best_i = d, i
            if d == 0: break
    return best_i

# ── XPM writer ────────────────────────────────────────────────────────────────

def write_xpm(path, var, pixels, palette):
    used = {}
    for row in pixels:
        for idx in row:
            if idx not in used: used[idx] = palette[idx]

    def ch(i):
        a = "abcdefghijklmnopqrstuvwxyz"
        return a[i//26] + a[i%26]

    lines = ["/* XPM */", f"static char *{var}[] = {{",
             f'"{W} {H} {len(used)} 2",']
    for idx in sorted(used):
        r,g,b = used[idx]
        col = "None" if idx == 255 else f"#{r:02X}{g:02X}{b:02X}"
        lines.append(f'"{ch(idx)} c {col}",')
    lines.append("/* pixels */")
    for y, row in enumerate(pixels):
        s = "".join(ch(i) for i in row)
        lines.append(f'"{s}"' + ("," if y < H-1 else ""))
    lines.append("};")

    os.makedirs(path.rsplit("/",1)[0], exist_ok=True)
    with open(path, "w") as f: f.write("\n".join(lines) + "\n")
    print(f"  criado: {path}")

# ── Designs dos tiles ─────────────────────────────────────────────────────────

def make_road_desert(pal):
    """Pista de deserto: alcatrão arenoso + marcações de faixa a tracejado."""
    C_BASE   = nearest(pal, 0x6B, 0x55, 0x3A)  # asfalto arenoso escuro
    C_MID    = nearest(pal, 0x7A, 0x64, 0x48)  # asfalto arenoso médio
    C_EDGE   = nearest(pal, 0x50, 0x3E, 0x28)  # borda escura
    C_MARK   = nearest(pal, 0xF0, 0xF0, 0xF0)  # marcação branca (dashes)
    C_SAND   = nearest(pal, 0x9E, 0x82, 0x58)  # grão de areia claro

    import random; rng = random.Random(42)

    pix = []
    for y in range(H):
        row = []
        for x in range(W):
            # Bordas da lane
            if x < 2 or x >= W-2:
                row.append(C_EDGE)
            # Marcação tracejada no centro (cols 30-33, a cada 16 px)
            elif 30 <= x <= 33 and (y % 16) < 8:
                row.append(C_MARK)
            # Grãos de areia aleatórios (textura)
            elif rng.random() < 0.06:
                row.append(C_SAND)
            elif rng.random() < 0.04:
                row.append(C_EDGE)
            else:
                row.append(C_BASE if rng.random() < 0.6 else C_MID)
        pix.append(row)
    return pix

def make_sand(pal):
    """Areia do deserto para cenário lateral."""
    C_BASE  = nearest(pal, 0xD4, 0xA8, 0x53)  # areia quente
    C_LIGHT = nearest(pal, 0xE8, 0xC5, 0x70)  # destaque
    C_DARK  = nearest(pal, 0xB8, 0x8C, 0x38)  # sombra
    C_GRAIN = nearest(pal, 0xCC, 0x99, 0x44)  # grão médio
    C_ROCK  = nearest(pal, 0x8B, 0x73, 0x55)  # pedrinhas

    import random; rng = random.Random(7)

    pix = []
    for y in range(H):
        row = []
        for x in range(W):
            r = rng.random()
            if r < 0.04:   row.append(C_ROCK)
            elif r < 0.10: row.append(C_DARK)
            elif r < 0.20: row.append(C_LIGHT)
            elif r < 0.35: row.append(C_GRAIN)
            else:          row.append(C_BASE)
        pix.append(row)
    return pix

def make_divider(pal):
    """Separador central: murete de betão com listas vermelhas/brancas."""
    C_CONC_D = nearest(pal, 0x66, 0x66, 0x66)  # betão escuro
    C_CONC_L = nearest(pal, 0x99, 0x99, 0x99)  # betão claro
    C_RED    = nearest(pal, 0xFF, 0x22, 0x22)  # lista vermelha
    C_WHITE  = nearest(pal, 0xF0, 0xF0, 0xF0)  # lista branca
    C_SHADOW = nearest(pal, 0x33, 0x33, 0x33)  # sombra base

    pix = []
    for y in range(H):
        row = []
        for x in range(W):
            # Sombra no chão (2px base)
            if y >= H-2:
                row.append(C_SHADOW)
            # Murete ocupa cols 16-47 (32px de largura)
            elif 16 <= x < 48:
                # Topo do murete (3px)
                if y < 3:
                    row.append(C_CONC_L)
                # Parede: listas diagonais vermelhas/brancas
                else:
                    stripe = ((x - 16) + y) // 8
                    row.append(C_RED if stripe % 2 == 0 else C_WHITE)
            # Lado esquerdo fora do murete: asfalto
            else:
                row.append(C_CONC_D if (x + y) % 3 != 0 else C_SHADOW)
        pix.append(row)
    return pix

# ── Main ──────────────────────────────────────────────────────────────────────

def main():
    pal = load_palette(PALETTE_C)
    tiles = [
        ("tile_road_desert_xpm", "tile_road_desert.xpm", make_road_desert(pal)),
        ("tile_sand_xpm",        "tile_sand.xpm",        make_sand(pal)),
        ("tile_divider_xpm",     "tile_divider.xpm",     make_divider(pal)),
    ]
    for var, fname, pix in tiles:
        write_xpm(os.path.join(OUT_DIR, fname), var, pix, pal)
    print("Feito.")

if __name__ == "__main__":
    main()

#!/usr/bin/env python3
import re
from pathlib import Path

SRC = Path("words_alpha.txt")
OUT = Path("Wordle_wordlists_all.cpp")

if not SRC.exists():
    print(f"Error: {SRC} not found. Download words_alpha.txt into the script folder.")
    raise SystemExit(1)

# collect words by length
easy = []
med = []
hard = []
seen = set()

with SRC.open(encoding="utf-8") as f:
    for line in f:
        w = line.strip().lower()
        if not w or not re.fullmatch(r"[a-z]+", w):
            continue
        if w in seen:
            continue
        seen.add(w)
        L = len(w)
        if L == 4:
            easy.append(w)
        elif L == 5:
            med.append(w)
        elif L == 6:
            hard.append(w)

def write_array(f, name, words, row_len):
    f.write(f"// {len(words)} words, each {row_len-1} letters\n")
    f.write(f'char {name}[][ {row_len} ] = {{\n')
    for i, w in enumerate(words):
        entry = f'"{w}"'
        if i != len(words) - 1:
            entry += ","
        if (i % 10) == 9:
            f.write(entry + "\n")
        else:
            f.write(entry + " ")
    f.write("\n};\n\n")

with OUT.open("w", encoding="utf-8") as out:
    out.write("// Auto-generated word arrays - generated from words_alpha.txt\n")
    out.write('#include "config.h"\n\n')
    write_array(out, "easyWords", easy, 4 + 1)
    write_array(out, "mediumWords", med, 5 + 1)
    write_array(out, "hardWords", hard, 6 + 1)
    out.write(f"const int EASY_WORD_COUNT = {len(easy)};\n")
    out.write(f"const int MEDIUM_WORD_COUNT = {len(med)};\n")
    out.write(f"const int HARD_WORD_COUNT = {len(hard)};\n")

print(f"Wrote {OUT} (4:{len(easy)} 5:{len(med)} 6:{len(hard)})")
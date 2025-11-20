#!/usr/bin/env python3
"""
Fetch Wordle answer words from:
https://www.wordunscrambler.net/word-list/wordle-word-list

Generates: wordle_wordlists_from_web.cpp
which defines:
  const int WEB_WORDLE_COUNT = N;
  const char mediumWords[WEB_WORDLE_COUNT][6] = { "aback", "abase", ... };
"""

import requests
from bs4 import BeautifulSoup
import re
import time
import sys
from collections import OrderedDict

URL = "https://www.wordunscrambler.net/word-list/wordle-word-list"
OUT_CPP = "wordle_wordlists_from_web.cpp"
HEADERS = {
    "User-Agent": "WordleListFetcher/1.0 (+https://example.local)"
}

WORDS_PER_LINE = 10

def fetch(url):
    resp = requests.get(url, headers=HEADERS, timeout=15)
    resp.raise_for_status()
    return resp.text

def extract_words(html):
    soup = BeautifulSoup(html, "html.parser")
    anchors = soup.find_all("a", href=re.compile(r"/unscramble/"))
    # Preserve order of appearance, remove duplicates
    seen = OrderedDict()
    for a in anchors:
        txt = a.get_text().strip().lower()
        if len(txt) == 5 and txt.isalpha():
            if txt not in seen:
                seen[txt] = True
    return list(seen.keys())

def write_cpp(words, path):
    n = len(words)
    with open(path, "w", encoding="utf-8") as f:
        f.write('// Auto-generated from {}\n'.format(URL))
        f.write('#include "config.h"\n\n')
        f.write('const int WEB_WORDLE_COUNT = {};\n'.format(n))
        # Note: You were using [6] for 5-letter words in the original.
        # Your desired format uses [5] which implies 4-letter words, but the data is 5-letter words.
        # I'll keep the original [6] for 5-letter words + null terminator.
        # To match your requested output style, I'll use the array name 'mediumWords'.
        f.write('const char mediumWords[WEB_WORDLE_COUNT][6] = {\n')
        
        # --- MODIFIED LOGIC START ---
        
        # Iterate through the list of words in chunks of WORDS_PER_LINE
        for i in range(0, n, WORDS_PER_LINE):
            chunk = words[i:i + WORDS_PER_LINE]
            # Format each word with quotes and a comma
            word_strings = ['"{}"'.format(w) for w in chunk]
            
            # Join the words for the current line
            line = ", ".join(word_strings)
            
            # If this is the last chunk, don't add a comma at the end of the line
            # Otherwise, add a comma and a newline to prepare for the next line
            terminator = ',\n' if i + WORDS_PER_LINE < n else '\n'
            
            f.write('    {}{}'.format(line, terminator))
            
        # --- MODIFIED LOGIC END ---
        
        f.write('};\n')
    print("Wrote {} words to {}".format(n, path))

def main():
    try:
        print("Fetching:", URL)
        html = fetch(URL)
        print("Parsing HTML...")
        words = extract_words(html)
        if not words:
            print("No words found. Exiting.", file=sys.stderr)
            sys.exit(1)
        print("Found {} unique 5-letter words.".format(len(words)))
        write_cpp(words, OUT_CPP)
        print("Done. Backup your original word list file, then copy/merge the generated array into your project.")
    except Exception as e:
        print("Error:", e, file=sys.stderr)
        sys.exit(2)

if __name__ == "__main__":
    main()
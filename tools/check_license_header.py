#!/usr/bin/env python3

import re
from pathlib import Path

title = 'SDLXX - Modern C++ wrapper for Simple DirectMedia Layer (SDL2)'

text = title + '\n\n' + Path('../LICENSE.md').read_text()

expected_header = '/*\n' + re.sub(r'^(?=.)', '  ', text, flags=re.M) + '*/\n'

num_lines = len(expected_header.splitlines())

for path in Path('../include/').glob('**/*.h'):
    content = path.read_text().splitlines()[:num_lines]
    if content != expected_header.splitlines():
        print('Wrong header:', path)

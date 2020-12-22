#!/usr/bin/env python3

import sys
import re

with open(sys.argv[1], 'r') as in_file:
    printing = True

    for line in in_file:
        stripped_line = line.strip()

        if re.match(r'\w*// <<<', stripped_line):
            printing = False
        elif re.match(r'\w*// >>>', stripped_line):
            printing = True
        elif re.match(r'\w*// ===', stripped_line):
            print(line.replace('// ===', ''), end='')
        elif printing:
            print(line, end='')

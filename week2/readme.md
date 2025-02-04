# File I/O Performance Benchmark (Python vs C)

## Overview
This project compares the execution time of file writing and reading in **Python** and **C**.

## Programs Used
- `file_io.py` → Python script for file I/O.
- `file_io.c` → C program for file I/O.

## How to Run
### C Program:
```bash
gcc file_io.c -o ~/bin/file_io
time ~/bin/file_io
time python3 file_io.py
# File I/O Performance Benchmark (Python vs C)

## Overview
This project compares the execution time of file writing and reading in **Python** and **C**.

## Programs Used
- `file_io.py` → Python script for file I/O.
- `file_io.c` → C program for file I/O.

## How to Run
### C Program:
```bash
gcc file_io.c -o ~/bin/file_io
time ~/bin/file_io

###Python
time python3 file_io.py

###Analysis
#C is ~5x faster than Python for file I/O due to direct OS interaction.
#Python has high CPU (user) time due to interpreted execution.
#C has slightly higher sys time since it manages low-level file operations.

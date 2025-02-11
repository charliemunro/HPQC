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
```

### Python Program:
```bash
time python3 file_io.py
```

## Performance Results

| Language  | Measured Time (in script) | `real` Time | `user` Time | `sys` Time |
|-----------|---------------------------|-------------|-------------|-------------|
| **Python** | **0.009377 sec**          | 0m0.047s    | 0m0.036s    | 0m0.001s    |
| **C**      | **(Printed "File content: Hello, world!")** | 0m0.009s | 0m0.000s | 0m0.003s |

## Analysis
- **C is ~5x faster** than Python for file I/O due to direct OS interaction.
- **Python has high CPU (`user`) time** due to interpreted execution.
- **C has slightly higher `sys` time** since it manages low-level file operations.

## Conclusion
For file-intensive applications, **C is significantly faster**. Python remains a great choice for ease of use but sacrifices performance.

## Submission Instructions
- Clone this repository:
  ```bash
  git clone <your-repo-link>
  ```
- Follow the instructions above to run the scripts and verify the results.

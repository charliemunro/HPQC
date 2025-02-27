# String Oscillation Simulation (Week 5)

## Overview
This repository contains two versions of a string oscillation simulation:
1. **Serial Version** (`string_wave.c`)
2. **MPI Version** (`string_wave_mpi.c`)

The MPI version distributes the string’s points among processes, exchanging boundary information at each iteration. The code also includes timing instrumentation to measure total, communication, and computation times using `MPI_Wtime()`.

## Files
- **`string_wave.c`**: Serial implementation  
- **`string_wave_mpi.c`**: MPI parallel implementation  
- **`animate_line_file.py`**: Python script to visualize the CSV output

## Benchmark Results
Below is a sample table of benchmark results for different problem sizes and process counts. Note that these times can vary between runs due to system load and MPI overhead.

| Version         | Points    | Processes | Approx. Real Time  | Notes                                                                    |
|-----------------|-----------|-----------|--------------------|--------------------------------------------------------------------------|
| **Serial**      | 4,800     | 1         | ~0.29 s            | Very small workload; serial overhead is minimal.                         |
| **Serial**      | 4,800,000 | 1         | ~17.93 s           | Baseline for a larger workload.                                          |
| **MPI**         | 4,800,000 | 2         | ~28.25 s           | Overhead outweighed benefits in one test; times vary between runs.       |
| **MPI**         | 4,800,000 | 4         | ~3m23.51 s         | Some runs showed higher times, possibly due to system load or overhead.  |
| **MPI**         | 4,800,000 | 8         | ~22.79 s           | Indicated better performance in one test; inconsistent across runs.      |

**Observations:**
- For **smaller problem sizes**, the **serial version** outperforms MPI due to lower overhead.  
- For **larger workloads**, MPI can potentially speed up computations, but communication overhead and system load can significantly impact results.  
- **Further tests** with larger problem sizes and repeated runs are needed to find the “crossover” point where MPI reliably outperforms the serial version.

## Usage

### Compilation

- **Serial:**
  ```bash
  gcc -g string_wave.c -o bin/string_wave -lm
  ```

- **MPI:**
  ```bash
  mpicc -g string_wave_mpi.c -o bin/string_wave_mpi -lm
  ```

### Running

- **Serial Example:**
  ```bash
  ./bin/string_wave 4800000 5 25 data/string_wave_serial_4800000.csv
  ```

- **MPI Example (4 Processes):**
  ```bash
  mpirun -np 4 ./bin/string_wave_mpi 4800000 5 25 data/string_wave_mpi_4800000_np4.csv
  ```

### Visualization

Use the Python script to animate the CSV output:
```bash
python3 animate_line_file.py data/string_wave_serial_4800000.csv
python3 animate_line_file.py data/string_wave_mpi_4800000_np4.csv
```

## Brief Discussion

Overall, these experiments show that while MPI introduces overhead (particularly at smaller problem sizes), it can offer performance gains at larger scales—though results vary with process counts and system conditions. Continued experimentation with larger workloads and repeated runs will help identify more consistent scaling behavior.

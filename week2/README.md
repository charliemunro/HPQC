
# Week 2: File I/O Benchmarking and Code

This repository contains the code and results for the **Week 2** exercises in the **HPQC** course.

## Files in the Week 2 Folder:
1. `hello_world.c` - Simple C program that prints "Hello, World!".
2. `hello_world.py` - Python version of the "Hello, World!" program.
3. `repeat_adder.c` - C program implementing the "repeat addition" strategy for multiplication.
4. `repeat_adder.py` - Python version of the "repeat addition" strategy for multiplication.
5. `time_print.c` - C program that writes to a file and measures time.
6. `time_print.py` - Python program that writes to a file and measures time.

---

## Benchmarking Results:

### **Hello World Program Execution Time:**

| **Program** | **Execution Time (real)** | **User CPU Time** | **System CPU Time** |
|-------------|---------------------------|-------------------|---------------------|
| **Python**  | 0.067s                    | 0.044s            | 0.020s              |
| **C**       | 0.005s                    | 0.003s            | 0.001s              |

### **Repeat Adder Execution Time:**

| **Program** | **Execution Time (real)** | **User CPU Time** | **System CPU Time** |
|-------------|---------------------------|-------------------|---------------------|
| **Python**  | 0.065s                    | 0.044s            | 0.020s              |
| **C**       | 0.005s                    | 0.003s            | 0.001s              |

---

## File I/O Benchmarking Results:

### **File Writing Time:**

| **Program** | **File Write Time (real)** | **User CPU Time** | **System CPU Time** |
|-------------|----------------------------|-------------------|---------------------|
| **Python**  | 0.723s                     | 0.494s            | 0.069s              |
| **C**       | 0.183s                     | 0.168s            | 0.032s              |

---

## Observations:
1. **C is significantly faster** than Python for both the **"Hello World"** program and the **"Repeat Adder"** program.
   - C programs show much lower execution times for both tasks.

2. **File I/O** in Python incurs higher system and user CPU time, showing that Python's overhead increases when performing large I/O tasks compared to C.

3. The difference between C and Python **scales up** as the task complexity increases, confirming that **C is more efficient** for performance-critical operations such as file writing.

---

## Conclusion:
- **C** is consistently faster than **Python** in terms of execution time, especially when it comes to file I/O operations.
- For tasks that involve intensive computation or file manipulation, **C** is a more efficient choice.

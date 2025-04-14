# Grover's Search Algorithm (Quantum Simulation in Python)

This project is a simple NumPy-based simulation of **Grover's Search**, a quantum algorithm that allows searching an unsorted list of \( N \) items in only \( O(\sqrt{N}) \) time. It was developed as part of the **"Program Your Own Quantum Computer"** tutorial series (Part 2 – Grover's Search).

---

## Features
- Simulates Grover's algorithm for \( n \)-qubit search problems
- Uses classical NumPy arrays to represent quantum state amplitudes
- Implements:
  - Uniform state initialization
  - Phase oracle (marks the target state by sign inversion)
  - Inversion about the mean (diffusion operator)
  - Measurement via maximum amplitude

---

## How It Works
Grover's algorithm works by repeatedly:
1. Flipping the sign of the correct answer's amplitude (phase oracle)
2. Reflecting all amplitudes about their average (diffusion)
3. Repeating for ~\( \frac{\pi}{4}\sqrt{2^n} \) iterations

This amplifies the correct answer’s probability to nearly 1.

---

## Requirements

<pre> <code>pip install numpy</code> </pre>

---

## How to Run

<pre> <code>python grover_search.py</code> </pre>

You should see the probability of the correct solution increasing with each iteration:

<pre> ``` Iter 1: Prob(target) = 0.134827 Iter 2: Prob(target) = 0.343895 ... Result: Most likely state: 0b111101 (decimal 61) Probability: 0.996586 ``` </pre>

---
## Result:
  Most likely state: 0b111101 (decimal 61)
  Probability: 0.996586


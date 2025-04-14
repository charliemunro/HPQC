# Quantum Simulator – Part 3 (GPU-Accelerated)

This project is Part 3 of the **"Program Your Own Quantum Computer"** tutorial series. It expands the quantum simulator by leveraging **GPU acceleration** with **PyTorch**, enabling faster and more scalable simulations.

---

## Features

- Simulates quantum state evolution using PyTorch tensors
- Runs on **CPU** or **GPU** automatically (if CUDA is available)
- Implements Grover’s Algorithm with:
  - Superposition initialization
  - Phase oracle (inverts target state)
  - Diffusion operator (reflect about average)
  - Measurement and probability readout
- Benchmarks runtime for CPU vs GPU

---

## 🛠 Requirements

- Python 3.8+
- [PyTorch](https://pytorch.org) with optional CUDA support
- NumPy

### Install with pip:

pip install torch numpy

### How to Run

python part3_quantum_simulation.py

### Results

GPU available
11111101
With GPU: 0.0034 s


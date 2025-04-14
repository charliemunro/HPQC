# Week 7 – Quantum Simulator (Part 1)

This is a basic quantum simulator implemented in **pure Python with NumPy**, developed as part of Week 7 of the *"Program Your Own Quantum Computer"* tutorial series. It models a single-qubit quantum system with the ability to apply gates and perform probabilistic measurements.

---

## Features

- Stack-based quantum state memory using Kronecker products
- Quantum gate support:
  - **Hadamard Gate (H)** – creates superposition
  - **Pauli-X Gate (X)** – flips qubit state
- Probability calculation and random measurement (wavefunction collapse)
- Fully vectorized using NumPy arrays

---

## Concepts Demonstrated

1. **Qubit Initialization**: Start in a known state (e.g. \(|0⟩\))
2. **Gate Operations**: Apply transformations like Hadamard to rotate the state
3. **Probabilistic Measurement**: Simulate the quantum measurement process using amplitudes
4. **Wavefunction Collapse**: Retain only the measured outcome

---

## File Structure

part1_quantum_simulator.py

---


Contains:
- `pushQubit()` – Adds a new qubit to the workspace
- `applyGate()` – Applies a 2x2 quantum gate
- `probQubit()` – Calculates measurement probabilities
- `measureQubit()` – Simulates measurement and updates state

---

## Requirements

pip install numpy

---

## How to Run

python part1_quantum_simulator.py

---

## Results

Probabilities: [0.5 0.5]
Measurement result: 1



import numpy as np

def initialize(n):
    N = 2**n
    state = np.ones(N) / np.sqrt(N)
    return state

def phase_oracle(state, target):
    state[target] *= -1
    return state

def diffusion_operator(state):
    mean = np.mean(state)
    return 2 * mean - state

def grover_search(n, target, print_steps=False):
    state = initialize(n)
    N = 2**n
    optimal_iters = int(np.pi / 4 * np.sqrt(N))

    for i in range(optimal_iters):
        state = phase_oracle(state, target)
        state = diffusion_operator(state)
        if print_steps:
            probs = state**2
            print(f"Iter {i+1}: Prob(target) = {probs[target]:.6f}")

    return state

def measure(state):
    probs = state**2
    return np.argmax(probs), probs

# --- Run Example ---
n = 6
target = 0b111101  # decimal 61

final_state = grover_search(n, target, print_steps=True)
result, probs = measure(final_state)

print("\nResult:")
print(f"  Most likely state: {bin(result)} (decimal {result})")
print(f"  Probability: {probs[result]:.6f}")

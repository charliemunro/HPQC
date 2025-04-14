import numpy as np

workspace = np.array([[1.]], dtype=np.complex128)

def pushQubit(weights):
    global workspace
    weights = np.array(weights, dtype=workspace.dtype)
    weights = weights / np.linalg.norm(weights)
    workspace = np.reshape(workspace, (1, -1))
    workspace = np.kron(workspace, weights)

def applyGate(gate):
    global workspace
    workspace = np.reshape(workspace, (-1, gate.shape[0]))
    np.matmul(workspace, gate.T, out=workspace)

H_gate = np.array([[1, 1], [1, -1]]) * np.sqrt(0.5)
X_gate = np.array([[0, 1], [1, 0]])

def probQubit():
    global workspace
    workspace = np.reshape(workspace, (-1, 2))
    return np.linalg.norm(workspace, axis=0) ** 2

def measureQubit():
    global workspace
    probs = probQubit()
    outcome = np.random.choice([0, 1], p=probs)
    workspace = workspace[:, [outcome]] / np.sqrt(probs[outcome])
    return outcome

# Example run
if __name__ == "__main__":
    workspace = np.array([[1.]], dtype=np.complex128)
    pushQubit([1, 0])        # |0⟩
    applyGate(H_gate)        # Apply Hadamard
    print("Probabilities:", probQubit())
    print("Measurement result:", measureQubit())

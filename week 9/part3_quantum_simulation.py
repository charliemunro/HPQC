import torch as pt
import numpy as np
import time

pt.autograd.set_grad_enabled(False)

if pt.cuda.is_available():
    print("GPU available")
else:
    print("Sorry, only CPU available")

workspace = pt.tensor([[1.0]], device=pt.device('cuda' if pt.cuda.is_available() else 'cpu'), dtype=pt.float32)
namestack = []

X_gate = np.array([[0, 1], [1, 0]])
H_gate = np.array([[1, 1], [1, -1]]) * np.sqrt(0.5)
Z_gate = H_gate @ X_gate @ H_gate


def pushQubit(name, weights):
    global workspace, namestack
    if (workspace.shape[0], workspace.shape[1]) == (1, 1):
        namestack = []
    namestack.append(name)
    weights = weights / np.linalg.norm(weights)
    weights = pt.tensor(weights, device=workspace.device, dtype=workspace.dtype)
    workspace = pt.reshape(workspace, (1, -1))
    workspace = pt.kron(workspace, weights)


def tosQubit(name):
    global workspace, namestack
    k = len(namestack) - namestack.index(name)
    if k > 1:
        namestack.append(namestack.pop(-k))
        workspace = pt.reshape(workspace, (-1, 2, 2 ** (k - 1)))
        workspace = pt.swapaxes(workspace, -2, -1)


def applyGate(gate, *names):
    global workspace
    if list(names) != namestack[-len(names):]:
        for name in names:
            tosQubit(name)
    workspace = pt.reshape(workspace, (-1, 2 ** len(names)))
    subworkspace = workspace[:, -gate.shape[0]:]
    gate = pt.tensor(gate.T, device=workspace.device, dtype=workspace.dtype)
    if workspace.device.type == 'cuda':
        pt.matmul(subworkspace, gate, out=subworkspace)
    else:
        subworkspace[:, :] = pt.matmul(subworkspace, gate)


def probQubit(name):
    global workspace
    tosQubit(name)
    workspace = pt.reshape(workspace, (-1, 2))
    prob = pt.linalg.norm(workspace, axis=0) ** 2
    prob = pt.Tensor.cpu(prob).numpy()
    return prob / prob.sum()


def measureQubit(name):
    global workspace, namestack
    prob = probQubit(name)
    measurement = np.random.choice(2, p=prob)
    workspace = workspace[:, [measurement]] / np.sqrt(prob[measurement])
    namestack.pop()
    return str(measurement)


def sample_phaseOracle(qubits):
    applyGate(X_gate, qubits[1])
    applyGate(Z_gate, *namestack)
    applyGate(X_gate, qubits[1])


def zero_phaseOracle(qubits):
    for q in qubits:
        applyGate(X_gate, q)
    applyGate(Z_gate, *namestack)
    for q in qubits:
        applyGate(X_gate, q)


def groverSearch(n, printProb=True):
    global workspace
    qubits = list(range(n))
    for q in qubits:
        pushQubit(q, [1, 1])
    for k in range(int(np.pi / 4 * np.sqrt(2 ** n) - 0.5)):
        sample_phaseOracle(qubits)
        for q in qubits:
            applyGate(H_gate, q)
        zero_phaseOracle(qubits)
        for q in qubits:
            applyGate(H_gate, q)
        if printProb:
            print(probQubit(qubits[0]))
    for q in reversed(qubits):
        print(measureQubit(q), end="")
    print()


# Run Grover's search with GPU and CPU
def run_grover():
    global workspace

    device = pt.device('cuda') if pt.cuda.is_available() else pt.device('cpu')
    workspace = pt.tensor([[1.]], device=device, dtype=pt.float32)
    t = time.process_time()
    groverSearch(8, printProb=False)
    print("\nWith GPU:" if device.type == 'cuda' else "\nWith CPU:", time.process_time() - t, "s")


if __name__ == "__main__":
    run_grover()
    workspace = pt.tensor([[1.]], device=pt.device('cpu'), dtype=pt.float32)
    run_grover()

# MiniPerceptron – Perceptron / Simple ANN for Logic Gates

The first neural network: a single perceptron that learns the **AND** and **OR** gates.
Stretch goal: a **Layer of perceptrons** that learns **XOR**.

The code is split into a few small files (see *Project files*). **Nothing is hardcoded** – the gate, training data,
activation function, learning rate, epochs and layer size are all entered while the program runs.
Starting weights are random.

## Project files
| File | What is inside |
|---|---|
| `main.cpp` | The program flow: asks questions, trains, prints results, predicts |
| `Activation.h` | `IActivation`, all 7 activation classes, the activation list (menu + factory) |
| `Perceptron.h` | `ActivationPerceptron` – one neuron |
| `DataSet.h` | `DataPoint` and `DataSet` – training examples |
| `PerceptronTrainer.h` | `PerceptronTrainer` – trains one perceptron |
| `LayerNetwork.h` | `LayerNetwork` – layer of perceptrons + output perceptron (XOR stretch goal) |
| `Helpers.h` | Functions for reading input and counting correct answers |
| `README.md`, `CLASS_DIAGRAM.md` | Documentation |

All `.h` files are included by `main.cpp`, so you only compile `main.cpp`.

## How to run
```bash
g++ -std=c++17 main.cpp -o perceptron
./perceptron
```

## What you enter
1. Gate name (just a label) and number of inputs
2. Number of training examples, then each example: `input1 input2 ... target`
3. Model: **1** = single perceptron, **2** = layer of perceptrons
4. Activation function (and layer size if you chose the layer model)
5. Learning rate, epochs, max tries
6. Any new inputs you want to predict

### Activation functions
| # | Name | Output |
|---|---|---|
| 1 | Step | 1 if x >= 0, else 0 |
| 2 | Sigmoid | smooth 0 to 1 |
| 3 | Tanh | smooth -1 to 1 |
| 4 | ReLU | 0 if x < 0, else x |
| 5 | Leaky ReLU | like ReLU, small slope below 0 (you enter the leak) |
| 6 | Linear | x |
| 7 | Softplus | smooth version of ReLU |

### Example: AND gate with Step (one line of input)
```
AND 2 4  0 0 0  0 1 0  1 0 0  1 1 1  1 1  0.1 100 5 0
```
(gate, inputs, examples, 4 rows, model 1, activation 1, learning rate, epochs, tries, 0 predictions)

### Example: XOR with a layer of 2 perceptrons
Gate `XOR`, 2 inputs, 4 examples (`0 0 0`, `0 1 1`, `1 0 1`, `1 1 0`), model `2`,
layer size `2`, Sigmoid for the layer, Sigmoid for the output, learning rate `0.5`, epochs `5000`.

## Classes
| Class | Job (file) |
|---|---|
| `IActivation` | interface: `activate()` and `slope()` |
| `StepActivation`, `Sigmoid`, `Tanh`, `ReLU`, `LeakyReLU`, `Linear`, `Softplus` | the activation functions |
| `ActivationPerceptron` | one neuron: weights, bias, activation (`unique_ptr<IActivation>`) |
| `DataSet` / `DataPoint` | training examples (inputs + target) |
| `PerceptronTrainer` | `train(perceptron, dataSet, epochs)` |
| `LayerNetwork` | layer of perceptrons + 1 output perceptron (stretch goal) |

## How learning works
For every example: `error = target - prediction`, then
`weight = weight + learningRate * error * slope * input` (same for bias).
`slope` comes from the activation. Step uses slope = 1, which gives the classic perceptron rule.

## Design decisions
- **IActivation interface + activation list**: to add a new activation, write one small class and add one line to `activationList()`.
- **No hardcoded values**: data, settings and activation come from the user; the output threshold is worked out from the targets (halfway between smallest and largest target).
- **Random starting weights**: needed so layer neurons learn different things; with "max tries" the program restarts with new random weights if training fails.
- **Trainer separate from perceptron**: the perceptron predicts, the trainer teaches.
- **XOR needs a layer**: XOR cannot be split by one straight line, so a single perceptron can never learn it (the program tells you this if you try).

See `CLASS_DIAGRAM.md` for the diagram.

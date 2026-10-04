# Sample Runs

Real runs of the program. The lines after each prompt are what the user typed.
Weights start random, so decimal values (like `0.0282494`) change slightly from run to run,
but the rounded results stay the same.

## 1. AND gate – single perceptron with Step activation

```
MiniPerceptron 
Enter gate name (AND/OR/XOR/anything): AND
Number of inputs per example: 2
Number of training examples: 4

For each example enter 2 input(s) then the target.
Example for 2 inputs: 1 1 1

Example 1: 0 0 0
Example 2: 0 1 0
Example 3: 1 0 0
Example 4: 1 1 1

Model: 1. Single perceptron   2. Layer of perceptrons (for XOR)
Choose: 1

Choose activation function:
  1. Step
  2. Sigmoid
  3. Tanh
  4. ReLU
  5. Leaky ReLU
  6. Linear
  7. Softplus
Choose: 1

Learning rate: 0.1
Epochs: 100
Max tries (new random weights if it fails): 5

AND Gate - Trained Result
Activation: Step   Tries used: 1

Input  -> Output (rounded)
0 0 -> 0 (0)
0 1 -> 0 (0)
1 0 -> 0 (0)
1 1 -> 1 (1)

Correct: 4 / 4

How many new inputs do you want to predict? 1
Enter 2 input(s): 1 1
Output: 1  (rounded: 1)
```

## 2. XOR gate – single perceptron fails (not linearly separable)

A single perceptron can only draw one straight line, so it gets only 2 of 4 rows right
(the outputs stay near 0.5) and the program suggests the Layer model.

```
MiniPerceptron 
Enter gate name (AND/OR/XOR/anything): XOR
Number of inputs per example: 2
Number of training examples: 4

For each example enter 2 input(s) then the target.
Example for 2 inputs: 1 1 1

Example 1: 0 0 0
Example 2: 0 1 1
Example 3: 1 0 1
Example 4: 1 1 0

Model: 1. Single perceptron   2. Layer of perceptrons (for XOR)
Choose: 1

Choose activation function:
  1. Step
  2. Sigmoid
  3. Tanh
  4. ReLU
  5. Leaky ReLU
  6. Linear
  7. Softplus
Choose: 2

Learning rate: 0.5
Epochs: 2000
Max tries (new random weights if it fails): 3

XOR Gate - Trained Result
Activation: Sigmoid   Tries used: 3

Input  -> Output (rounded)
0 0 -> 0.516106 (1)
0 1 -> 0.5 (1)
1 0 -> 0.483894 (0)
1 1 -> 0.467821 (0)

Correct: 2 / 4
A single perceptron cannot learn this gate (not linearly separable). Try the Layer model.

How many new inputs do you want to predict? 0
```

## 3. XOR gate – layer of 2 perceptrons (stretch goal)

With a layer of 2 perceptrons (Sigmoid for the layer, Sigmoid for the output) XOR is learned.

```
MiniPerceptron 
Enter gate name (AND/OR/XOR/anything): XOR
Number of inputs per example: 2
Number of training examples: 4

For each example enter 2 input(s) then the target.
Example for 2 inputs: 1 1 1

Example 1: 0 0 0
Example 2: 0 1 1
Example 3: 1 0 1
Example 4: 1 1 0

Model: 1. Single perceptron   2. Layer of perceptrons (for XOR)
Choose: 2

Number of perceptrons in the layer: 2

Activation for the layer:
  1. Step
  2. Sigmoid
  3. Tanh
  4. ReLU
  5. Leaky ReLU
  6. Linear
  7. Softplus
Choose: 2

Activation for the output perceptron:
  1. Step
  2. Sigmoid
  3. Tanh
  4. ReLU
  5. Leaky ReLU
  6. Linear
  7. Softplus
Choose: 2

Learning rate: 0.5
Epochs: 5000
Max tries (new random weights if it fails): 10

XOR Gate - Trained Result
Layer activation: Sigmoid   Output activation: Sigmoid   Tries used: 1

Input  -> Output (rounded)
0 0 -> 0.0272737 (0)
0 1 -> 0.974144 (1)
1 0 -> 0.969241 (1)
1 1 -> 0.0241857 (0)

Correct: 4 / 4

How many new inputs do you want to predict? 2
Enter 2 input(s): 0 1
Output: 0.974144  (rounded: 1)
Enter 2 input(s): 1 1
Output: 0.0241857  (rounded: 0)
```

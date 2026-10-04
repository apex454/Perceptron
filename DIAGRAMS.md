# Project Diagrams

These diagrams explain how MiniPerceptron works. They render automatically on GitHub.
The class diagram is in `CLASS_DIAGRAM.md`.

## 1. Program flow (what happens when you run it)

```mermaid
flowchart TD
    A["Start"] --> B["Enter gate name, number of inputs, number of examples"]
    B --> C["Enter each example: inputs then target"]
    C --> D{"Choose model"}
    D -->|"1: Single perceptron"| E["Choose one activation function"]
    D -->|"2: Layer of perceptrons"| F["Enter layer size, choose layer activation and output activation"]
    E --> G["Enter learning rate, epochs, max tries"]
    F --> G
    G --> H["Reset to new random weights"]
    H --> I["Train for the given number of epochs"]
    I --> J{"All examples correct?"}
    J -->|"Yes"| L["Show trained truth table and accuracy"]
    J -->|"No"| K{"Tries left?"}
    K -->|"Yes"| H
    K -->|"No"| L
    L --> M{"Single perceptron and not all correct?"}
    M -->|"Yes"| N["Tell user: not linearly separable, try the Layer model"]
    M -->|"No"| O["Ask for new inputs to predict"]
    N --> O
    O --> P["Predict with the learned weights and print output"]
    P --> Q["End"]
```

## 2. How one perceptron learns (training loop)

```mermaid
flowchart TD
    A["Start epoch"] --> B["Take next example"]
    B --> C["Weighted sum = bias + input1 x weight1 + input2 x weight2 + ..."]
    C --> D["Activation function turns the sum into an output"]
    D --> E["error = target - output"]
    E --> F["change = error x slope of the activation"]
    F --> G["weight = weight + learning rate x change x input"]
    G --> H["bias = bias + learning rate x change"]
    H --> I{"More examples?"}
    I -->|"Yes"| B
    I -->|"No"| J{"More epochs?"}
    J -->|"Yes"| A
    J -->|"No"| K["Training finished, weights are now fixed"]
```

## 3. Layer network for XOR (forward and backward)

```mermaid
flowchart LR
    X1["Input x1"] --> H1["Hidden perceptron 1"]
    X2["Input x2"] --> H1
    X1 --> H2["Hidden perceptron 2"]
    X2 --> H2
    H1 --> O["Output perceptron"]
    H2 --> O
    O --> R["Result"]
    R -.->|"error = target - result"| O
    O -.->|"blame = output delta x output weight"| H1
    O -.->|"blame = output delta x output weight"| H2
```

Solid arrows are the forward pass (prediction). Dotted arrows show the error going back
to update the weights. XOR needs the hidden layer because one perceptron can only draw one
straight line, and XOR cannot be split by a single line.

## 4. How the files fit together

```mermaid
flowchart TD
    M["main.cpp"] --> H["Helpers.h"]
    M --> T["PerceptronTrainer.h"]
    M --> L["LayerNetwork.h"]
    M --> D["DataSet.h"]
    H --> A["Activation.h"]
    H --> D
    T --> P["Perceptron.h"]
    T --> D
    L --> P
    L --> D
    P --> A
```

## 5. Activation functions (Strategy pattern)

```mermaid
flowchart LR
    P["ActivationPerceptron"] -->|"uses"| I["IActivation: activate and slope"]
    I --> S1["Step"]
    I --> S2["Sigmoid"]
    I --> S3["Tanh"]
    I --> S4["ReLU"]
    I --> S5["Leaky ReLU"]
    I --> S6["Linear"]
    I --> S7["Softplus"]
    M["activationList menu and factory"] -.->|"creates the one the user picks"| I
```

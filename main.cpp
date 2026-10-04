#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <functional>

#include "Activation.h"
#include "Perceptron.h"
#include "DataSet.h"
#include "PerceptronTrainer.h"
#include "LayerNetwork.h"
#include "Helpers.h"
using namespace std;

int main() {
    srand((unsigned)time(nullptr));

    cout << "MiniPerceptron \n";

    string gateName;
    cout << "Enter gate name (AND/OR/XOR/anything): ";
    cin >> gateName;

    int inputCount = askInt("Number of inputs per example: ", 1);
    int sampleCount = askInt("Number of training examples: ", 1);

    cout << "\nFor each example enter " << inputCount << " input(s) then the target.\n";
    cout << "Example for 2 inputs: 1 1 1\n\n";

    vector<DataPoint> samples;
    for (int i = 0; i < sampleCount; i++) {
        DataPoint p;
        cout << "Example " << i + 1 << ": ";
        for (int j = 0; j < inputCount; j++) {
            double x;
            cin >> x;
            p.inputs.push_back(x);
        }
        cin >> p.target;
        samples.push_back(p);
    }
    DataSet dataSet(samples);

    cout << "\nModel: 1. Single perceptron   2. Layer of perceptrons (for XOR)\n";
    int model = askInt("Choose: ", 1);

    ActivationChoice hiddenAct{0, 0}, outAct{0, 0};
    int hiddenCount = 0;
    if (model == 1) {
        outAct = askActivation("Choose activation function:");
    } else {
        hiddenCount = askInt("\nNumber of perceptrons in the layer: ", 1);
        hiddenAct = askActivation("Activation for the layer:");
        outAct = askActivation("Activation for the output perceptron:");
    }

    double learningRate = askDouble("\nLearning rate: ");
    int epochs = askInt("Epochs: ", 1);
    int restarts = askInt("Max tries (new random weights if it fails): ", 1);

    ActivationPerceptron single(inputCount, makeActivation(outAct));
    LayerNetwork network(inputCount, model == 1 ? 1 : hiddenCount, hiddenAct, outAct);
    PerceptronTrainer trainer(learningRate);

    function<double(const vector<double>&)> predictFn;
    if (model == 1) predictFn = [&](const vector<double>& in) { return single.predict(in); };
    else            predictFn = [&](const vector<double>& in) { return network.predict(in); };

    int tries = 0;
    for (int t = 1; t <= restarts; t++) {
        tries = t;
        if (model == 1) { single.resetWeights();  trainer.train(single, dataSet, epochs); }
        else            { network.resetWeights(); network.train(dataSet, epochs, learningRate); }

        if (countCorrect(dataSet, predictFn) == (int)dataSet.size()) break;
    }

    int correct = countCorrect(dataSet, predictFn);
    double thr = dataSet.threshold();

    cout << "\n" << gateName << " Gate - Trained Result\n";
    if (model == 1)
        cout << "Activation: " << activationName(outAct);
    else
        cout << "Layer activation: " << activationName(hiddenAct)
             << "   Output activation: " << activationName(outAct);
    cout << "   Tries used: " << tries << "\n\n";
    cout << "Input  -> Output (rounded)\n";
    for (const DataPoint& p : dataSet.getData()) {
        for (double x : p.inputs) cout << x << " ";
        double r = predictFn(p.inputs);
        cout << "-> " << r << " (" << (r >= thr ? 1 : 0) << ")\n";
    }
    cout << "\nCorrect: " << correct << " / " << dataSet.size() << "\n";
    if (correct != (int)dataSet.size() && model == 1)
        cout << "A single perceptron cannot learn this gate (not linearly separable). "
                "Try the Layer model.\n";

    int predictions = askInt("\nHow many new inputs do you want to predict? ", 0);
    for (int k = 0; k < predictions; k++) {
        vector<double> in;
        cout << "Enter " << inputCount << " input(s): ";
        for (int j = 0; j < inputCount; j++) {
            double x;
            cin >> x;
            in.push_back(x);
        }
        double r = predictFn(in);
        cout << "Output: " << r << "  (rounded: " << (r >= thr ? 1 : 0) << ")\n";
    }
    return 0;
}

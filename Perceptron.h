#pragma once
#include <cstdlib>
#include <memory>
#include <vector>
#include "Activation.h"
using namespace std;

inline double randomWeight() {
    return (rand() / (double)RAND_MAX) * 2.0 - 1.0;
}

class ActivationPerceptron {
private:
    vector<double> weights;
    double bias;
    unique_ptr<IActivation> act;

public:
    ActivationPerceptron(int inputSize, unique_ptr<IActivation> activation)
        : weights(inputSize), bias(0.0), act(std::move(activation)) {
        resetWeights();
    }

    void resetWeights() {
        for (size_t i = 0; i < weights.size(); i++) weights[i] = randomWeight();
        bias = randomWeight();
    }

    double predict(const vector<double>& inputs) const {
        double sum = bias;
        for (size_t i = 0; i < inputs.size(); i++)
            sum += inputs[i] * weights[i];
        return act->activate(sum);
    }

    void updateWeights(const vector<double>& inputs, double error, double learningRate) {
        double change = error * act->slope(predict(inputs));
        for (size_t i = 0; i < weights.size(); i++)
            weights[i] += learningRate * change * inputs[i];
        bias += learningRate * change;
    }

    double slopeOf(double output) { return act->slope(output); }
    double getWeight(int i) const { return weights[i]; }
};

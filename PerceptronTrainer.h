#pragma once
#include "DataSet.h"
#include "Perceptron.h"

class PerceptronTrainer {
private:
    double learningRate;
public:
    PerceptronTrainer(double lr) : learningRate(lr) {}

    void train(ActivationPerceptron& perceptron, const DataSet& dataSet, int epochs) {
        for (int epoch = 0; epoch < epochs; epoch++) {
            for (const DataPoint& point : dataSet.getData()) {
                double prediction = perceptron.predict(point.inputs);
                double error = point.target - prediction;
                perceptron.updateWeights(point.inputs, error, learningRate);
            }
        }
    }
};

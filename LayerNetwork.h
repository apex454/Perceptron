#pragma once
#include <vector>
#include "Activation.h"
#include "DataSet.h"
#include "Perceptron.h"
using namespace std;

class LayerNetwork {
private:
    vector<ActivationPerceptron> layer;
    ActivationPerceptron output;

public:
    LayerNetwork(int inputSize, int hiddenCount,
                 const ActivationChoice& hiddenAct, const ActivationChoice& outAct)
        : output(hiddenCount, makeActivation(outAct)) {
        for (int i = 0; i < hiddenCount; i++)
            layer.push_back(ActivationPerceptron(inputSize, makeActivation(hiddenAct)));
    }

    void resetWeights() {
        for (size_t i = 0; i < layer.size(); i++) layer[i].resetWeights();
        output.resetWeights();
    }

    vector<double> hiddenOutputs(const vector<double>& in) const {
        vector<double> h;
        for (size_t i = 0; i < layer.size(); i++) h.push_back(layer[i].predict(in));
        return h;
    }

    double predict(const vector<double>& in) const {
        return output.predict(hiddenOutputs(in));
    }

    void train(const DataSet& dataSet, int epochs, double lr) {
        for (int e = 0; e < epochs; e++) {
            for (const DataPoint& p : dataSet.getData()) {
                vector<double> h = hiddenOutputs(p.inputs);
                double out = output.predict(h);

                double outDelta = (p.target - out) * output.slopeOf(out);
                vector<double> blame;
                for (size_t j = 0; j < layer.size(); j++)
                    blame.push_back(outDelta * output.getWeight(j));

                output.updateWeights(h, p.target - out, lr);
                for (size_t j = 0; j < layer.size(); j++)
                    layer[j].updateWeights(p.inputs, blame[j], lr);
            }
        }
    }
};

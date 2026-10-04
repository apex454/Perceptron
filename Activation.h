#pragma once
#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class IActivation {
public:
    virtual double activate(double x) = 0;
    virtual double slope(double output) = 0;
    virtual ~IActivation() = default;
};

class StepActivation : public IActivation {
public:
    double activate(double x) override { return x >= 0 ? 1 : 0; }
    double slope(double) override { return 1; }
};

class Sigmoid : public IActivation {
public:
    double activate(double x) override { return 1.0 / (1.0 + exp(-x)); }
    double slope(double out) override { return out * (1.0 - out); }
};

class Tanh : public IActivation {
public:
    double activate(double x) override { return tanh(x); }
    double slope(double out) override { return 1.0 - out * out; }
};

class ReLU : public IActivation {
public:
    double activate(double x) override { return x > 0 ? x : 0; }
    double slope(double out) override { return out > 0 ? 1 : 0; }
};

class LeakyReLU : public IActivation {
private:
    double leak;
public:
    LeakyReLU(double leak) : leak(leak) {}
    double activate(double x) override { return x > 0 ? x : leak * x; }
    double slope(double out) override { return out > 0 ? 1 : leak; }
};

class Linear : public IActivation {
public:
    double activate(double x) override { return x; }
    double slope(double) override { return 1; }
};

class Softplus : public IActivation {
public:
    double activate(double x) override { return log(1.0 + exp(x)); }
    double slope(double out) override { return 1.0 - exp(-out); }
};

struct ActivationInfo {
    string name;
    bool needsParam;
    string paramPrompt;
    function<unique_ptr<IActivation>(double)> make;
};

inline vector<ActivationInfo> activationList() {
    return {
        {"Step",       false, "", [](double)   { return unique_ptr<IActivation>(new StepActivation()); }},
        {"Sigmoid",    false, "", [](double)   { return unique_ptr<IActivation>(new Sigmoid()); }},
        {"Tanh",       false, "", [](double)   { return unique_ptr<IActivation>(new Tanh()); }},
        {"ReLU",       false, "", [](double)   { return unique_ptr<IActivation>(new ReLU()); }},
        {"Leaky ReLU", true,  "Enter leak value (e.g. small positive number): ",
                                   [](double p) { return unique_ptr<IActivation>(new LeakyReLU(p)); }},
        {"Linear",     false, "", [](double)   { return unique_ptr<IActivation>(new Linear()); }},
        {"Softplus",   false, "", [](double)   { return unique_ptr<IActivation>(new Softplus()); }},
    };
}

struct ActivationChoice {
    int index;
    double param;
};

inline unique_ptr<IActivation> makeActivation(const ActivationChoice& c) {
    return activationList()[c.index].make(c.param);
}

inline string activationName(const ActivationChoice& c) {
    return activationList()[c.index].name;
}

#pragma once
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "Activation.h"
#include "DataSet.h"
using namespace std;

inline ActivationChoice askActivation(const string& title) {
    vector<ActivationInfo> list = activationList();
    cout << "\n" << title << "\n";
    for (size_t i = 0; i < list.size(); i++)
        cout << "  " << i + 1 << ". " << list[i].name << "\n";

    int pick = 0;
    while (pick < 1 || pick > (int)list.size()) {
        cout << "Choose: ";
        if (!(cin >> pick)) {
            if (cin.eof()) exit(1);
            cin.clear(); cin.ignore(10000, '\n'); pick = 0;
        }
    }
    ActivationChoice c{pick - 1, 0};
    if (list[c.index].needsParam) {
        cout << list[c.index].paramPrompt;
        cin >> c.param;
    }
    return c;
}

inline int askInt(const string& text, int minimum) {
    int v = minimum - 1;
    while (v < minimum) {
        cout << text;
        if (!(cin >> v)) {
            if (cin.eof()) exit(1);
            cin.clear(); cin.ignore(10000, '\n'); v = minimum - 1;
        }
    }
    return v;
}

inline double askDouble(const string& text) {
    double v;
    while (true) {
        cout << text;
        if (cin >> v) return v;
        if (cin.eof()) exit(1);
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

inline int countCorrect(const DataSet& d, const function<double(const vector<double>&)>& predict) {
    double t = d.threshold();
    int correct = 0;
    for (const DataPoint& p : d.getData())
        if ((predict(p.inputs) >= t) == (p.target >= t)) correct++;
    return correct;
}

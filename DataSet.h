#pragma once
#include <vector>
using namespace std;

struct DataPoint {
    vector<double> inputs;
    double target;
};

class DataSet {
private:
    vector<DataPoint> data;
public:
    DataSet(const vector<DataPoint>& samples) : data(samples) {}
    const vector<DataPoint>& getData() const { return data; }
    size_t size() const { return data.size(); }

    double threshold() const {
        double lo = data[0].target, hi = data[0].target;
        for (const DataPoint& p : data) {
            if (p.target < lo) lo = p.target;
            if (p.target > hi) hi = p.target;
        }
        return (lo + hi) / 2.0;
    }
};

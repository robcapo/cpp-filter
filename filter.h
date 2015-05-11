#ifndef FILTER_H
#define FILTER_H

#include <vector>

using namespace std;

class Filter 
{
private:
    vector<double> b;
    vector<double> a;

public:
    Filter();
    /**
     * Create a Filter with only b coefficients
     */
    Filter(vector<double> b);

    /**
     * Create a Filter with b and a coefficients
     */
    Filter(vector<double> b, vector<double> a);

    /**
     * Filter a signal
     */
    vector<double> filter(const vector<double> &input) const;
};

#endif

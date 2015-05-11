#include <cmath>
#include <vector>
#include "filter.h"

using namespace std;

Filter::Filter()
{
    
}

Filter::Filter(vector<double> b)
{
    this->b = b;
}

Filter::Filter(vector<double> b, vector<double> a)
{
    this->b = b;
    this->a = a;
}

vector<double> Filter::filter(const vector<double> &input) const
{
    vector<double> output;
    for (int i = 0; i < input.size() + this->b.size(); i++) {
        double out = 0.0;

        for (int j = 0; j < this->b.size(); j++) {
            if (i - j >= 0) {
                out += input[i-j] * this->b[j];
            }
        }

        output.push_back(out);
    }

    return output;
}

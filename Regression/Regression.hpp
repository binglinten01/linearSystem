#ifndef REGRESSION_HPP
#define REGRESSION_HPP

#include <string>
#include "../Vector/Vector.hpp"

struct RegressionResult {
    Vector parameters;
    double rmse;

    RegressionResult(int parameterCount);
};

RegressionResult runCpuRegression(const std::string& filename, double lambda = 1e-8);

#endif

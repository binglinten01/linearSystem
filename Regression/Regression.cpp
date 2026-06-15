#include "Regression.hpp"
#include "../Matrix/Matrix.hpp"
#include "../LinearSystem/SolverHelpers.hpp"
#include <cassert>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct CpuRecord {
    double x[6];
    double y;
};

RegressionResult::RegressionResult(int parameterCount)
    : parameters(parameterCount), rmse(0.0) {}

static bool parseCpuLine(const std::string& line, CpuRecord& record) {
    std::stringstream ss(line);
    std::string fields[10];

    for (int i = 0; i < 10; i++) {
        if (!std::getline(ss, fields[i], ',')) {
            return false;
        }
    }

    record.x[0] = std::stod(fields[2]);
    record.x[1] = std::stod(fields[3]);
    record.x[2] = std::stod(fields[4]);
    record.x[3] = std::stod(fields[5]);
    record.x[4] = std::stod(fields[6]);
    record.x[5] = std::stod(fields[7]);
    record.y = std::stod(fields[8]);

    return true;
}

RegressionResult runCpuRegression(const std::string& filename, double lambda) {
    std::ifstream input(filename);
    assert(input.is_open());

    std::vector<CpuRecord> records;
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        CpuRecord record;

        if (parseCpuLine(line, record)) {
            records.push_back(record);
        }
    }

    assert(records.size() >= 2);

    int totalCount = static_cast<int>(records.size());
    int trainingCount = static_cast<int>(totalCount * 0.8);
    int testingCount = totalCount - trainingCount;

    assert(trainingCount > 0);
    assert(testingCount > 0);

    Matrix X(trainingCount, 6);
    Vector y(trainingCount);

    for (int i = 1; i <= trainingCount; i++) {
        for (int j = 1; j <= 6; j++) {
            X(i, j) = records[i - 1].x[j - 1];
        }

        y(i) = records[i - 1].y;
    }

    Vector parameters = solveByTikhonov(X, y, lambda);

    double squaredErrorSum = 0.0;

    for (int i = trainingCount; i < totalCount; i++) {
        double prediction = 0.0;

        for (int j = 0; j < 6; j++) {
            prediction += parameters(j + 1) * records[i].x[j];
        }

        double error = prediction - records[i].y;
        squaredErrorSum += error * error;
    }

    RegressionResult result(6);
    result.parameters = parameters;
    result.rmse = std::sqrt(squaredErrorSum / testingCount);

    return result;
}

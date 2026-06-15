#include "Regression.hpp"
#include "../Matrix/Matrix.hpp"
#include "../Vector/Vector.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

const int MAX_ROWS = 300;
const int NUM_FEATURES = 6;

bool readMachineData(const char* fileName, float features[MAX_ROWS][NUM_FEATURES], float targets[MAX_ROWS], int& numberOfRows) {
    std::ifstream input(fileName);

    if (!input.is_open()) {
        return false;
    }

    numberOfRows = 0;
    std::string line;

    while (std::getline(input, line) && numberOfRows < MAX_ROWS) {
        std::stringstream lineStream(line);
        std::string item;
        std::string fields[10];
        int fieldIndex = 0;

        while (std::getline(lineStream, item, ',') && fieldIndex < 10) {
            fields[fieldIndex] = item;
            fieldIndex++;
        }

        if (fieldIndex == 10) {
            features[numberOfRows][0] = std::stof(fields[2]);
            features[numberOfRows][1] = std::stof(fields[3]);
            features[numberOfRows][2] = std::stof(fields[4]);
            features[numberOfRows][3] = std::stof(fields[5]);
            features[numberOfRows][4] = std::stof(fields[6]);
            features[numberOfRows][5] = std::stof(fields[7]);
            targets[numberOfRows] = std::stof(fields[8]);

            numberOfRows++;
        }
    }

    input.close();
    return true;
}

Vector trainRegression(float features[MAX_ROWS][NUM_FEATURES], float targets[MAX_ROWS], int trainRows) {
    Matrix X(trainRows, NUM_FEATURES);
    Vector y(trainRows);

    for (int i = 1; i <= trainRows; i++) {
        for (int j = 1; j <= NUM_FEATURES; j++) {
            X(i, j) = features[i - 1][j - 1];
        }

        y(i) = targets[i - 1];
    }

    Matrix XInverse = X.pseudoInverse();
    Vector parameters = XInverse * y;

    return parameters;
}

float predict(const Vector& parameters, float row[NUM_FEATURES]) {
    float prediction = 0.0f;

    for (int i = 1; i <= NUM_FEATURES; i++) {
        prediction += parameters(i) * row[i - 1];
    }

    return prediction;
}

float computeRMSE(const Vector& parameters, float features[MAX_ROWS][NUM_FEATURES], float targets[MAX_ROWS], int startRow, int endRow) {
    float errorSum = 0.0f;
    int count = 0;

    for (int i = startRow; i < endRow; i++) {
        float predicted = predict(parameters, features[i]);
        float error = predicted - targets[i];
        errorSum += error * error;
        count++;
    }

    return std::sqrt(errorSum / count);
}

void runRegression(const char* fileName) {
    float features[MAX_ROWS][NUM_FEATURES];
    float targets[MAX_ROWS];
    int numberOfRows = 0;

    bool fileLoaded = readMachineData(fileName, features, targets, numberOfRows);

    if (!fileLoaded) {
        std::cout << "Regression data file was not found." << std::endl;
        std::cout << "Download machine.data from the UCI Computer Hardware dataset." << std::endl;
        std::cout << "Then put it in this folder and run: ./main machine.data" << std::endl;
        return;
    }

    int trainRows = numberOfRows * 80 / 100;
    int testRows = numberOfRows - trainRows;

    Vector parameters = trainRegression(features, targets, trainRows);
    float trainRMSE = computeRMSE(parameters, features, targets, 0, trainRows);
    float testRMSE = computeRMSE(parameters, features, targets, trainRows, numberOfRows);

    std::cout << "Linear regression test" << std::endl;
    std::cout << "Rows: " << numberOfRows << std::endl;
    std::cout << "Training rows: " << trainRows << std::endl;
    std::cout << "Testing rows: " << testRows << std::endl;

    std::cout << "Parameters:" << std::endl;
    parameters.print();

    std::cout << "Training RMSE: " << trainRMSE << std::endl;
    std::cout << "Testing RMSE: " << testRMSE << std::endl;
}

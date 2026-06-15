# Linear System Project

This is a complete C++ implementation of Project 1.

## Build and run

```bash
make build
./main path/to/machine.data
make run
```

## Dependencies
- UCI Computer Hardware dataset file `machine.data`
- CPP compiler

## Structure

- `Vector/`: dynamic vector class
- `Matrix/`: dynamic matrix class
- `LinearSystem/`: Gaussian elimination, conjugate gradient, pseudo-inverse/Tikhonov helpers
- `Regression/`: linear regression using the CPU performance dataset

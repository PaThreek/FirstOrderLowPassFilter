# FirstOrderLowPassFilter
This application demonstrates the usage of threads for computing the mathematical formula for First Order Low Pass Filter.

A first-order low-pass filter is described by the following mathematical formula:

y(k) = α*x(k) + (1 - α)*y(k-1)

where:

    y(k) is the output signal at time k
    x(k) is the input signal at time k
    y(k-1) is the output signal at the previous time step
    α is the filter coefficient, which determines the amount of smoothing applied to the signal.

The behaviour of the apllication is the following:
* there are two types of threads for computation of the formula - for multiplication and addition
* multiplication thread will compute α*x(k) and (1 - α)*y(k-1) from the formula
* addition thread will add together results from multiplication threads so we get the result for the whole formula y(k) = α*x(k) + (1 - α)*y(k-1) 
* α = -1
* k = 0, .., 39
* x(k) = 1
* y(-1) = 0

The result for all y(k) is at the end written to the file in human-readable format.

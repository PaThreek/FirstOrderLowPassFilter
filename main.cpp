#include <iostream>
#include <fstream>
#include <functional>
#include <thread>
#include <vector>
;

constexpr double LAMBDA = 0.1;
constexpr double INPUT_SIGNAL_VALUE = 1;
constexpr int REPETITIONS = 40;

int main(int argc, char** argv)
{
    auto multiplication = [](double a, double b, double& result) -> void {
        result = a * b;
        std::cout << a << " * " << b << " = " << result << std::endl;
    };

    auto addition = [](std::thread& multiplicationThreadA, std::thread& multiplicationThreadB, double& a, double& b, double& result) -> void {
        multiplicationThreadA.join();
        multiplicationThreadB.join();
        result = a + b;
        std::cout << a << " + " << b << " = " << result << std::endl;
    };

    // Input signal values
    std::vector<double> x;
    x.resize(REPETITIONS, INPUT_SIGNAL_VALUE);
    
    // Output signal values
    std::vector<double> y;
    y.resize(REPETITIONS, 0);

    for(size_t k = 0; k < REPETITIONS; ++k) {
        double a = 0;
        double b = 0;
        std::thread multiplicationThreadA(multiplication, LAMBDA, x[k], std::ref(a));
        std::thread multiplicationThreadB(multiplication, 1 - LAMBDA, k > 0 ? y[k-1] : 0, std::ref(b));

        double additionResult = 0;
        std::thread additionThread(addition, std::ref(multiplicationThreadA), std::ref(multiplicationThreadB), std::ref(a), std::ref(b), std::ref(additionResult));
        additionThread.join();

        y[k] = additionResult;
    }

    std::ofstream resultFile("result.txt");
    if (resultFile.is_open()) {
        for (int k = 0; k < REPETITIONS; ++k) {
            resultFile << "y[" << k << "] = " << y[k] << std::endl;
        }
        resultFile.close();
    }

    return 0;
}
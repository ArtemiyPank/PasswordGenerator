#ifndef LINEARFUNCTION_H
#define LINEARFUNCTION_H


// f(x) = kx + h
class LinearFunction {
public:
    double k, h;    // function parameters

    // Constructor taking raw parameter values and mapping them into valid ranges
    LinearFunction(double P_k, double P_h);

    // Print current parameter values
    void printLinearParameters() const;

    // Value of the function in x
    [[nodiscard]] double func(double x) const;

    // Value of the function at the intersection with the Y axis
    [[nodiscard]] double intersectionWithAxis_X() const;

    // Function argument at the intersection with the X axis
    [[nodiscard]] double intersectionWithAxis_Y() const;
};

#endif //LINEARFUNCTION_H

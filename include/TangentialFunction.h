#ifndef TANGENTIALFUNCTION_H
#define TANGENTIALFUNCTION_H


// function f(x) = g * ((c * tan(a * x + b) + d) / f)
class TangentialFunction {
public:
    double a, b, c, d, f, g;      // function parameters

    // Constructor taking raw parameter values and mapping them into valid ranges
    TangentialFunction(double P_a, double P_b, double P_c, double P_d, double P_f, double P_g);

    // Print current parameter values
    void printTangentialParameters() const;

    // Value of the function in x
    [[nodiscard]] double func(double x) const;

    // Compute the x-value of the nth vertical asymptote
    [[nodiscard]] double GetAsymptoteByNumber(int n) const;
};

#endif // TANGENTIALFUNCTION_H

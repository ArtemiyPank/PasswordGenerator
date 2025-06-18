//
// Created by artemiypank on 6/8/25.
//

#ifndef LINEARFUNCTION_H
#define LINEARFUNCTION_H



class LinearFunction {
public:
    double k, h;


    LinearFunction(double P_k, double P_h);

    [[nodiscard]] double func(double x) const;

    [[nodiscard]] double intersectionWithAxis_X() const;
    [[nodiscard]] double intersectionWithAxis_Y() const;

};



#endif //LINEARFUNCTION_H

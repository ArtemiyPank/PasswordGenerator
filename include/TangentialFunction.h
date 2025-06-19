    //
    // Created by artemiypank on 6/8/25.
    //

    #ifndef TANGENTIALFUNCTION_H
    #define TANGENTIALFUNCTION_H




    class TangentialFunction {
    public:
        double a, b, c, d, f, g;

        TangentialFunction(double P_a, double P_b, double P_c, double P_d, double P_f, double P_g);

        void printTangentialParameters() const;

        [[nodiscard]] double func(double x) const;

        [[nodiscard]] double GetAsymptoteByNumber(int n) const;


    };


    #endif //TANGENTIALFUNCTION_H

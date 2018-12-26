//
// Created by adell.j on 18.12.2018.
//

#ifndef TKOM_FRACTION_H
#define TKOM_FRACTION_H


#include <string>

class Fraction {
public:
    Fraction();
    Fraction(int nominator, int denominator);
    Fraction(std::string value);
    ~Fraction();
    void setNominator(int nominator);
    void setDenominator(int denominator);
    int getNominator() const;
    int getDenominator() const;

private:
    int nominator;
    int denominator;
    int NWW();
    int NWD();
};


#endif //TKOM_FRACTION_H

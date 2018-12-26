//
// Created by adell.j on 18.12.2018.
//

#include "Fraction.h"

Fraction::Fraction(int nomin, int denomin) {
    nominator = nomin;
    denominator = denomin;
}

Fraction::Fraction(std::string value){
    int split = value.find("%");
    if(split == -1) {
        setNominator(stoi(value));
        setDenominator(1);
    }
    else {
        setNominator(stoi(value.substr(0, split)));
        setDenominator(stoi(value.substr(split + 1, value.length() - split + 1)));
    }
}

int Fraction::getNominator() const {
    return nominator;
}

int Fraction::getDenominator() const {
    return denominator;
}

void Fraction::setNominator(int nominator) {
    Fraction::nominator = nominator;
}

void Fraction::setDenominator(int denominator) {
    Fraction::denominator = denominator;
}

Fraction operator+ (Fraction first, Fraction second) {
    int newNominator;
    int newDenominator;
    //return Fraction();
}

Fraction operator- (Fraction first, Fraction second) {
    int newNominator;
    int newDenominator;
    //return Fraction();
}

Fraction operator* (Fraction first, Fraction second) {
    int newNominator;
    int newDenominator;
    //return Fraction(first.getNominator()* second.getNominator(), first.getDenominator() * second.getDenominator());
}

Fraction operator/ (Fraction first, Fraction second) {
    int newNominator;
    int newDenominator;
    //return Fraction();
}

int Fraction::NWW(){

}

int Fraction::NWD(){

}


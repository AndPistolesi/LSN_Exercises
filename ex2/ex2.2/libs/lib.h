#ifndef __lib__
#define __lib__


#include <iostream>
#include <cmath>
#include <vector>
#include "random.h"

using namespace std;



struct Data {

	vector<double> v;
	vector<double> x;
	vector<double> err;
};

	double const_1(double x);
	double Id (double x);
	Data Cum_av(vector<double> v, double(*g)(double) = const_1, double(*f)(double) = Id);




class RW_1D{
    public:
        RW_1D(double a0){x = 0; a = a0; Inizialize(rnd);}
        void Passo_m(); //Random walk step
        double Measure();
        void Reset(){x = 0;}


    private:
        double x; //posizione
        double a; //incremento
        Random rnd;

};

class RW_3D{
    public:
        RW_3D(double a0){x = vector<double> (3); a = a0; Inizialize(rnd);}
        void Passo_m();
        double Measure();
        void Reset(){x[0] = 0; x[1] = 0; x[2] = 0;}

    private:
        vector<double> x; //posizione
        double a; //incremento
        Random rnd;

};


#endif 
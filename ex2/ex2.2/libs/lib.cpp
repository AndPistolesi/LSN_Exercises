
#include "lib.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>


double const_1(double x) {return 1;}
double Id (double x){return x;}
double Inv(double x){return 1./(2*x);}

Data Cum_av(vector<double> x, double(*g)(double) /*=const_1*/, double(*f)(double) /*=Id*/){
	vector<double> v(x.size());
	vector<double> v2(x.size());
	vector<double> err(x.size());
	Data b;
	for (int i=0; i<x.size(); i++){
		for (int j=0; j<i+1; j++){
			v[i] += x[j]/(i+1);
			v2[i] += x[j]*x[j]/(i+1);
			}
		//propagazione errori
		err[i] = g(v[i])*(sqrt((v2[i] - v[i]*v[i])/(i+1)));
		v[i] = f(v[i]);

		//cout << v[i] << endl;

		}
	
	b.v = x;
	b.x = v;
	b.err = err;
	return b;
}


void RW_1D::Passo_m(){
    if (rnd.Rannyu() >= 0.5)
        x += a;
    else x -=a ;
}
double RW_1D::Measure(){
    return x*x;
}

void RW_3D::Passo_m(){
    double f = rnd.Rannyu(0, 2*M_PI);
    double t = -acos(rnd.Rannyu(-1, 1)); //campiono sin(t)dt
    x[0] += a*cos(f)*sin(t);
    x[1] += a*sin(f)*sin(t);
    x[2] += a*cos(t);
}
double RW_3D::Measure(){
    return x[0]*x[0] + x[1]*x[1] + x[2]*x[2];
}
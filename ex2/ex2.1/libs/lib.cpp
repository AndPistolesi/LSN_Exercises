
#include "lib.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>


double const_1(double x) {return 1;}
double Id (double x){return x;}

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
		
		err[i] = g(v[i])*(sqrt((v2[i] - v[i]*v[i])/(i+1)));
		v[i] = f(v[i]);

		//cout << v[i] << endl;

		}
	b.x = v;
	b.err = err;
	return b;
}


void Print_Data(vector<Data> b, ofstream& out){

	for (int j=0; j<b[0].x.size(); j++){
		out << j << " "; 
		for (int i=0; i<b.size(); i++)
			out << b[i].x[j] << " " << b[i].err[j] << " ";
		out << endl;
	}
}

vector<double> IS (double (*f)(double), double (*Cum_IS)(double), Random &rnd, int L, int N) {
	double sum = 0;
	vector<double> z;
	for (int j=0; j<N; j++){
		sum = 0;
		for (int i=0; i<L; i++)
			sum += f(Cum_IS(rnd.Rannyu()));
		
		z.push_back(sum/L);
		}
	return z;
}


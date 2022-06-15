
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
		//Propagation of errors
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




Distr::Distr(double (*Cum_INV)(double), Random &rnd, int N){
	vector<double> v(N);
	double s;
	for (int i=0; i<N; i++){
		s = rnd.Rannyu();
		v[i] = (Cum_INV(s));	
		
	}
	x = v;

}
Distr::Distr(double (*p)(double), Random &rnd, double min_x, double max_x, double max, int N){
	vector<double> v(N);
	double z, y;
	int c=0; 
	for (int i=0; c<=N; i++){
		y = rnd.Rannyu(min_x, max_x);
		z = rnd.Rannyu(0, max);
		if (p(y) >= z){
			v[c] = y;
			c++;
			}
	}
	x = v;
}


double Distr::Av(){
	double sum = 0;
	for (int i=0; i<x.size(); i++)
		sum += x[i];
	return sum/x.size();
}

double Distr::Dev_st(){
	double sum2 = 0;
	for (int i=0; i<x.size(); i++)
		sum2 += x[i]*x[i];
	
	return sqrt(sum2/x.size() - Av()*Av());
}




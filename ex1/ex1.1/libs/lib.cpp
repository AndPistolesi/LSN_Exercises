
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

//Print one vector in a file

void Print_vect_1(vector<double> b, ofstream& out){
	for (int j=0; j<b.size(); j++){
		out << j << " "; 
		out << b[j] << " ";
		out << endl;
	}
}

//Pirnt a vector of Data in a file

void Print_Data(vector<Data> b, ofstream& out){

	for (int j=0; j<b[0].x.size(); j++){
		out << j << " "; 
		for (int i=0; i<b.size(); i++)
			out << b[i].x[j] << " " << b[i].err[j] << " ";
		out << endl;
	}
}


vector<double> INT (double (*f)(double), Random &rnd, int L, int N) {
	double sum = 0;
	vector<double> z{};
	for (int j=0; j<N; j++){
		sum = 0;
		for (int i=0; i<L; i++)
			sum += f(rnd.Rannyu());
		
		z.push_back(sum/L);
		}
	return z;
}



vector<vector<double>> Ivs (Random &rnd, int M, int N, int n){
	vector<vector<double>> v(N, vector<double> (M));
	double y;
	for (int i=0; i < N; i++){
		for (int j=0; j<n; j++){
			y = rnd.Rannyu();
			v[i][(int)(y*M)] ++;
		}
	}
	
	return v;
}

double Chi_2(vector<double> x, vector<double> m){
	double chi = 0;
	for (int i=0; i<x.size(); i++)
			chi += pow(x[i] - m[i],2)/m[i];
	return chi;

}






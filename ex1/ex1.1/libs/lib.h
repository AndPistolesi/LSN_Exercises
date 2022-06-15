#ifndef __lib__
#define __lib__


#include <iostream>
#include <cmath>
#include <vector>
#include "random.h"

using namespace std;

struct Data {

	vector<double> x;
	vector<double> err;
};

	double const_1(double x);
	double Id (double x);
	Data Cum_av(vector<double> v, double(*g)(double) = const_1, double(*f)(double) = Id);
	
	void Print_vect_1(vector<double> b, ofstream& out);
	void Print_Data(vector<Data> b, ofstream &);
	
double Chi_2(vector<double> v, vector<double> m);
vector<double> INT (double (*f)(double), Random &rnd, int L, int N);
vector<vector<double>> Ivs (Random &, int L, int N, int n);

#endif // __lib__
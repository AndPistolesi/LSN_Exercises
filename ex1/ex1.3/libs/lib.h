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
	

	void Print_Data(vector<Data> b, ofstream &);
	
vector<double> Bar (double D, double l, Random &rnd, int L, int N);


#endif // __lib__
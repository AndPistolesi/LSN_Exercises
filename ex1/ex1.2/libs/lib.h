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
	

class Distr{
	public:
		Distr(){x = vector<double> ();};
		//Vector creation
		Distr(double (*Cum_INV)(double), Random &rnd, int N);
		Distr(double (*p)(double), Random &rnd, double min_x, double max_x, double max, int N);
		
		//Average and Standard deviaion
		double Av();
		double Dev_st();	
		
		vector<double> Get_x() {return x;};
		void Set_x(vector<double> v) {x = v;};
		vector<double> Get_err() {return err;};
		
	protected:
	vector<double> x;
	vector<double> err;

};


#endif // __lib__
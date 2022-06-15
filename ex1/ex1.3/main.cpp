#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

double l = 3;
double d = 30;

//Functions for propagation of errors
double f(double x){return 2*l/(x*x*d);}
double g(double x){return 2*l/(d*x);}

int main(){
	
	Random rnd;
	ofstream mid;
	Inizialize(rnd);
	int N = 100;
	int L = 100;
	vector<Data> b (1);
	vector<double> v;

	v = Bar(d, l, rnd, L, N);
	b[0] = Cum_av(v, f, g);
	
	mid.open("mid.dat");
	Print_Data(b, mid);
		
	return 0;
	}

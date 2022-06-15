#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include <cmath>
#include <fstream>
#include <vector>


using namespace std;

double f (double x){	

	return M_PI/2*cos(M_PI/2*x);
	}

double p (double x) {

	return 1 - sqrt(1-x);
	}

//f/p
double f1 (double x){
	return f(x)/(2*(1-x));
}


int main(){

	Random rnd;
	Inizialize (rnd);
	ofstream out;
	out.open("out.dat");

	vector<double> v, v1;
	vector<Data> b(2);
	
	//standard integral
	v = IS (f, Id, rnd, 100, 100);
	//important sampling
	v1 = IS (f1, p, rnd, 100, 100);
	
	b[0] = Cum_av(v);
	b[1] = Cum_av(v1);
	
	Print_Data(b, out);
	return 0;
}

#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

double f(double x){return x;}
double g(double x){return (x-0.5)*(x-0.5);}


int main(){
	
	Random rnd;
	ofstream itg, itv;
	Inizialize(rnd);
	int M_integral=50000; //total number of steps for integrals
	int N_integral=100; //number of blocks for integrals
	int L_integral=M_integral/N_integral;

	int n_int = 10000;
	int M_int = 100;
	int N_int = 100;

	vector<Data> b (2);
	vector<double> x1, x2, Chi;
	vector<vector<double>> Iv(N_int, vector<double> (M_int));
	vector<double> m(100, 100);
	
	//computing integrals
	x1 = INT(f, rnd, L_integral, N_integral);
	x2 = INT(g, rnd, L_integral, N_integral);

	//Throwing in the intervals 
	Iv = Ivs(rnd, M_int , N_int, n_int);

	//computing Chi^2 for every set of throws
	for (int i=0; i<N_int; i++)
		Chi.push_back(Chi_2(Iv[i], m));

	//Printing

	b[0] = Cum_av(x1);
	b[1] = Cum_av(x2);

	itg.open("Integral.dat");
	itv.open("Interval.dat");
	
	Print_Data(b, itg);
	Print_vect_1(Chi, itv);

	itg.close();
	itv.close();
	
	
	return 0;
	}

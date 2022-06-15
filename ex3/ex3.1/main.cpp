#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include "libs/libd.h"
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

vector<double> Count_Int(Random,int, int);


int main(){
	
	Random rnd;
	Inizialize(rnd);
	ofstream mid;
	mid.open("out.dat");
	
	int L = 2000;
	int N = 50;

	Opt O100(100, 0.1, 0.25, 0.1);
	Opt O1(100, 0.1, 0.25, 1);
	Pos *P, *P1;
	P = &O100;
	P1 = &O1;
	vector<Data> b (2), b1(2), bf(4);


	//Media a blocchi
	b = Block_v(L, N, P);
	b1 = Block_v(L, N, P1);

	bf[0] = b[0];
	bf[1] = b[1];
	bf[2] = b1[0];
	bf[3] = b1[1];

	Print_Data(bf, mid);

	
	
	return 0;
	}

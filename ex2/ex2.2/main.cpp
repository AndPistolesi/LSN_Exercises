#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

double f(double x){return 1/(2*sqrt(x));}

int main(){
	
	Random rnd;
	Inizialize(rnd);
	ofstream out1, out3; 
	out1.open("out1.dat");
	out3.open("out3.dat");
	
	int nstep = 100;
	int nblk = 100;
	int RW_steps = 100;

	// Immagazzina le Blk_av per ogni step
	vector<vector<double>> Dist_1(RW_steps, vector<double> (nblk)), Dist_3(RW_steps, vector<double> (nblk));
	// Errore e Media finale per ogni step
	vector<vector<double>> Dist_1_fin(2, vector<double> (RW_steps)), Dist_3_fin(2, vector<double> (RW_steps));

	RW_1D R1(1.);
	RW_3D R3(1.);


	//creazione blocchi
	for (int k=0; k < nblk; k++){
		for (int j=0; j < nstep; j++){
			R1.Reset();
			R3.Reset();
			for (int i=0; i < RW_steps; i++){
				R1.Passo_m();
				R3.Passo_m();
				Dist_1[i][k] += R1.Measure()/nstep;
				Dist_3[i][k] += R3.Measure()/nstep;
			}
		}
		
	}

	//Media e propagazione errori

	for (int i=0; i < RW_steps; i++){
		Dist_1_fin[0][i] = Cum_av(Dist_1[i], f, sqrt).x[nblk-1];
		Dist_1_fin[1][i] = Cum_av(Dist_1[i], f, sqrt).err[nblk-1];
	
		Dist_3_fin[0][i] = Cum_av(Dist_3[i], f, sqrt).x[nblk-1];
		Dist_3_fin[1][i] = Cum_av(Dist_3[i], f, sqrt).err[nblk-1];
		
	}

	for (int i=0; i< RW_steps; i++){
		out3 << i << " " << Dist_3_fin[0][i] << " " << Dist_3_fin[1][i] << endl;
		out1 << i << " " << Dist_1_fin[0][i] << " " << Dist_1_fin[1][i] << endl;
	}
	
	out1.close();
	out3.close();

	return 0;
	}

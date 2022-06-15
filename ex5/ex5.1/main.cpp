#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include <cmath>
#include <fstream>
#include <vector>
#include "libs/libd.h"


using namespace std;


int main(){
	
	//Definizione classi
	Pos *P;
	double a1 = .3, a2 = .7, a3 = .3, a4 = 1.; //Raggi degli step e deviazioni standard
	vector<double> v{1., 1., 1.};
	
	Atom x1(v, a1, 0, 1); // Psi 100, Passo sferico
	Atom x2(v, a2, 1, 1); // Psi 210, Passo sferico
	Atom x3(v, a3, 0, 0); // Psi 100, Passo Gaussiano
	Atom x4(v, a4, 1, 0); // Psi 210, Passo Gaussiano
	int nblk=50, nstep=2000;

	//output
	ofstream out2, out1, out4, out3;
	out4.open("Dist4.out"); // Psi 210, Passo Gaussiano
	out1.open("Dist1.out"); // Psi 100, Passo sferico
	out2.open("Dist2.out"); // Psi 210, Passo sferico
	out3.open("Dist3.out"); // Psi 100, Passo Gaussiano
	Data m1;

	P = &x1;
	Block(10, 10, P, 0); //equilibration
	m1 = Block(nstep, nblk, P, 0, "pos.out");
	Print_Data(m1, out1);
	cout << endl << "Acceptance rate: " << (double)P->Get_acc_tot()/(nblk*nstep) << endl;
	cout << endl << "-----------------------"<< endl;


	P = &x2;
	Block(10, 10, P, 0);
	m1 = Block(nstep, nblk, P, 0, "pos1.out");
	Print_Data(m1, out2);
	cout << endl << "Acceptance rate: " << (double)P->Get_acc_tot()/(nblk*nstep) << endl;
	cout << endl << "-----------------------"<< endl;

	P = &x3;
	Block(10, 10, P, 0);
	m1 = Block(nstep, nblk, P, 0);
	Print_Data(m1, out3);
	cout << endl << "Acceptance rate: " << (double)P->Get_acc_tot()/(nblk*nstep) << endl;
	cout << endl << "-----------------------"<< endl;

	P = &x4;
	Block(10, 10, P, 0);
	m1 = Block(nstep, nblk, P, 0);
	Print_Data(m1, out4);
	cout << endl << "Acceptance rate: " << (double)P->Get_acc_tot()/(nblk*nstep) << endl;
	cout << endl << "-----------------------"<< endl;
	
	return 0;
}

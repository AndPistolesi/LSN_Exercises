#pragma once
#include <iostream>
#include "random.h"
#include "lib.h"
#include <cmath>
#include <fstream>
#include <vector>





class Atom: public Pos{
	public:
		Atom(vector<double> x0, double a0, bool j1, bool k1){x=x0; a=a0; j=j1; k=k1; Inizialize(rnd); acc=0; acc1=0;}

		void Passo_m();
		double Measure();	//Misura distanza
		void Temp_measure(ofstream &);	//Misura posizioni istantanee
		
		double psi2(vector<double> v);
        double dist() {return sqrt(pow(x[0], 2) + pow(x[1], 2) + pow(x[2], 2));}

	
	private:
		vector<double> x;
		double a; //Raggio step o deviazione standard Gaussiana
        bool j; // 1 = Psi 210, 0 = Psi 100
        bool k; // 1 = Passo Unif, 0 = Passo Gauss

};

double Dist(vector<double> x);
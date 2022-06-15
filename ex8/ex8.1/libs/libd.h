#pragma once
#include <iostream>
#include "random.h"
#include "lib.h"
#include <cmath>
#include <fstream>
#include <vector>

class Energy: public Pos{
	public:
		Energy(double x0, double a0, vector<double> v){x=x0; a=a0; para = v; Inizialize(rnd); acc=0; acc1=0;}

		void Passo_m();
		double Measure() {return K() + V();} 
		

		double K(); 
		double V();
		double psi(double x);
		double psi2(double x);

		double Get_x(){return x;}
		vector<double> param(){return para;}

	private:
		double x; // posizione
		double a; // raggio del passo metropolis
		vector<double> para; // mu e sigma

};

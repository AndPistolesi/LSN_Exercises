#pragma once
#include <iostream>
#include "random.h"
#include "lib.h"
#include <cmath>
#include <fstream>
#include <vector>

//Energy class of 8.1
class Ene: public Pos{
	public:
		Ene(double x0, double a0, vector<double> v){x=x0; a=a0; para = v; Inizialize(rnd); acc1=0; acc=0;}

		void Passo_m();
		double Measure() {return K() + V();}	
		

		double K();
		double V();
		double psi(double x);
		double psi2(double x);

		double Get_x(){return x;}
		vector<double> param(){return para;}

	private:
		double x;
		double a;
		vector<double> para;


};

// Class for the evolution of Parameters
class Par: public Pos{
	public:
		Par(vector<double> v1, vector<double> p){v = v1; param = p; Inizialize(rnd); acc1=0; acc=0; En_appo=Energy(p);}

		void Passo_m();
		vector<double> Measure_v();

		double Energy(vector<double> w);
		void Set_T(double temp){T = temp;}
		vector<double> Get_x(){return param;}

	private:
		double T;
		vector<double> v; //incrementi
		vector<double> param; //paramteri
		double En_appo; //variabile di appoggio per salvare l'energia

};


void Input(double &T, int &nblk, int &nstep, vector<double>& param, vector<double>& param1);
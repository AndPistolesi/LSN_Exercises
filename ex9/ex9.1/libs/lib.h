#ifndef __lib__
#define __lib__


#include <iostream>
#include <cmath>
#include <vector>
#include "random.h"

using namespace std;


struct Data {
	//Block averages
	vector<double> v;
	//Cumulative averages
	vector<double> x;
	vector<double> err;
};

	double const_1(double x);
	double Id (double x);
	Data Cum_av(vector<double> v, double(*g)(double) = const_1, double(*f)(double) = Id);
	
	// Printing options
	void Print_Data(vector<Data> b, ofstream &);
	void Print_Data(Data b, ofstream &);
	void Print_vect(vector<vector<double>> v, ofstream &);
	void Print_vect(vector<double> v, ofstream&);
	void Print_line(vector<double> v, ofstream &);
	void Print_line(double v, ofstream&);
	

class Pos{
	public:
		virtual void Passo_m (){} //Passo
		//Valori su cui fare la media a blocchi
		virtual vector<double>  Measure_v(){return vector<double> {1};} 
		virtual double  Measure() {return 0;}
		//Valori da stampare passo passo du file
		virtual void Temp_measure(ofstream &){return;}

		void Reset(){acc=0;}


		int Get_acc(){return acc;}
		//Accettazione complessiva
		int Get_acc_tot(){return acc1;}
	
	protected:
		Random rnd;
		int acc, acc1;
		
};


// Medie a Blocchi
//Se Devo misurare un vettore
vector<Data> Block_v(int nstep, int nblk, Pos*, bool print=1, string save="");
//Se Devo misurare uno scalare
Data Block(int nstep, int nblk, Pos*, bool print=1, string save="");




#endif // __lib__
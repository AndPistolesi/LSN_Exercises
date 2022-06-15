#ifndef __lib__
#define __lib__


#include <iostream>
#include <cmath>
#include <vector>
#include "random.h"

using namespace std;


double Av(vector<double> v);
double Var(vector<double> v);
double Cor(vector<double> v, vector<double> x);



struct Data {

	vector<double> v;
	vector<double> x;
	vector<double> err;
};

	double const_1(double x);
	double Id (double x);
	Data Cum_av(vector<double> v, double(*g)(double) = const_1, double(*f)(double) = Id);
	

	void Print_Data(vector<Data> b, ofstream &);
	void Print_Data(Data b, ofstream &);
	void Print_vect(vector<vector<double>> v, ofstream &);
	void Print_vect(vector<double> v, ofstream&);
	void Print_line(vector<double> v, ofstream &);
	void Print_line(double v, ofstream&);
	

class Pos{
	public:
	//Passo
		virtual void Passo_m (){}
	// Misura di un vettore su cui fare mdia a blocchi
		virtual vector<double>  Measure_v(){return vector<double> {1};}
	//Misura di uno scalare su cui fare media a blocchi
		virtual double  Measure() {return 0;}
	//Misura step per step
		virtual void Temp_measure(ofstream &){return;}

		void Reset(){acc=0;}


		int Get_acc(){return acc;}
		int Get_acc_tot(){return acc1;}
	
	protected:
		Random rnd;
		int acc, acc1;
		
};

vector<Data> Block_v(int nstep, int nblk, Pos*, bool print=1, string save="");
Data Block(int nstep, int nblk, Pos*, bool print=1, string save="");


double Av(vector<double> v);
double Var(vector<double> v);
double Cor(vector<double> v, vector<double> x);


#endif // __lib__
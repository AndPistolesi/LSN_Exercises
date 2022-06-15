
#include "lib.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>


double const_1(double x) {return 1;}
double Id (double x){return x;}

Data Cum_av(vector<double> x, double(*g)(double) /*=const_1*/, double(*f)(double) /*=Id*/){
	vector<double> v(x.size());
	vector<double> v2(x.size());
	vector<double> err(x.size());
	Data b;
	for (int i=0; i<x.size(); i++){
		for (int j=0; j<i+1; j++){
			v[i] += x[j]/(i+1);
			v2[i] += x[j]*x[j]/(i+1);
			}
		
		err[i] = g(v[i])*(sqrt((v2[i] - v[i]*v[i])/(i+1)));
		v[i] = f(v[i]);

		//cout << v[i] << endl;

		}
	
	b.v = x;
	b.x = v;
	b.err = err;
	return b;
}




void Print_Data(vector<Data> b, ofstream& out){

	for (int j=0; j<b[0].x.size(); j++){
		out << j << " "; 
		for (int i=0; i<b.size(); i++)
			out << b[i].v[j] << " " <<b[i].x[j] << " " << b[i].err[j] << " ";
		out << endl;
	}
}

void Print_Data(Data b, ofstream& out){
	for (int j=0; j<b.x.size(); j++){
		out << j << " " << b.v[j] << " " << b.x[j] << " " << b.err[j] << " " << endl;
	}
}

void Print_line(vector<double> v, ofstream &out){
	for (int i=0; i<v.size(); i++)
		out << v[i] << " ";
	out << endl;
}


void Print_vect(vector<vector<double>> b, ofstream& out){
	for (int j=0; j<b.size(); j++){
		out << j << " "; 
		for (int i=0; i<b[0].size(); i++)
			out << b[j][i] << " ";
		out << endl;
	}
}


void Print_vect(vector<double> b, ofstream& out){
	for (int j=0; j<b.size(); j++){
		out << j << " "; 
		out << b[j] << " ";
		out << endl;
	}
}



vector<Data> Block_v(int nstep, int nblk, Pos* P, bool print /*1*/, string save /*""*/){
	ofstream out;
	if(save != ""){out.open(save);} 
	vector<double> w;
	w =  P->Measure_v();
	vector<vector<double>> v(w.size(), vector<double> (nblk));
	vector<Data> m(w.size());	

	for (int iblk=0; iblk < nblk; iblk++){
		P->Reset();
		for (int jstep=0; jstep<nstep; jstep++){
			P->Passo_m();
			w =  P->Measure_v();
			for (int j=0; j<w.size(); j++)
				v[j][iblk] += w[j];
			if(save != "") P->Temp_measure(out);
			
		}
	
		for (int j=0; j<v.size(); j++) 
			v[j][iblk] /= nstep;

		if (print==1){
			cout << endl << "-----------------------------";
			cout << endl << endl << "Block number " << iblk + 1;
			cout << endl << "Acceptance rate: " << (double)P->Get_acc()/nstep ;
			cout << endl << "Average acceptance rate: " << (double)P->Get_acc_tot()/(nstep*(iblk+1)) << endl;
		}
	}
	for (int j=0; j<w.size(); j++) 
		m[j] = Cum_av(v[j]);

	return m;
}



Data Block(int nstep, int nblk, Pos* P, bool print /*1*/, string save /*""*/){
	ofstream out;
	if(save != ""){out.open(save);} 
	double w;
	vector<double> v(nblk);

	for (int iblk=0; iblk < nblk; iblk++){
		P->Reset();
		for (int jstep=0; jstep<nstep; jstep++){
			P->Passo_m();
			w =  P->Measure();
			v[iblk] += w;
			if(save != "") P->Temp_measure(out);
		}
	 
		v[iblk] /= nstep;

		if (print==1){
			cout << endl << "-----------------------------";
			cout << endl << endl << "Block number " << iblk + 1;
			cout << endl << "Acceptance rate: " << (double)P->Get_acc()/nstep ;
			cout << endl << "Average acceptance rate: " << (double)P->Get_acc_tot()/(nstep*(iblk+1)) << endl;
		}
	}

	return Cum_av(v);
}

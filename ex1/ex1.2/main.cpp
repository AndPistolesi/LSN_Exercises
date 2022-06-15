#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

double l = 1;
double L = 1;
double m = 0;



double Exp(double x){return -log(1-x)/l;}
double Lor(double x){return  m + L*tan(M_PI*(x-0.5));}
double f(double x){return x;}

int main(){
	
	Random rnd;
	ofstream mid;
	Inizialize(rnd);
	int N=10000;
	vector<int> v{1,2,10,100};
	//creation of Distribuiton vectors
	vector<vector<double>> exp(4);
	vector<vector<double>> lor(4);
	vector<vector<double>> std(4);
	Distr *E; 
	Distr *L;
	Distr *S;
	
	for (int i=0; i<4; i++){
		for (int j=0; j<N; j++){
		
			E = new Distr(Exp, rnd, v[i]);
			L = new Distr(Lor, rnd, v[i]);
			S = new Distr(f, rnd, v[i]);
			//cout << L.Get_x()[0] << " ";
			exp[i].push_back(E->Av());
			lor[i].push_back(L->Av());
			std[i].push_back(S->Av()); 
		}
	}
	
	
	
	mid.open("mid.dat");
	for (int i=0; i<N; i++){
		mid << endl;
		for (int n=0; n<4; n++){
			mid << exp[n][i] << " , " << lor[n][i] << " , " << std[n][i] << " , ";
			}
		}
  
	
	return 0;
	}

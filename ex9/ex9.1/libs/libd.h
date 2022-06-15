#pragma once
#include <iostream>
#include "random.h"
#include "lib.h"
#include <cmath>
#include <fstream>
#include <vector>



using namespace std;

int Pbc(int i, int size);
double Dist_1(vector<double> w, vector<double> v);
//Controlla se un elemento è in un intervallo di un vettore
bool Check(vector<unsigned int> v, int start, int finish, unsigned int s);
//generatori di città da file o casuali
vector<vector<double>> Cities_gen(int n, bool a, Random &rnd);
vector<vector<double>> Cities_gen(int n, string file);

class Population: public Pos{
	public:
		Population(vector<vector<double>> cit, double p_perm1, double p_inv1, double p_shift1, double p_perm_bl1, int p_size, double p1);

		void Passo_m();
		void Temp_measure(ofstream &);
		double Dist(int j);
		void Permutation(int j);
		void Inversion(int j);
		void Shift(int j);
		void Permutation_blk(int j);
		void Reproduction(int s1, int s2, int s3s);
		void sort();
		bool Autocheck();
		void Order();

		vector<vector<unsigned int>> Get_pop(){return pop;}
		vector<vector<double>> Get_cities(){return cities;}

	private:
		vector<vector<unsigned int>> pop; //popolazione
		vector<vector<double>> cities; //città
		vector<double> dist; //distanza per individup
		vector<unsigned int> top; //migliore
		double min_dist; //distanza del migliore
		int size, p_size; //size di un individuo e della popolazione
		double p_perm, p_inv, p_shift, p_perm_bl, p; //probabilità di mutazione e coefficente di selezione per la riproduzione
		

};

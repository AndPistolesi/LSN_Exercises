#pragma once

#include <iostream>
#include "random.h"
#include "lib.h"
#include <cmath>
#include <fstream>
#include <vector>


int Pbc(int i, int size);
double Dist_1(vector<double> w, vector<double> v);
bool Check(vector<unsigned int> v, int start, int finish, unsigned int s);
vector<vector<double>> Cities_gen(int n, bool a, Random &rnd);
vector<vector<double>> Cities_gen(int n, string file);

class X: public Pos{
	public:
		X(vector<vector<double>> cit, double p_perm1, double p_inv1, double p_shift1, double p_perm_bl1, int p_size, double p1, int rank);

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

		int Size(){return size;}
		vector<vector<unsigned int>> Get_pop(){return pop;}
		vector<vector<double>> Get_cities(){return cities;}
		void Set_ind(vector<unsigned int> v, int j){pop[j] = v;}
		double Get_min_dist(){return min_dist;}

	private:
		vector<vector<unsigned int>> pop;
		vector<vector<double>> cities;
		vector<double> dist;
		vector<unsigned int> top;
		double min_dist;
		int size, p_size;
		double p_perm, p_inv, p_shift, p_perm_bl, p; 
		

};

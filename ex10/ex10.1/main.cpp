#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include "libs/libd.h"
#include <mpi.h>

using namespace std;

void Migrate(int size, int rank, X &x, Random &rnd);
void Scambio(int i, int j, int rank, X &x, Random &rnd);

int main(int argc, char* argv[]){

int size, rank;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

int n_cities = 50;
int pop_size = 3000;
double p_perm = 0.45;
double p_inv = 0.1;
double p_shift = 0.45;
double p_perm_bl = 0.2;
double p = 5;
Random rnd;
Inizialize(rnd, 4*rank);
Pos *P;

X x(Cities_gen(n_cities, "American_capitals.dat"), p_perm, p_inv, p_shift, p_perm_bl, pop_size, p, 4*rank);
P = &x;


ofstream out;
string file = "Averages" + to_string(rank) + ".out";
out.open("Cities" + to_string(rank) + ".out");

cout << endl;

for (int i=0; i<=10; i++){
    Block(50, 1, P, 0, file);
    cout << "\r\e[A" << "[" << rank << "] Completed " << i*10 << "%; Minimum: " << x.Get_min_dist() << endl;
    Migrate(size, rank, x, rnd);
    P = &x;
}

x.Order();
for (int i=0; i<n_cities; i++){
    out << x.Get_cities()[i][0] << " " << x.Get_cities()[i][1] << endl ;
}

out.close();

MPI_Finalize();
return 0;

}


void Migrate(int size, int rank, X &x, Random &rnd){
	int v[size];
	for (int i=0; i<size; i++){
		v[i] = i;
	}
    for(int i=0; i<10; i++) swap(v[(int)rnd.Rannyu(0,size)], v[(int)rnd.Rannyu(0,size)]);
	MPI_Bcast(v, size, MPI_INTEGER, 0, MPI_COMM_WORLD);
	for(int i=0; i<size; i+=2){
		if (i+1 < size)		
			Scambio(v[i], v[i+1], rank, x, rnd);

	}
}

void Scambio(int i, int j, int rank, X &x, Random &rnd){
    vector<unsigned int> v(x.Size());
    unsigned int appo, appo1;
    MPI_Status s1, s2;
    for (int s=0; s<=10; s++){
        for (int t=0; t<x.Size(); t++){
            if (rank == i){
                appo = x.Get_pop()[s][t];
                MPI_Send(&appo,1,MPI_INTEGER,j,1,MPI_COMM_WORLD);
                MPI_Recv(&appo1,1,MPI_INTEGER,j,2,MPI_COMM_WORLD, &s1);
                v[t] = appo1;
				
            }
            else if (rank == j){
                appo = x.Get_pop()[s][t];
                MPI_Send(&appo,1,MPI_INTEGER,i,2,MPI_COMM_WORLD);
                MPI_Recv(&appo1,1,MPI_INTEGER,i,1,MPI_COMM_WORLD, &s2);
                v[t] = appo1;

            }
        }
        if (rank == i || rank == j) x.Set_ind(v,s);
    }
}

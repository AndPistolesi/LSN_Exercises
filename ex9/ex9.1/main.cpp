#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include <cmath>
#include <fstream>
#include <vector>
#include "libs/libd.h"


using namespace std;

int main(){

int n_cities = 34;
int pop_size = 2000;
double p_perm = 0.9;
double p_inv = 0.6;
double p_shift = 0.9;
double p_perm_bl = 0.7;
double p = 2.5;
Random rnd;
Inizialize(rnd);
Pos *P;

Population x(Cities_gen(n_cities, 0, rnd), p_perm, p_inv, p_shift, p_perm_bl, pop_size, p);
P = &x;


ofstream out;
out.open("Cities.out");

Block(40, 30, P, 1, "Averages.out");

x.Order();
for (int i=0; i<n_cities; i++){
    out << x.Get_cities()[i][0] << " " << x.Get_cities()[i][1] << endl ;
}

out.close();

return 0;
}

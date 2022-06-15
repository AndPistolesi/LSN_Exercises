#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include <cmath>
#include <fstream>
#include <vector>
#include "libs/libd.h"

using namespace std;

int main(){

//Variabili per le classi
int nstep, nblk;
double T;
vector<double> param(2), incr(2), x(3);
Input(T, nblk, nstep, param, incr);
Pos *P;
Par p(incr, param);
p.Set_T(T);
P = &p;

//Output
ofstream config, out;
config.open("config.out");
out.open("Parameters.out", ios::app);
vector<Data> m;

m = Block_v(nstep, nblk, P, 0);
Print_Data(m, out);

cout << endl << "Acceptance rate: " << (double)P->Get_acc_tot()/(nblk*nstep) << endl;
cout << endl << "-----------------------"<< endl;

//Salvo configurazione finale
config << p.Get_x()[0] << endl << p.Get_x()[1];

config.close();
out.close();

return 0;
}


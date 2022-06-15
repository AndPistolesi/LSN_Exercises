#include <iostream>
#include "libs/random.h"
#include "libs/lib.h"
#include <cmath>
#include <fstream>
#include <vector>
#include "libs/libd.h"

using namespace std;


int main(){

//class Definition
int nstep = 5000, nblk = 20;
vector<double> a{0.80182, 0.633461};
//vector<double> a{0., 1.};
Pos *P;
Energy p(0, 2., a);
P = &p;

//output
ofstream out;
out.open("Energy.out");
Data m;

m = Block(nstep, nblk, P);
Print_Data(m, out);

return 0;
}

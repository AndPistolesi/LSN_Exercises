#include "libd.h"

void Opt::Passo_m(){
    x = x0;
    for (int i=0; i<1/t; i++)
	    x *= exp((r-0.5*s*s)*t+s*sqrt(t)*rnd.Gauss(0,1));	
}

vector<double> Opt::Measure_v(){
    vector<double> v(2);
    v[0] = exp(-1*r)*max(0.,x-x0);
    v[1] = exp(-1*r)*max(0.,-x+x0);
   // cout << v[0] << endl;
    return v;
}

#include "libd.h"



void Input(double &T, int &nblk, int &nstep, vector<double>& param, vector<double>& param1){
    ifstream in;
    in.open("input.in");
	
    in >> T;
	in >> param1[0];
	in >> param1[1];
	in >> nblk;
	in >> nstep;

	in.close();
	in.open("config.in");
	in >> param[0];
	in >> param[1];
}


double Ene::psi(double y){
	double mu = para[0], sigma=para[1];
	return  exp(-pow(y-mu,2)/(2*sigma*sigma)) + exp(-pow(y+mu,2)/(2*sigma*sigma)) ;
	}

double Ene::psi2(double y){
	return psi(y)*psi(y);
	}

void Ene::Passo_m(){
	double x1 = x;
	x1 += rnd.Rannyu(-a, a);

	if (rnd.Rannyu() <= min(1., psi2(x1)/psi2(x))){
		x = x1;
		acc ++;
		acc1 ++;
	}
}

double Ene::V() { 
	return x*x*x*x - 5./2*x*x;
	//return 0.5*x*x;
}

double Ene::K(){
	double a=para[0], s=para[1]; 
	return -0.5*(-exp(-(x - a)*(x - a)/(2*s*s))/(s*s) - exp(-(a + x)*(a + x)/(2*s*s))/(s*s) + (x - a)*(x - a)*exp(-(x - a)*(x - a)/(2*s*s))/(s*s*s*s) + ((a + x)*(a + x)*exp(-(a + x)*(a + x)/(2*s*s)))/(s*s*s*s))/psi(x);
}


void Par::Passo_m(){
    vector<double> z = param;
    z[0] += rnd.Rannyu(-v[0], v[0]);
    z[1] += rnd.Rannyu(-v[1], v[1]);
	double a = Energy(z);
    if (rnd.Rannyu() <= exp(-(a-En_appo)/T)) {
		En_appo = a;
		param = z;
		acc ++;
		acc1 ++;
	}

}
vector<double> Par::Measure_v(){
	vector<double> v(3);
	v[1] = param[0];
	v[2] = param[1];
	v[0] = En_appo;
    return v;
}

double Par::Energy(vector<double> w){
    Pos *P;
    Ene p(0, 2., w);
    P = &p;
    
    Data m;

    m = Block(2000, 10, P, 0);
    return m.x[9];
}

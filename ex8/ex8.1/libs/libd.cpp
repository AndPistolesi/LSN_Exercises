
#include "libd.h"


double Energy::psi(double y){
	double mu = para[0], sigma=para[1];
	return  exp(-pow(y-mu,2)/(2*sigma*sigma)) + exp(-pow(y+mu,2)/(2*sigma*sigma)) ;
	}

double Energy::psi2(double y){
	return psi(y)*psi(y);
	}

void Energy::Passo_m(){
	double x1 = x;
	x1 += rnd.Rannyu(-a, a);

	if (rnd.Rannyu() <= min(1., psi2(x1)/psi2(x))){
		x = x1;
		acc ++;
		acc1 ++;
	}
}

double Energy::V() { 
	return x*x*x*x - 5./2*x*x;
	//return 0.5*x*x;
}

double Energy::K(){
	double a=para[0], s=para[1]; 
	return -0.5*(-exp(-(x - a)*(x - a)/(2*s*s))/(s*s) - exp(-(a + x)*(a + x)/(2*s*s))/(s*s) + (x - a)*(x - a)*exp(-(x - a)*(x - a)/(2*s*s))/(s*s*s*s) + ((a + x)*(a + x)*exp(-(a + x)*(a + x)/(2*s*s)))/(s*s*s*s))/psi(x);
}


#include "libd.h"


//Funzioni d'onda per altri orbitali
//return pow( sqrt(2)/(2*27*M_PI)*(-pow(x[0], 2) - pow(x[1], 2) + 2*pow(x[2], 2))/(pow(Dist(v),2))*pow(3, -3/2)*pow(Dist(v), 2)*exp(-Dist(v)/3), 2);
//return pow(1./8*sqrt(1./tgamma(8))*sqrt(45/(4*M_PI*32))*(7*pow(x[2],2)-pow(Dist(v),2)*(pow(x[0],2) + pow(x[1],2)))/pow(Dist(v),4)*pow(Dist(v)/2, 3)*exp(-Dist(v)/4), 2);


double Atom::psi2(vector<double> v){
    if (j)
	    return pow(v[2]*exp(-Dist(v)/2),2); //Psi 210
    else
        return pow(exp(-Dist(v)),2); //Psi100
	}


double Dist(vector<double> x) {
    return sqrt(pow(x[0], 2) + pow(x[1], 2) + pow(x[2], 2));
}

void Atom::Passo_m(){
	vector<double> x1 = x;
    double f, t, r;
	for (int i=0; i<x.size(); i++){
        if (k){
            //Passo sferico
            r = 3*a*pow(rnd.Rannyu(),1/3);
	        t = M_PI/2 + asin(rnd.Rannyu(-1, 1));
	        f = rnd.Rannyu(0,2*M_PI);
	        x1[0] += r*cos(f)*sin(t);
	        x1[1] += r*sin(f)*sin(t);
	        x1[2] += r*cos(t);
        }
        else{
            //Passo Gaussiano
            x1[0] += rnd.Gauss(0, a);
	        x1[1] += rnd.Gauss(0, a);
	        x1[2] += rnd.Gauss(0, a);
        }

    }
    //cout << psi2(x1)/psi2(x);
	if (rnd.Rannyu() <= min(1., psi2(x1)/psi2(x))){
		x = x1;
		acc ++;
		acc1 ++;
	}
}

void Atom::Temp_measure(ofstream &out){
    out << x[0] << " " << x[1] << " " << x[2] << endl;
}

double Atom::Measure(){
    return dist();
}

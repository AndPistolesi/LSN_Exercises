#pragma once
#include <iostream>
#include "random.h"
#include "lib.h"
#include <cmath>
#include <fstream>
#include <vector>

class Opt: public Pos {
    public:
        Opt(double _x0, double _r, double _s, double _t){ x = _x0; x0 = _x0; s = _s; t = _t, r = _r, Inizialize(rnd); acc = 0; acc1 = 0;}
        void Passo_m(); 
        vector<double> Measure_v();

    private:
        double x; //posizione
        double x0; //posizione iniziale
        double r; //media
        double s; // volatilità
        double t; //incremento

};


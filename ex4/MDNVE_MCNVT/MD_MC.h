/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#ifndef __fluid__
#define __fluid__


#include <vector>
//Random numbers
#include "random.h"


int seed[4];
Random rnd;

//parameters, observables
char flav;
const int m_props=1000;
const int ivs = 900; //number of intervals for g(r)
int n_props, iv, ik, it, ie, iw;
int ig[ivs];
double vtail, ptail, bin_size, sd;
double walker[m_props];
double count=0;
std::vector<double> Epot0 (1), err_g_r(ivs);

// averages
double blk_av[m_props], blk_norm, accepted, attempted;
double glob_av[m_props], glob_av2[m_props];
double stima_pot, stima_pres, stima_kin, stima_etot, stima_temp, stima_g[ivs];
double err_pot, err_pres, err_kin, err_etot, err_temp;
 

//configuration
const int m_part=108;
double x[m_part],    y[m_part],    z[m_part];
double xold[m_part], yold[m_part], zold[m_part];
double vx[m_part],  vy[m_part],   vz[m_part];
double Vtail, Wtail;

// thermodynamical state
int npart;
double beta,temp,energy,vol,rho,box,rcut, Dv[ivs];

// simulation
int iNVET, nstep, nblk, restart, G_step=2000;
double delta;


//functions
void Input(void);
void Reset(int);
void Accumulate(void);
void Averages(int);
void Move(void);
void ConfFinal(void);
void ConfXYZ(int);
void Measure(void);
double Boltzmann(double, double, double, int);
double Pbc(double);
double Error(double,double,int);
double Force(int, int);

#endif

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/


#include "libd.h"

vector<vector<double>> Cities_gen(int n, string file){
	ifstream input;
	input.open(file);
	int a;
	double b,c;
	vector<vector<double>> v(n, vector<double> (2));

	for (int i=0; i<n; i++){
		input >> a;
		input >> b;
		input >> c;
		v[i][0] = b;
		v[i][1] = c; 

	}

	return v;
}

vector<vector<double>> Cities_gen(int n, bool a, Random &rnd){
	vector<vector<double>> v(n, vector<double> (2)); 
	double x = 0;
	if (a == 0){ //circle
		for (int i=0; i<n; i++){
			x += 2.*M_PI/n;
			v[i][0] = cos(x);
			v[i][1] = sin(x);
			
		}
	}
	if (a == 1){ //square
		for (int i=0; i<n; i++){
			v[i][0] = rnd.Rannyu();
			v[i][1] = rnd.Rannyu();
		}
	}
	return v;
}

Population::Population(vector<vector<double>> cit, double p_perm1, double p_inv1, double p_shift1, double p_perm_bl1, int p_size1, double p1){
	
	Inizialize(rnd);
	acc = 0;
	acc1 = 0;
	p = p1;
	size = cit.size() - 1;
	cities = cit;
	p_size = p_size1;
	p_perm = p_perm1;
	p_perm_bl = p_perm_bl1;
	p_shift = p_shift1;
	p_inv = p_inv1;

	
	pop = vector<vector<unsigned int>> (p_size, vector<unsigned int> (33));
	dist = vector<double> (p_size);
	cout << "[Generating population]" << endl;
	for (int i=0; i<p_size; i++){
		for (int j=0; j<size; j++){
			pop[i][j] = j;
		}
		for (int s=0; s<p_size/*(int)rnd.Rannyu(0., size+1)*/; s++)
			swap(pop[i][(int)rnd.Rannyu(0.,size)], pop[i][(int)rnd.Rannyu(0.,size)]);
	}
	sort();
	top = pop[0];
	min_dist = dist[0];
	cout << "[Population Generated]" << endl;
}

double Population::Dist(int j){
	double a = 0;
	for (int i=0; i<size-1; i++){
		a += Dist_1(cities[pop[j][i]], cities[pop[j][i+1]]);
	}
	return a + Dist_1(cities[size], cities[pop[j][size-1]]) + Dist_1(cities[size], cities[pop[j][0]]);
}

void Population::Permutation(int j){
		unsigned int a, b, c;
		b = (int)rnd.Rannyu(0., size);
		c = (int)rnd.Rannyu(0., size);
		a = pop[j][b];
		pop[j][b] = pop[j][c];
		pop[j][c] = a;  
}

void Population::Inversion(int j){
	int a, b, c;
	a = (int)rnd.Rannyu(0, size);
	b = (int)rnd.Rannyu(0, size);
	for(int i=min(a,b); i<max(a,b); i++){
		c = pop[j][i];
		pop[j][i] = pop[j][max(a,b)];
		pop[j][max(a,b)] = c;
	}

}

void Population::Shift(int j){
	int a;
	vector<unsigned int> g = pop[j];
	a = (int)rnd.Rannyu(0, size);
	for (int i=0; i<size; i++)
		pop[j][i] = g[Pbc(i-a, size)];
}


void Population::Permutation_blk(int j){
 	int a, b, d;
	b = (int)rnd.Rannyu(0., size);
	d = (int)rnd.Rannyu(0., size);
	if (abs(b-d)%2 == 1)
		b ++;
	for(int i=b; i<=(b+d)/2; i++){
		a = pop[j][i];
		pop[j][i] = pop[j][i+abs(d-b)/2];
		pop[j][i] = a;  
	}
}


int Pbc(int i, int size){
	if (i >= size)
		return i - size;
	else if(i < 0)
		return size + i;
	else return i;
}

double Dist_1(vector<double> w, vector<double> v){
	return sqrt(pow(v[0] - w[0],2) + pow(v[1] - w[1],2));
}


void Population::sort(){
	//cout << "Sorting";
	bool a = true;
	for (int i=0; i<p_size; i++)
		dist[i] = Dist(i);

	while (a){
		a = false;
		for (int i=0; i<p_size-1; i++){
			if (dist[i]>dist[i+1]){
				swap(pop[i], pop[i+1]);
				swap(dist[i], dist[i+1]);
				a = true;
			}
		}
	}
}


void Population::Reproduction(int s1, int s2, int s3){
	int a = (int)rnd.Rannyu(0, size);
	//cout << a << endl;
	bool check, c;
	int s = 0;
	vector<unsigned int> v = pop[s1], w = pop[s2], x = w;
	for (int i=a; i<size; i++){
		s = 0;
		c = true;
		check = Check(w, 0, i, v[i]);
		if (check){
			while (c){
				if(!Check(w, 0 ,i, v[s])){
					w[i] = v[s];
					c = false;
				}
				s ++;
			}	
		}
		else
			w[i] = v[i];
	}
	

	for (int i=a; i<size; i++){
		s = 0;
		c = true;
		check = Check(v, 0, i, x[i]);
		if (check){
			while (c){
				if(!Check(v, 0 ,i, x[s])){
					v[i] = x[s];
					c = false;
				}
				s ++;
			}	
		}
		else
			v[i] = x[i];
	}

	pop[s3-1] = w;
	pop[s3] = v;
	
}


bool Check(vector<unsigned int> v, int start, int finish, unsigned int s){
	for(int i=start; i<finish; i++){
		if(v[i] == s)
			return true;
	}

	return false;
}

bool Population::Autocheck(){
	for (int i=0; i<p_size; i++){
		for (int j=0; j<size; j++){
			if(Check(pop[i], j+1 , size, pop[i][j]))
				return true;
		}
	}
	return false;
}


void Population::Passo_m(){
	int a, b;
	for(int i=p_size-1; i>0; i-=2){
		a = (int)(size*pow(rnd.Rannyu(),p));
		b = (int)(size*pow(rnd.Rannyu(),p));
		//cout << a <<" " << b;
		Reproduction(a , b, i);
	}
	for(int i=0; i<p_size; i++){
		if(rnd.Rannyu() < p_inv)
			Inversion(i);
		if(rnd.Rannyu() < p_perm)
			Permutation(i);
		if(rnd.Rannyu() < p_perm_bl)
			Permutation_blk(i);
		if(rnd.Rannyu() < p_shift)
			Shift(i);
	}
	if (Autocheck()){
		cout << "[Autocheck failed]" << endl;
		exit(-1);
	}
	
	sort();
	if (dist[0] < min_dist){
		top = pop[0];
		min_dist = dist[0];
	}
	
	
}

void Population::Temp_measure(ofstream & out){
	double sum = 0;
	for (int i=0; i<p_size/2; i++){
		sum += dist[i];
	}
	out << dist[0] << " " << sum/(p_size/2) << endl;
	
}

void Population::Order(){
	
	vector<vector<double>> x = cities;
	cities[0] = x[size];
	for (int i=1; i<size+1; i++)
		cities[i] = x[top[i-1]];

}

#include <iostream>
#include <math.h>
#include "fonctions.cpp"
#include <complex>
#include <Windows.h>
using namespace std;

//parametre actuel:
//alpha=1.1
//r=0
//sigma=0.01
//S0=St=K=1
//T=1000

class expo{
public:
	double operator()(double x){return exp(-x);};
};

class tot{
public:
	double operator()(double x){return exp(-(x*x));};
};
class sinu{
public:
	double operator()(double x){return sin(x);};
};

class poly{
public:
	double operator()(double x){return x*x;};
};

template<typename Function>
complex<double> trapeze(Function f, double a, double b, int n){
	double step=(b-a)/n;
	complex<double> area=(f(a)+f(b))*0.5;
	for(int i=1; i<n; i++){
		area=area+f(a+i*step);
	}
	return step*area;
}

template<typename Function>
complex<double> simpson(Function f,double a, double b, int n){
	double step=(b-a)/n;
	complex<double> area=(f(a)+f(b));
	for(int i=1; i<n; i++){
		if(i%2)area=area+4*f(a+i*step);
		else area=area+f(a+i*step);
	}
	area*=step/3;
	return area;
}

template<typename Function>
complex<double> romberg(Function f,double a,double b, int n){
	complex<double> *R=new complex<double>[n*n]; // où R[i+n*j] correspond à R(i,j)
	for(int i=0;i<n;i++){
	   R[i]=trapeze(f,a,b,pow(2,i));} //On initialise
    for(int i=1;i<n;i++){
		for(int j=1;j<=i;j++){
				R[i+n*j]=(pow(4,j)*R[i+n*(j-1)]-R[i-1+n*(j-1)])/(pow(4,j)-1);
			}	
		}
	complex<double> result=R[(n-1)+n*(n-1)];
	delete[]R;
	return result;
}

double CDF(int n,double x){ //developpement de la fonctio de répartition en une série intière
	double sum=x;;
	double terme=x;
	for(int i=1;i<n;i++){
	terme=terme*pow(x,2)/(2*i+1);
	sum+=terme;
	}
	return(1/2+1/(sqrt(2*M_PI))*exp(-pow(x,2)/2)*sum);
}

double Call_value_theory(double T, double k, double S,double sigma,double r){
	double d1,d2;
	int n=1000000;
	d1=1/(sigma*sqrt(T))*(log(S)-k+(r+pow(sigma,2)/2)	*T);
	d2=1/(sigma*sqrt(T))*(log(S)-k+(r-pow(sigma,2)/2)*T);
	return(CDF(n,d1)*S-CDF(n,d2)*exp(-r*T+k));
}

complex<double> Value_2_int(double T, double borne_sup,double St=1,double K=1){ //calcul la valeur via les 2 intégrales
	int1_attari int1;
	int2_attari int2;
	int r=0; //voir comment le choper avec les parametres
	return(St*(0.5+1/M_PI*romberg(int1,0.01,borne_sup,35))-exp(-r*T)*K*(0.5+1/M_PI*romberg(int2,0.01,borne_sup,35)));
}

complex<double> Value_1_int(double T, double borne_sup,double St=1,double K=1){ //calcul avec une seule intégrale, on doit trouver la même chose
	int_attari integrand;
	int r=0; //voir comment le choper avec les parametres
	return(St-exp(-r*T)*K/2-exp(-r*T)*K*(1/M_PI)*romberg(integrand,0.000000000001,borne_sup,25));
}

int main(){
	expo f;
	expo_complex exp;
	tot g;
	sinu s;
	PSI psi;
	PHI phi;
	double Pi=3.14159265358979;
	poly p;
	double b=1000;

	cout<<"Calcul theorique: "<<endl;
	cout << Call_value_theory(1000,0,1,0.1,0) <<endl;
	//initialisation du chrono
	DWORD begin_time=GetTickCount();
	cout <<"attari1:" <<Value_1_int(10000,b,1,1) <<endl;
	DWORD end_time=GetTickCount()-begin_time;
	cout<<"temps d'execution : "<<end_time<<".ms"<<endl;
	begin_time=GetTickCount();
	cout<<"attari2:" <<Value_2_int(10000,b,1,1) <<endl;
	end_time=GetTickCount()-begin_time;
	cout<<"temps d'execution : "<<end_time<<".ms"<<endl;
	cout<<"Trapeze : "<<endl; 
	cout<<trapeze(psi,-b,b,100000)<<endl;
	cout<<"Romberg : "<<endl;
	cout<<romberg(psi,-b,b,25) <<endl;
	//on devrait obtenir le même résultat pour les 2 derniers trucs mais là non.

	while(true){}
	return 0;
}
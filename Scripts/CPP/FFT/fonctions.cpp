#include <complex>
#include <math.h>

#define _USE_MATH_DEFINES

using namespace std;

//attention à l'utilisation des float ou double
class PHI; class PSI;
class BS{
	friend class PHI;
	friend class PSI;
private:
	float r,sigma,t,W,S0;
public:
	BS(){
		r=0;sigma=0;t=0;W=0;S0=1;
	}
	BS(float r_,float sigma_,float t_,float W_,float S0_=1){
		r=r_; sigma=sigma_; t=t_; W=W_; S0=S0_;
	}
	float operator()(){
		return S0*exp((r-pow(sigma,2)/2)*t+sigma*W);
	}
};


class PHI{
	friend class PSI;
private:
	BS bs;
	double T; //T est-il égal au t de bs ?
public:
	PHI(){
		T=0;
	}
	PHI(BS bs_, double T_){
		bs=bs_; T=T_;
	}
	complex<double> operator()(complex<double> u){
		double x=-1/2*(pow(u.real(),2)-pow(u.imag(),2))*pow(bs.sigma,2)*T-u.imag()*(log(bs.S0)+(bs.r-pow(bs.sigma,2)/2)*T);
		double y=u.real()*(log(bs.S0)+(bs.r-pow(bs.sigma,2)/2)*T)-u.real()*u.imag()*pow(bs.sigma,2)*T;
		complex<double> z=complex<double>(x,y);
		return exp(z);
	}
};

class PSI{
	PHI phi;
	double alpha;
public:
	PSI(){
		alpha=0;
	}
	PSI(PHI phi_,double alpha_){
		phi=phi_; alpha=alpha_;
	}
	complex<double> operator()(double v){
		complex<float> z=complex<float>(v,-alpha-1);
		complex<float> num=exp(-phi.bs.r*phi.T)*phi(z); 
		complex<float> denum=complex<float>(pow(alpha,2)+alpha-pow(v,2),(2*alpha+1)*v);
		return (num/denum);
	}
};

class Xj_trap{
	PSI psi;
	double eta;
public:
	Xj_trap(PSI psi_,double eta_){
		psi=psi_; eta=eta_;
	}
	complex<double> operator()(int j){
		double expo=(j%2)?-1:1;//le préfacteur se simplifie en exp(i*Pi*j) d'où la valeur (attention j%2 renvoie 1 donc True si j n'est pas divisible par 2)
		complex<double> x=expo*psi(eta*j);
		return x;
	}
};
#include <complex>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

//attention à l'utilisation des double ou double
class PHI; class PSI;
class BS{
	friend class PHI;
	friend class PSI;
private:
	double r,sigma,S0;
public:
	BS(){
		r=0;sigma=0.01;S0=1;
	}
	BS(double r_,double sigma_,double S0_=1){
		r=r_; sigma=sigma_; S0=S0_;
	}
};


class PHI{
	friend class PSI;
private:
	BS bs;
	double T; 
public:
	PHI(){
		T=1000;
	}
	PHI(BS bs_, double T_){
		bs=bs_; T=T_;
	}
	complex<double> operator()(complex<double> u){
		/*double x=-1/2*(pow(u.real(),2)-pow(u.imag(),2))*pow(bs.sigma,2)*T-u.imag()*(log(bs.S0)+(bs.r-pow(bs.sigma,2)/2)*T);
		double y=u.real()*(log(bs.S0)+(bs.r-pow(bs.sigma,2)/2)*T)-u.real()*u.imag()*pow(bs.sigma,2)*T;
		complex<double> z=complex<double>(x,y);*/
		complex<double>z(0,-pow(bs.sigma,2)*T/2);
		double t=-T/2*pow(bs.sigma,2);
		return exp(z*u+t*pow(u,2));
	}
};

class Xj_trap;

class PSI{
	friend class Xj_trap;
private:
	PHI phi;
	double alpha;
public:
	PSI(){
		alpha=1.1;
	}
	PSI(PHI phi_,double alpha_){
		phi=phi_; alpha=alpha_;
	}
	complex<double> operator()(double v){
		double k=1;//attention à ce cas qu'on devrat surement rentrer en parametre
		complex<double> z1=complex<double>(0,-k*v);//attention
		complex<double> z=complex<double>(v,-alpha-1);
		complex<double> num=exp(-phi.bs.r*phi.T)*phi(z); 
		complex<double> denum=complex<double>(pow(alpha,2)+alpha-pow(v,2),(2*alpha+1)*v);
		return (num/denum*exp(z1)/M_PI*exp(-alpha*k));
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
	double prefact(int k, int N){
		double factor=eta*exp(-psi.alpha*M_PI*(2*k-N)/(N*eta))/M_PI;
		return factor;
	}

};
/*
class expo_complex{
public:
	complex<double> operator()(double x){
		int k=10;
		complex<double> z=complex<double>(0,-k*x);
	    return exp(z);};
};
*/
class int2_attari{ //premiere des deux deux intégrales dont parle Attari
private:
	PHI phi;
public:
  complex<double> operator()(double x){
	double k=1;//parametre à modifier
	double I1=phi(x).imag();
	double R1=phi(x).real();
		double num=I1*cos(x*k)-R1*sin(x*k);
	
	return num/x;
  }
};

class int1_attari{ //premiere des deux deux intégrales dont parle Attari
private:
	PHI phi;
public:
  complex<double> operator()(double x){
	double k=1;//parametre à modifier
	/*double I2=phi(complex<double>(x,-1)).imag();
	double R2=phi(complex<double>(x,-1)).real();
		double num=I2*cos(x*k)-R2*sin(x*k);*/
	double result=(exp(complex<double>(0,-x*log(k)))*phi(complex<double>(x,-1))/(complex<double>(0,x)*phi(complex<double>(0,-1)))).real();
	return result;
  }
};

class int_attari{ //2 intégrales en une Attari
private:
	PHI phi;
public:
  complex<double> operator()(double x){
	double k=1;//parametre a modifier
	double I2=phi(x).imag();
	double I1=phi(complex<double>(x,-1)).imag();
	double R2=phi(x).real();
	double R1=phi(complex<double>(x,-1)).real();
		double num=(R2+I2/x)*cos(x*k)+(I2-R2/x)*sin(x*k);
		double denum=(1+pow(x,2));
	
	return num/denum;
  }
};
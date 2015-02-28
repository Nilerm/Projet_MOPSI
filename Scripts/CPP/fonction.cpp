#include <complex>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

float BS(float r,float sigma, float t,float W,float S0=1){
    return S0*exp((r-pow(sigma,2)/2)*t+sigma*W);
}

complex<float> phi_BS(float r,float sigma,float T,complex<float> u, float S0=1){
    float x=-1/2*(pow(u.real(),2)-pow(u.imag(),2))*pow(sigma,2)*T-u.imag()*(log(S0)+(r-pow(sigma,2)/2)*T);
    float y=u.real()*(log(S0)+(r-pow(sigma,2)/2)*T)-u.real()*u.imag()*pow(sigma,2)*T;
    complex<float> z=complex<float>(x,y);
    return exp(z);
}

float VG(float r,float t, float X,float theta,float nu,float sigma, float S0=1){
    float omega=1/nu*log(1-theta*nu-1/2*pow(sigma,2)*nu);
    return (S0*exp(r*t+X+omega*t));
}

complex<float> phi_VG(float r,float nu,float theta,float T,float sigma, complex<float> u,float S0=1){
    float omega=1/nu*log(1-theta*nu-1/2*pow(sigma,2)*nu);
    float expo=exp(log(S0)+(r+omega)*T);
    float x=1+theta*nu*u.imag()+1/2*pow(sigma,2)*(pow(u.real(),2)-pow(u.imag(),2))*nu;
    float y=-theta*nu*u.real()+pow(sigma,2)*nu*u.real()*u.imag();
     complex<float> z=complex<float>(x,y);
    return (expo*pow(z,-T/nu));
}

complex<float> psi(float r,complex<float> phi,float alpha, float v,float T){
    complex<float> z=complex<float>(v,-alpha-1);
    complex<float> num=exp(-r*T)*phi; //penser à définir phi(z) à l'appel de la fonction
    complex<float> denum=complex<float>(pow(alpha,2)+alpha-pow(v,2),(2*alpha+1)*v);
    return (num/denum);
}

complex<float> x_j_trapeze(float eta,float b,float v,float alpha,float k,float psi){
    complex<float> expo=complex<float>(0,b*v);
    float eta_bis=eta/M_PI;
    complex<float> res=exp(-alpha*k)*exp(expo)*psi*eta_bis; //penser à utiliser psi(v)
    return (res);
}

complex<float> x_j_simpson(float eta,float b,float v,float alpha,float k,float psi,int j){
    complex<float> expo=complex<float>(0,b*v);
    float eta_bis=eta/(3*M_PI);
    float elem=3+pow(-1,j);
    if(j==1){
        float elem=2+pow(-1,j);}
    complex<float> res=exp(-alpha*k)*exp(expo)*psi*eta_bis*elem; //penser à utiliser psi(v)

    return res;
}

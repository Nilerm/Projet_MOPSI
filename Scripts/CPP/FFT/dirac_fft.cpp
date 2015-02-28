#include "fftw3.h"
#include <iostream>

using namespace std;

int main(){
	int size=32;
	fftw_complex *in, *out;
	fftw_plan p;

	in=(fftw_complex*) fftw_malloc(sizeof(fftwf_complex)*size); //allocation d'un tableau prenant les variables d'échantillonage en entrée
	out=(fftw_complex*) fftw_malloc(sizeof(fftwf_complex)*size); //allocation d'un tableau allant recevoir les valeurs de sorties
	p=fftw_plan_dft_1d(size,in,out,FFTW_FORWARD,FFTW_ESTIMATE); //création du plan de la transformée
	//on alloue arbitrairement les valeurs 
	for(int i=0; i<size; i++){ 
		if(i==2) in[i][0]=1;//Dirac en 2
		else in[i][0]=0;
		in[i][1]=0;
	}
	fftw_execute(p); //execute le plan
	// affichage des valeurs trouvées
	for(int i=0; i<size; i++){
		cout<<"coeff "<<i<<" : "<<out[i][0]<<"+ I*"<<out[i][1]<<endl;
	}
	cout<<"Tout va bien"<<endl;
	//lignes posant problème à l'exécution
	//fftw_destroy_plan(p);
	//fftw_free(in);
	//fftw_free(out);
	return 0;
}
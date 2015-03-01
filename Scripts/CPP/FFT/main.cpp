#include <iostream>
#include "fftw3.h"
#include "functions.cpp"

using namespace std;

int main(){
	//initialisation des fonctions
	BS bs;//remplir des parenthèses avec des valeurs probables
	PHI phi;//remplir des parenthèses avec une valeur probable pour T
	PSI psi;//remplir des parenthèses avec une valeur probable pour alpha
	Xj_trap xj(psi,0);//remplir les parenthèses avec une valeur probable pour eta

	int size=N; //attention N et eta sont liés
	fftw_complex *in, *out;
	fftw_plan p;

	in=(fftw_complex*) fftw_malloc(sizeof(fftwf_complex)*size); //allocation d'un tableau prenant les variables d'échantillonage en entrée
	out=(fftw_complex*) fftw_malloc(sizeof(fftwf_complex)*size); //allocation d'un tableau allant recevoir les valeurs de sorties
	p=fftw_plan_dft_1d(size,in,out,FFTW_FORWARD,FFTW_ESTIMATE); //création du plan de la transformée
	//on alloue les valeurs 
	for(int i=0; i<size; i++){ 
		complex<double> z=xj(i);
		in[i][0]=z.real();
		in[i][1]=z.imag();
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
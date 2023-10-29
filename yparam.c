#include <stdio.h>
#include <math.h>
#include <string.h>
#include <complex.h>

#define J _Complex_I

//input,output,forward, reverse admittances
complex float yi,yo,yf,yr;

float linvill_stability_factor(void){
	complex float yfyr=yf*yr;
	float mag_yfyr=sqrt(creal(yfyr)*creal(yfyr)+cimag(yfyr)*cimag(yfyr));
	float gi=crealf(yi);
	float go=crealf(yo);
	float g_yfyr=crealf(yfyr);
	return mag_yfyr/(2*gi*go-g_yfyr);
}

float MAG(void){
	float mag_yf=crealf(yf)*crealf(yf)+cimagf(yf)*cimagf(yf);
	float gi=crealf(yi);
	float go=crealf(yo);
	return 10*log10(mag_yf/(4*gi*go));
}

float transducer_gain(complex float ys,complex float yl){
	float mag_yf=crealf(yf)*crealf(yf)+cimagf(yf)*cimagf(yf);
	complex float z=(yi+ys)*(yo+yl)-yf*yr;
	float mag_z=creal(z)*creal(z)+cimag(z)*cimag(z);
	return 10*log10((4*crealf(ys)*crealf(yl)*mag_yf)/mag_z);
}

void find_mismatch_impedance(complex float *ys,complex float *yl,float k,float gs){
	complex float yfyr=yf*yr;
	float mag_yfyr=sqrt(creal(yfyr)*creal(yfyr)+cimag(yfyr)*cimag(yfyr));
	float gl=k*(mag_yfyr+crealf(yfyr))/(2*(crealf(yi)+gs))-crealf(yo);
	*yl=gl-cimagf(yo)*J;
	complex float new_yi=yi-yfyr/(yo+*yl);
	*ys=crealf(new_yi)-cimagf(new_yi)*J;
}

void print_complex(complex float z){
	float im=cimagf(z);
	float re=crealf(z);
	printf("%.3f",re);
	if(im>=0)
		printf("+j");
	else
		printf("-j");
	printf("%.3f mmho\n",fabs(im));
}

void display_admittances(void){
	printf("Input Admittance = ");
	print_complex(yi);
	printf("Output Admittance = ");
	print_complex(yo);
	printf("Forward Admittance = ");
	print_complex(yf);
	printf("Reverse Admittance = ");
	print_complex(yr);	
}

void MPSH10(void){
	yi=3.1+7*J;
	yo=0.1+0.5*J;
	yf=52-22*J;
	yr=-0.01-0.25*J;
}

int main(int argc, char **argv){
	MPSH10();
	
	printf("\n\nThis is a tool for design using the MPSH10 transistor\n\n");
	printf("Admittances\n\n");
	display_admittances();
	printf("MAG = %.2f dB\n\n",MAG());

	printf("finding impedances\n\n");
	complex float ys,yl;
	
	find_mismatch_impedance(&ys,&yl,5,10);
	printf("Source admittance = ");
	print_complex(ys);
	printf("Load admittance = ");
	print_complex(yl);
	printf("transducer gain = %.2f dB\n",transducer_gain(ys,yl));

	return 0;
}
#include <stdio.h>
#include <math.h>
#define epsilon 1e-6

double sinh(double x);

int main(){
	double x;
	scanf("%lf",&x);
	printf("%lf",sinh(x));
}

double sinh(double x){
	double sh = 0, a = 1;
	long i = 0;
	while (a > epsilon){
		double gt = 1;
		for (long j = 1; j <= (2*i + 1); j++) gt *=j;
		a = pow(x, 2*i +1) / gt;
		sh += a;
		i++; 
	}
	return sh;
}

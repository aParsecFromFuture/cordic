#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159
#define K 0.60725

typedef struct vector vector;

struct vector{
	unsigned long x;
	unsigned long y;
};

vector* create_vector(unsigned long,unsigned long);
vector* cordic(double,const char*);

double ator(double);
double rtoa(double);

double my_sin(double);
double my_cos(double);
double my_tan(double);

int main(){
	printf("%lf",my_cos(ator(60)));	
}

vector* create_vector(unsigned long x,unsigned long y){
	vector *v = malloc(sizeof(vector));
	v->x = x;
	v->y = y;
	return v;
}

vector* cordic(double angle,const char *file_name){
	FILE *fp = fopen(file_name,"r");
	vector *v = create_vector(1 << 20,0);
	double ang_now = 0,theta = 0;
	unsigned long x = 0,y = 0;
	for(int i = 0;i < 20;i++){
		fscanf(fp,"%lf",&theta);
		if(ang_now < angle){
			x = v->x - (v->y >> i);
			y = (v->x >> i) + v->y;
			ang_now += theta;
		}else{
			x = v->x + (v->y >> i);
			y = -(v->x >> i) + v->y;
			ang_now -= theta;
		}
		v->x = x;
		v->y = y;
	}
	fclose(fp);
	return v;
}

double ator(double angle){
	return angle * PI / 180;
}

double rtoa(double angle){
	return angle * 180 / PI;
}

double my_sin(double ang){
	vector *v = cordic(ang,"theta.txt");
	return (double)(v->y) * K / (1 << 20);
}

double my_cos(double ang){
	vector *v = cordic(ang,"theta.txt");
	return (double)(v->x) * K / (1 << 20);
}

double my_tan(double ang){
	vector *v = cordic(ang,"theta.txt");
	return (double)(v->y) / v->x;
}

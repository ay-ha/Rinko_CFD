#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using std::endl;
using std::ofstream;

int main (){
	double V0; /*初速度*/ 
	double t0; /*開始時間*/
	double t; /*終了時刻*/
	double dt; /*時間刻み*/
	//double ang; /*角度 度*/
	//double u0,v0,x0,y0,u,v,x,y; 
	//double g=9.81; /*重力加速度*/
	int i;

	printf("初速度，終了時間，時間刻みを一マスあけて入力してください\n");
	scanf("%lf %lf %lf",&V0,&t,&dt);
	std::vector<double> f={-9.81,V0};
	std::vector<double> v={V0,0};
	std::vector<double> F={-9.81,0};//f*
	std::vector<double> v1={0,0};//v*

	ofstream ofs("hoin.csv");

	/*以下ルンゲクッタ法*/
	for(t0=0.0;t0<=t;t0=t0+dt){
		printf("t=%lf,v=%lf,y=%lf\n",t0,v[0],v[1]);
		ofs << t0 <<","<< v[0] <<","<< v[1] << endl;
		f[1]=v[0];
		for(i=0;i<2;i++){
			v1[i]=v[i]+dt/2*f[i];
			F[1]=v1[0];
			v[i]=v[i]+dt*F[i];
		}

	}
return 0;	
}


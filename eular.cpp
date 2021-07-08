#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
//#include "matplotlibcpp.h"
//namespace plt = matplotlibcpp;

using std::endl;
using std::ofstream;

int main (){
	double V0; /*初速度*/ 
	double t0; /*開始時間*/
	double t; /*終了時刻*/
	double dt; /*時間刻み*/
	/*double ang; 角度 度*/
	double g=9.81; /*重力加速度*/
	//std::vector<double> f(2);
	//std::vector<double> f={-9.81,V0};
	//std::vector<double> v(2);
	//std::vector<double> v={V0,0};
	int i;
	

	printf("初速度，終了時間，時間刻みを一マスあけて入力してください\n");
	scanf("%lf  %lf %lf",&V0,&t,&dt);
	std::vector<double> f={-9.81,V0};
	std::vector<double> v={V0,0};
	
    printf("%lf\n",v[0]);
	// u0=V0*cos(ang*3.14/180); /*x方向の初速度*/
	//v0=V0*sin(ang*3.14/180); /*y方向の初速度*/
	//x0=0; /*xの初期位置*/
	//y0=0; /*yの初期位置*/

	ofstream ofs("eular.csv");

	/*以下オイラー法*/
	for(t0=0.0;t0<=t;t0=t0+dt){
		printf("t=%lf,v=%lf,y=%lf\n",t0,v[0],v[1]);
		ofs << t0 <<","<< v[0] <<","<< v[1] << endl;
		f[1]=v[0];
		for(i=0;i<2;i++){
			v[i]=v[i]+dt*f[i];
		}
		//v=v+dt*f;
		//v[1]=v[1]+dt*f[1];
		


		//x=x0+u0*dt;
		//y=y0+v0*dt;
		//u=u0;
		//v=v0-g*dt;
		

		//x0=x;
		//y0=y;
		//u0=u;
		//v0=v;

		/*plt::plot(x,y);*/
    	/*plt::show();*/


	}
return 0;	
}

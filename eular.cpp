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
	double ang; /*角度 度*/
	double u0,v0,x0,y0,u,v,x,y;
	double g=9.81; /*重力加速度*/

	printf("初速度，角度，終了時間，時間刻みを一マスあけて入力してください\n");
	scanf("%lf %lf %lf %lf",&V0,&ang,&t,&dt);

	u0=V0*cos(ang*3.14/180); /*x方向の初速度*/
	v0=V0*sin(ang*3.14/180); /*y方向の初速度*/
	x0=0; /*xの初期位置*/
	y0=0; /*yの初期位置*/

	ofstream ofs("eular.csv");

	/*以下オイラー法*/
	for(t0=0.0;t0<=t;t0=t0+dt){
		printf("t=%lf,x=%lf,y=%lf\n",t0,x,y);
		x=x0+u0*dt;
		y=y0+v0*dt;
		u=u0;
		v=v0-g*dt;

		x0=x;
		y0=y;
		u0=u;
		v0=v;

		
		ofs << t0 <<","<< x <<","<< y << endl;

	}
return 0;	
}
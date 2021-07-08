#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using std::endl;
using std::ofstream;

#define Nx 10 //x方向の分割数
#define Nt 200 //時間の分割数

int main (){
	double a=1.0; /*熱拡散率*/ 
	double L=1.0; /*計算領域*/
	double z=0.5; /*計算時間*/
	double dt=z/Nt; /*時間刻み*/
	double dx=L/Nx; //空間刻み
    double T[Nx+1][Nt+1];
    double x[Nx+1];
    double t[Nt+1];
	int i,j;



	ofstream ofs("kakusann_eular.csv");

	/*座標*/
	for(i=0;i<=Nx;i++){
		x[i]=i*dx;
	}
	for(i=0;i<=Nt;i++){
		t[i]=i*dt;
	}
	//初期値
	for(i=0;i<=Nx;i++){
		T[i][0]=600*x[i]*(1-x[i])+300;
	}
	//オイラー法
	for(j=0;j<=Nt-1;j++){
		for(i=0;i<=Nx-1;i++){
			T[i][j+1]=T[i][j]+dt*a*(T[i+1][j]-2*T[i][j]+T[i-1][j])/(dx*dx);
			std::cout << T[i][j] << std::endl;
		}
		T[0][j+1]=300;
		T[Nx][j+1]=300;
	}
	//for(i=0;i<=Nx;i++){
	//	for(j=0;j<=Nt;j++){
	//		printf("x=%lf,t=%lf,%lf\n",x[i],t[i],T[i][j]);
	//	}
	//}
			// ofs << x[i] <<","<< t[i] <<","<< T[i][j] << endl;
		
	for(j=0;j<=Nt;j++){
		// ofs << x[10] <<","<< t[j] <<","<< T[10][j] << endl;
		printf("x=%lf,t=%lf,%lf\n",x[5],t[j],T[5][j]);
		ofs << x[5] <<","<< t[j] <<","<< T[5][j] << endl;
	}
	

		
return 0;	
}


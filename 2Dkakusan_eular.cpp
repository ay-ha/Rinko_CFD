#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using std::endl;
using std::ofstream;

#define N     50               /* 分割数   */
#define NEND  3000             /* ループ数 */
#define NSAVE 200              /* 出力間隔 */
#define L     1.0              /* 棒の長さ */
#define TEMP0 1500.0             /* 初期温度 */
#define TEMPL 1500.0            /* 境界温度(左) */
#define TEMPR 1500.0              /* 境界温度(右) */
#define K     1.0              /* 熱拡散率 */
#define DT    1.0e-4           /* 時間刻み */

int main(void)
{
    int i, j, n;
    double temp[N+1][N+1], temp1[N+1][N+1];
    double a, dt, dx, dy;
    char fname[256];
    FILE *fp;
    /* i       空間座標カウンタ
       n       時間カウンタ
       temp[]  温度
       temp1[] 温度(一時保存用)
       a   熱拡散率
       dt      時間刻み
       dx      空間刻み
       fname[] ファイル名
       fp      ファイルポインタ   */

    a = K;                       /* 熱拡散率の設定 */
    dt = DT;                               /* 時間刻みの設定 */
    dx = L / N;   
    dy = L /N;                         /* 空間刻みの設定 */
    for(i = 0; i <= N; i++) {
        for(j = 0; j <= N; j++){
            temp[i][j]=100.0;  /* 初期温度の設定 */
        }
    }
        /* 初期値のファイルへの出力 */
    if((fp = fopen("2Dkekka000.csv","wt")) == NULL) exit(1);
    for(i = 0; i <= N; i++) {
        for(j = 0; j <= N; j++) {
            fprintf(fp, "%g,%g,%g\n", dx * j, dy * i,temp[i][j]);
            std::cout << temp[i][j];
        }
    }
    fclose(fp);
    //ofstream ofs("kakusann_eular2.csv");
    for(n = 0; n < NEND; n++)
    {
        for(i = 1; i < N; i++){
            for(j = 1; j < N; j++){
                temp[20][30] = TEMPL;                 /* 左の境界条件の設定 */
                temp[40][10] = TEMPR;  
             /* 右の境界条件の設定 */
            }
        }
        /* 差分法(完全陽解法)による温度の計算 */
        for(i = 1; i < N; i++){
            for(j = 1; j < N; j++){
                temp[i][j] = temp[i][j] + a*dt*((temp[i][j+1]-2*temp[i][j]+temp[i][j-1])/(dx*dx) + (temp[i+1][j]-2*temp[i][j]+temp[i-1][j])/(dy*dy));
                //if (std::isnan(temp[i][j])) exit(1);
                //std::cout << temp[i][j];

            }
        }

        if((n + 1) % NSAVE == 0){    
        /* 途中結果のファイルへの出力 */
            sprintf(fname,"2Dkekka%03d.csv",(n + 1) / NSAVE);
            if((fp = fopen(fname,"wt")) == NULL) exit(1);

            for(i = 1; i <= N; i++) {
                fprintf(fp, "%g,", dx*i);
            }
            fprintf(fp, "\n");

            for(j = 1; j <= N; j++){
                fprintf(fp, "%g,", dy*j);
                for(i = 1; i <= N; i++){
                    fprintf(fp, "%e,", temp[i][j]);
                }
                fprintf(fp, "\n");

                //fprintf(fp, "%g,%g,%e\n", dx*j, dy*i, temp[i][j]);
                // std::cout << temp[i][j];
            }

    fclose(fp);
    }
    }
return 0;
}
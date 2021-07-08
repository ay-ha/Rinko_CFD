#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using std::endl;
using std::ofstream;

#define N     200         /* 分割数   */
#define NEND  3000        /* ループ数 */
#define NSAVE 20         /* 出力間隔 */
#define L     1.0         /* 棒の長さ */
#define TEMP0 0.0         /* 初期温度 */
#define TEMPL 0.0         /* 境界温度(左) */
#define TEMPR 0.0         /* 境界温度(右) */
#define K     1.00        /* 熱拡散率 */
#define DT    1.0e-5      /* 時間刻み */


int main(void)
{
    int i, j, n;            /* i,j 空間座標カウンタ, n 時間カウンタ */
    double temp[N+1][N+1];  /* temp[] 温度 */
    double temp1[N+1][N+1]; /* temp1[] 温度(一時保存用) */
    double a;               /* a 熱拡散率 */
    double dt, dx, dy;      /* dt 時間刻み, dx 空間刻み */
    char fname[256];        /* fname[] ファイル名 */
    FILE *fp;               /* fp ファイルポインタ */

    a = K;      /* 熱拡散率の設定 */
    dt = DT;    /* 時間刻みの設定 */
    dx = L/N;   /* 空間刻みの設定 */
    dy = L/N;   /* 空間刻みの設定 */
    for(i = 0; i <= N; i++){
        for(j = 0; j <= N; j++){
            temp[i][j] = 100.0;  /* 初期温度の設定 */
        }
    }

    /* 初期値のファイルへの出力 */
    if((fp = fopen("2Dkekka000.csv","wt")) == NULL) exit(1);
    for(i = 1; i <= N; i++){
        fprintf(fp, "%g,", dx*i);
    }
    fprintf(fp, "\n");

    for(j = 1; j <= N; j++){
        fprintf(fp, "%g,", dy*j);
        for(i = 1; i <= N; i++){
            fprintf(fp, "%e,", temp[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    for(n = 0; n < NEND; n++){
        std::cout << "n = " << n << "\n";
        temp[N][N] = TEMPL;  /* 左の境界条件の設定 */
        temp[N][N] = TEMPR;  /* 右の境界条件の設定 */
        for(i=0; i<N; i++) {
            //temp[0][i]=TEMPL;
            //temp[N][i]=TEMPL;
            //temp[i][0]=TEMPR;
           // temp[i][N]=TEMPR;
            temp[i][N/2]=1000;
        }
        /* 差分法(完全陽解法)による温度の計算 */
        for(i = 1; i < N; i++){
            for(j = 1; j < N; j++){
                temp[i][j] = temp[i][j] + a*dt*((temp[i][j+1]-2*temp[i][j]+temp[i][j-1])/(dx*dx) + (temp[i+1][j]-2*temp[i][j]+temp[i-1][j])/(dy*dy));
            }
        }

        /* 途中結果のファイルへの出力 */
        if((n + 1) % NSAVE == 0){
            sprintf(fname,"2Dkekka%03d.csv",(n + 1) / NSAVE);
            if((fp = fopen(fname,"wt")) == NULL) exit(1);

            for(i = 1; i <= N; i++){
                fprintf(fp, "%g,", dx*i);
            }
            fprintf(fp, "\n");

            for(j = 1; j <= N; j++){
                fprintf(fp, "%g,", dy*j);
                for(i = 1; i <= N; i++){
                    fprintf(fp, "%e,", temp[i][j]);
                }
                fprintf(fp, "\n");
            }
        fclose(fp);
        }
    }
    return 0;
}

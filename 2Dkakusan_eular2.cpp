#if defined(__STDC__) || defined(ANSI) || defined(NRANSI) /* ANSI */

#include <stdio.h>
#include <stdlib.h>
#define NR_END 1
#define FREE_ARG char*


void nrerror(char error_text[])
/* Numerical Recipes standard error handler */
{
    fprintf(stderr,"Numerical Recipes run-time error...\n");
    fprintf(stderr,"%s\n",error_text);
    fprintf(stderr,"...now exiting to system...\n");
    exit(1);
}
/* double型の2次元配列をオフセット化&ポインタの配列へのポインタ変換 */
double **dmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix with subscript range m[nrl..nrh][ncl..nch] */
{
    long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
    double **m;

    /* allocate pointers to rows */
    m=(double **) malloc((size_t)((nrow+NR_END)*sizeof(double*)));
    if (!m) nrerror("allocation failure 1 in matrix()");
    m += NR_END;
    m -= nrl;

    /* allocate rows and set pointers to them */
    m[nrl]=(double *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
    if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
    m[nrl] += NR_END;
    m[nrl] -= ncl;

    for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

    /* return pointer to array of pointers to rows */
    return m;
}
#endif /* ANSI */


#define DT 1e-4
#define DX 1e-1
#define DY 1e-1
#define latT 100
#define latY 100
#define TEMP0 25
#define TEMP1 300
#define NEND 2000
#define NSAVE 20
#define D 20



int main(void){
    /* i:行　j:列　n:ループ回数 */
    int i, j, n;


   /* 温度の宣言 */
   double **temp, **ntemp;
   temp=dmatrix(0, latT+1, 0, latY+1);/* 境界条件を考えるために余分に一回り大きい行列を考える */
   ntemp=dmatrix(0, latT+1, 0, latY+1);

    /* 残りの変数の定義 */
    char fname[256]; 
    int a=0, b=100;/* 熱源の座標 */
    int c=100, d=0;
    double a = D;/* 拡散係数 */
    double dx=DX,dy=DY,dt=DT; /* 各微小量 */


    /* 各格子点の温度の初期化 */
    for(i = 0; i <= latT+1; i++){
        for(j =0; j <= latY+1; j++){
            temp[i][j] = TEMP0;
            if(i==a && j==b) temp[i][j] = TEMP1;
            if(i==c && j==d) temp[i][j] = TEMP1;
            //printf("%d, %d, %g\n",i, j, temp[i][j]);
        }
    }

    /* 初期値の書き込み */
    FILE *fp;
    if((fp = fopen("2D2kekka000.csv","wt")) == NULL) exit(1);/* if の中でfpを定義してかつfopenしている？*/
    for(i = 1; i <= latT; i++){
        for(j =1; j <= latY; j++){
            fprintf(fp, "%g,%g,%g\n", dx*j, dy*i, temp[i][j]); ///dxを１としたときにおかしい値になったので1.0と置いた
        }
        fprintf(fp, "\n"); /* 改行を入れないとgnuがエラーを吐く */
    }
    fclose(fp);


    for(n=1;n<=NEND;n++){
        /* 熱源を設置 */
        temp[a][b] = TEMP1;
        temp[c][d] = TEMP1;

        /* 境界条件(自由端)の更新 各頂点は計算過程に影響しないので無視 */ 
        for(i=1;i<=latT;i++){
            temp[i][0] = temp[i][1];
            temp[i][latY+1] = temp[i][latY];
        }
        for(j=1;j<=latY;j++){
            temp[0][j] = temp[1][j];
            temp[latT+1][j] = temp[latT][j];
        }

        /* 差分法のFTCSによる計算 ここで、(a,b)の温度は一定であることに注意する。*/
        for(i=1;i<=latT;i++){
            for(j=1;j<=latY;j++){
                if(i==a && j==b) ntemp[i][j] = TEMP1;
                else if(i==c && j==d) ntemp[i][j] = TEMP1; 
                else{ntemp[i][j] = temp[i][j] +/* jがx, iがyに対応していることに注意する */
                    a*((temp[i][j+1] -2*temp[i][j] + temp[i][j-1])/(dx * dx) +
                            (temp[i+1][j] -2*temp[i][j] + temp[i-1][j])/(dy * dy)
                    ) * dt;
                }                
            }
        }

        /* 温度の更新 */
        /* 各格子点の温度の初期化 */
        for(i = 0; i <= latT+1; i++){
            for(j =0; j <= latY+1; j++){
                temp[i,j] = ntemp[i,j];
                if(i==a && j==b && (n%NSAVE==0 || n==0)) printf("T(%g,%g) = %g\n",j*dx,i*dy, temp[i][j]);
            }
        }

        /* csvへの書き込み */
        if(n%NSAVE==0){
            sprintf(fname,"2D2kekka%03d.csv",n / NSAVE); /* fname[] にファイル名を代入 */
            if((fp = fopen(fname,"wt")) == NULL) exit(1);
            for(i = 1; i <= latT; i++){
                for(j =1; j <= latY; j++){
                fprintf(fp, "%g,%g,%g\n", dx*j, dy*i, temp[i][j]); 
                }
                fprintf(fp, "\n");
            }
            fclose(fp);
        }
    }

    return 0;
    }
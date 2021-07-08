#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using std::endl;
using std::ofstream;

#define N     101         /* x方向分割数*/
#define M     101         /*y方向分割数*/
#define LIMIT  10000        /* 反復回数 */
#define BUFSIZE 256       /*入力バッファ用配列の長さ*/
#define ERROR -1          /*入力時のエラーコード*/

int getuij(double u[][M]);
void putuij(double u[][M]);
void iteration(double u[][M]);
int getdouble(double *x);

int main(void)
{
    int i;
    double u[N][M];

    if(getuij(u)!=0){
        fprintf(stderr,"初期値読み込み失敗\n");
        exit(1);
    }

/*反復法の計算*/
    for(i=0;i<LIMIT;i++){
        iteration(u);
        if((i%(LIMIT/10))==0){
            printf("i=%d\n",i);
            putuij(u);
            printf("\n");
        }
    }

    putuij(u); /*結果出力*/

    return 0;
}

void iteration(double u[][M])
{
    double u_next[N][M];
    int i,j;

//次ステップの値を計算
    for (i=1;i<N-1;i++){
        for(j=1;j<M-1;j++){
            u_next[i][j]=(u[i][j-1]+u[i-1][j]+u[i+1][j]+u[i][j+1])/4;
        }
    }
//uijの更新
    for(i=1;i<N-1;i++){
        for(j=1;j<M-1;j++){
            u[i][j]=u_next[i][j];
        }
    }
}

void putuij(double u[][M])
{
    int i,j;

    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
           printf("%lf",u[i][j]); 
        }
        printf("\n");
    }
}

int getuij(double u[][M])
{
    int i,j;

    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            if(getdouble(&u[i][j])==EOF ){
                fprintf(stderr,"%d %d",i,j);
                return ERROR;
            }
        }
    }
    return 0;
}

int getdouble(double *x)
{
    char linebuf[BUFSIZE];
    int result=0;

    if(fgets(linebuf,BUFSIZE,stdin)!=NULL){
        if(sscanf(linebuf,"%lf",x)<=0){
            result=EOF;
        }
        else{
            result=EOF;
        }
    }
    return result;
}
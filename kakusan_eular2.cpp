#include <stdio.h>
#include <stdlib.h>

#define N     50               /* 分割数   */
#define NEND  2000             /* ループ数 */
#define NSAVE 200              /* 出力間隔 */
#define L     1.0              /* 棒の長さ */
#define TEMP0 1500.0             /* 初期温度 */
#define TEMPL 300.0            /* 境界温度(左) */
#define TEMPR 300.0              /* 境界温度(右) */
#define K     1.0              /* 熱拡散率 */
#define DT    1.0e-4           /* 時間刻み */

int main(void)
{
  int i, n;
  double temp[N+1], temp1[N+1];
  double kappa, dt, dx;
  char fname[256];
  FILE *fp;
  /* i       空間座標カウンタ
     n       時間カウンタ
     temp[]  温度
     temp1[] 温度(一時保存用)
     kappa   熱拡散率
     dt      時間刻み
     dx      空間刻み
     fname[] ファイル名
     fp      ファイルポインタ   */

  kappa = K;                             /* 熱拡散率の設定 */
  dt = DT;                               /* 時間刻みの設定 */
  dx = L / N;                            /* 空間刻みの設定 */
  for(i = 0; i <= N; i++) temp[i]=1500.0;  /* 初期温度の設定 */
  /* 初期値のファイルへの出力 */
  if((fp = fopen("kekka000.csv","wt")) == NULL) exit(1);
  for(i = 0; i <= N; i++) fprintf(fp, "%g,%g\n", dx * i, temp[i]);
fclose(fp);

  for(n = 0; n < NEND; n++)
  {
    temp[0] = TEMPL;                 /* 左の境界条件の設定 */
    temp[N] = TEMPR;                 /* 右の境界条件の設定 */
    /* 差分法(完全陽解法)による温度の計算 */
    for(i = 1; i < N; i++) 
      temp1[i] = temp[i] 
        + kappa * dt * (temp[i+1] - 2 * temp[i] + temp[i-1]) / (dx * dx); 
    /* 温度の更新 */
    for(i = 1; i < N; i++) temp[i] = temp1[i];
    if((n + 1) % NSAVE == 0)
{
      /* 途中結果のファイルへの出力 */
      sprintf(fname,"kekka%03d.csv",(n + 1) / NSAVE);
if((fp = fopen(fname,"wt")) == NULL) exit(1);
      for(i = 0; i <= N; i++) fprintf(fp, "%g,%g\n", dx * i, temp[i]);
fclose(fp);
    }
  }
}
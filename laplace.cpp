#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <array>

#define maxx 40                         /* number of grid points */
#define maxy 40                         /* number of grid points */
#define L 1.0

int main()
{

    double pnew;
    int i, j, iter;
    double dx,dy;
    dx = L / maxx;
    dy = L / maxy;

    std::array<std::array<double,maxx>,maxy> arr;
    //arr.fill(0.0);
    std::ofstream outputfile("laplace.csv");

    for(i=0; i<maxx; i++)                 /* clear the array  */
    {
        for (j=0; j<maxy; j++) 
        {
            arr[i][j] = 0;
        }
    }

    for(i=0; i<maxx; i++) 
    {
        for(j=0; j<maxy; j++)
        {
            arr[i][0] = 100.0;        /* p[i][0] = 100 V */  
            arr[0][j] = 100.0;
            arr[i][maxx-1] = 100.0;
            arr[maxx-1][j] = 100.0;
        }
    }
    
    for(iter=0; iter<1000; iter++)               /* iterations */
    {
        for(i=1; i<(maxx-1); i++)                  /* x-direction */
        {
            for(j=1; j<(maxy-1); j++)               /* y-direction */
            {
                pnew = (arr[i+1][j]+arr[i-1][j]+arr[i][j+1]+arr[i][j-1])/4;
                arr[i][j] = pnew; 
            }
        }
    }  
    for(i = 0; i < maxx; i++)
    {
        outputfile << dx*i << ",";
    }
    outputfile << std::endl;
    for (j=0; j<maxy ; j++)         
    {
        outputfile << dy*j << ",";
        for (i=0; i<maxx; i++) 
        {
             outputfile << arr[i][j] << ",";
         } 
        outputfile << std::endl;      /* empty line for gnuplot */
    }
    outputfile.close();
}
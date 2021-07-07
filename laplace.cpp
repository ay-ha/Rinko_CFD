#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>

#define maxx 40                         /* number of grid points */
#define maxy 40                         /* number of grid points */
#define L 1.0

int main()
{

    double p[maxx][maxy], pnew;
    int i, j, iter;
    double dx,dy;
    dx = L / maxx;
    dy = L / maxy;

    std::ofstream outputfile("laplace.csv");

    for(i=0; i<maxx; i++)                 /* clear the array  */
    {
        for (j=0; j<maxy; j++) 
        {
            p[i][j] = 0;
        }
    }

    for(i=0; i<maxx; i++) 
    {
        for(j=0; j<maxy; j++)
        {
            p[i][0] = 100.0;        /* p[i][0] = 100 V */  
            p[0][j] = 100.0;
            p[i][39] = 100.0;
            p[39][j] = 100.0;
        }
    }
    
    for(iter=0; iter<1000; iter++)               /* iterations */
    {
        for(i=1; i<(maxx-1); i++)                  /* x-direction */
        {
            for(j=1; j<(maxy-1); j++)               /* y-direction */
            {
                pnew = (p[i+1][j]+p[i-1][j]+p[i][j+1]+p[i][j-1])/4;
                p[i][j] = pnew; 
            }
        }
    }  
    for(i = 1; i <= maxx; i++)
    {
        outputfile << dx*i << ",";
    }
    outputfile << std::endl;
    for (j=0; j<maxy ; j++)         
    {
        outputfile << dy*j << ",";
        for (i=0; i<maxx; i++) 
        {
             outputfile << p[i][j] << ",";
         } 
        outputfile << std::endl;      /* empty line for gnuplot */
    }
    outputfile.close();
}
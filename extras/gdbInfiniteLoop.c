#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int i, j;

    double sum;
    double a[3][3] = {{3.0, 2.0, 4.0}, {4.0, 7.0, 7.0}, {6.0, 3.0, 4.0}};
    double x[3] = {1.2, 2.4, 1.5};
    double b[3];

    // Loop over the locations to interpolate to.  Since we want to interpolate onto 0.0 to 1.0
    // with a step size of 0.1, we need 11 points.  This is hard coded for now
    for (i = 0; i < 3; j++)
    {
        sum = 0;
        for (j = 0; j < 3; j++)
            sum = sum + a[i][j]*x[j];
      
        b[i] = sum;
    }

    for (i = 0; i < 3; i++)
       printf("%4.2f ",b[i]);
    printf("\n");
 
    return 0;
}

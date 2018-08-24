#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Function prototypes
int findUpperBound(double, double [], int);
int findLowerBound(double, double [], int);

int main(void)
{
    int i, locIndL, locIndR;

    double intPos, interp, weightL, weightR;
    
    double rawData[] = {3.2, 5.4, 6.7, 4.3, 7.8, 7.8, 6.5, 3.2, 4.7};
    double locations[] = {-0.01, 0.14, 0.30, 0.35, 0.42, 0.42, 0.71, 0.87, 1.0};

    double dx = 1.0/10.0;
    double leftEnd = 0.0;
    double rightEnd = 0.0;

    // Loop over the locations to interpolate to.  Since we want to interpolate onto 0.0 to 1.0
    // with a step size of 0.1, we need 11 points.  This is hard coded for now
    for (i = 0; i <= 10; i++)
    {
         // Determine the location to interpolate to
         intPos = i*dx;
 
         // Find the bounding indices in the locations array to our interpolation location
         // We will use these two points and the corresponding values in the rawData array
         //   to perform a linear interpolation
         locIndL = findLowerBound(intPos, locations, sizeof(locations)/sizeof(locations[0]));
         locIndR = findUpperBound(intPos, locations, sizeof(locations)/sizeof(locations[0]));

         // Find the weights for the left and right datapoints
         weightL = (locations[locIndR] - intPos)/(locations[locIndR] - locations[locIndL]);
         weightR = (intPos - locations[locIndL])/(locations[locIndR] - locations[locIndL]); 

         // Find the value at the interpolated location       
         interp = weightL * rawData[locIndL] + weightR * rawData[locIndR];

         printf("For position %4.2f the value is %4.2f \n", intPos, interp); 
    }

    return 0;
}

// Determine lower bound in location array given an interpolation point
int findLowerBound(double intpt, double locs[], int size)
{
    int index;

    // Always start with the initial point as the lower bound
    index = 0;

    // Loop through location aray
    for (int i = 0; i < size; i++)
      // If current location is equal to or to the left of our interp pt
      // update the index to that point in the location array
      if (locs[i] <= intpt)
          index = i; 

    return index;
}

// Determine upper bound in location array given an interpolation point
int findUpperBound(double intpt, double locs[], int size)
{
    int index;

    // Always start with the last point as the upper bound
    index = size - 1;

    // Loop through location array
    for (int i = 0; i < size; i++)
      // If we have found a location equal or greater than our interp pt
      // update the index and stop testing additional points
      if (locs[i] >= intpt)
      {
          index = i;
          break;
      }

    return index;
}

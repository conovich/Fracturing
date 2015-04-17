#include "nearlyEqual.h"

bool nearlyEqual(float a, float b) 
{
	 const float epsilon = 0.0015f;
     const float absA = fabs(a);
     const float absB = fabs(b);
     const float diff = fabs(a - b);

     if (a == b) 
	 { // shortcut
       return true;
     } 
	 else if (a * b == 0) 
	 { // a or b or both are zero
            // relative error is not meaningful here
            return diff < (epsilon * epsilon);
     } 
	 else 
	 { // use relative error
            return diff / (absA + absB) < epsilon;
     }
}

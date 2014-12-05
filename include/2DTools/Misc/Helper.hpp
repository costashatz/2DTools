#ifndef HELPER_HPP
#define HELPER_HPP
#include <limits>
#define minimum(x,y) (x>y)?x:y

namespace Tools2D {

const double Pi = 3.14159265358979323846264338327950288419716939937510;
const double   TwoPi     = Pi * 2;
const double   HalfPi    = Pi / 2;
const double   QuarterPi = Pi / 4;

double RadiansToDegrees(double rad)
{
    return rad*(180.0/Pi);
}

double DegreesToRadians(double deg)
{
    return deg*(Pi/180.0);
}

}

#endif

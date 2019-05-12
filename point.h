#ifndef POINT_
#define POINT_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

#define EPS 1e-9

using namespace std;

class point
{
    public:
        double x,y,z;
        point();
        point(double, double, double);
        point(FILE *fin);
        point(const point &a);
        point &operator =(const point& a);
        point operator +(const point& a);
        point operator -(const point& a);
        int scan(FILE *fin);
        int operator==(point& a);
        point projection(point norm, point p);
};

#endif

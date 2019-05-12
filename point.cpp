#include "point.h"

point::point(){}

point::point(double x_, double y_, double z_)
{
    x=x_;
    y=y_;
    z=z_;
}

point::point(FILE *fin)
{
    scan(fin);
}

point::point(const point &a)
{
    x=a.x;
    y=a.y;
    z=a.z;
}

int point::scan(FILE *fin)
{
    return fscanf(fin,"%lf%lf%lf",&x,&y,&z);
}

point &point::operator =(const point& a)
{
    x=a.x;
    y=a.y;
    z=a.z;
    return (*this);
}

point point::operator +(const point& a)
{
    point res;
    res.x=x+a.x;
    res.y=y+a.y;
    res.z=z+a.z;
    
    return res;
}

point point::operator -(const point& a)
{
    point res;
    res.x=x-a.x;
    res.y=y-a.y;
    res.z=z-a.z;
    
    return res;
}

int point::operator==(point& a)
{
    return (int)((fabs(a.x-x)<EPS) && (fabs(a.y-y)<EPS) && (fabs(a.z-z)<EPS));
}

point point::projection(point norm, point p)
{
   double q = (p.x*norm.x + p.y*norm.y + p.z*norm.z)/(norm.x*norm.x + norm.y*norm.y + norm.z*norm.z);   
   
   return point(x+norm.x*q,y+norm.y*q,z+norm.z*q);
}

#ifndef HEADER_
#define HEADER_

#include "point.h"

struct segment
{
    point a,b;
    int n_a,n_b;
    double weight;
};

class contour
{
    public:
    vector<segment> sgs;
    vector<point> conv;
    point norm;
    int ind;
    int id;
    int is_bad;
    
    contour();
    contour(const char * txt);
    void parse(const char * txt);
    void to_conv();
};

struct facet
{
    double a,b,c,d;
    vector<int> ind_of_vert;
};

struct edge
{
    int id1,id2,facet_id,ind_in_list;
};

struct poly
{
    vector<point> vertices;
    vector<facet> facets;
    vector<edge> edges;
};

void parse_poly(poly *p);        
    

/*
 *  a - current point,
 *  b - rightmost point,
 *  c - candidate
 */

double sign_of_sc_mult(point a, point b, point c, point norm);

#endif
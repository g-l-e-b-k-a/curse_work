#include "lib.h"

int main()
{
    FILE *fin,*fout;
    char name[50];
    poly p;
    
    vector<contour> arr_contour;
    
    fin=fopen("files.txt","r");
    fout=fopen("gp.sh","w");
    fprintf(fout,"#!/bin/bash\ngnuplot << EOP\nset terminal jpeg size 640,480\n");
    
    while(fscanf(fin,"%s",name)==1)
    {
        arr_contour.push_back(contour(name));
        fprintf(fout,"set output 'imgs/%s.jpg'\nsplot 'data/%s' with lines, 'conv/%s' with lines, 'norms/%s' using 1:2:3:4:5:6 with vectors filled head lw 3\n",name,name,name,name);
    }
    
    fprintf(fout,"EOP");
    fclose(fout);
    
    parse_poly(&p);
    
    fclose(fin);
    return 0;
}
#include "lib.h"

contour::contour(){}

contour::contour(const char * txt)
{
    parse(txt);
}

void contour::parse(const char * txt)
{
    FILE *fin, *fout;
    char name[500];
    segment buf;
    vector<point> jarvis;
    
    sprintf(name,"data/%s",txt);
    fin=fopen(name,"r");
    
    if(fscanf(fin,"# reflect cont ind %d  id %d",&ind,&id)!=2)
    {
        printf("Error in read 1-st string\n");
        fclose(fin);
        return;
    }
    
    if(fscanf(fin,"\n#  norm    %lf    %lf    %lf",&norm.x,&norm.y,&norm.z)!=3)
    {
        printf("Error in read 2-st string\n");
        fclose(fin);
        return;
    }
    
    printf("Norm of ind=%d id=%d: %f %f %f\n",ind,id,norm.x,norm.y,norm.z);
    
    
    while(fscanf(fin,"\n# vert  %d  %d   weight %lf",&buf.n_a,&buf.n_b,&buf.weight)==3)
    {
        buf.a.scan(fin);
        buf.b.scan(fin);
        sgs.push_back(buf);
    }
    fclose(fin);
    
    sprintf(name,"norms/reflect%03d_id%03d",ind,id);
    fout=fopen(name,"w");
    fprintf(fout,"%f %f %f %f %f %f\n",buf.a.x,buf.a.y,buf.a.z,norm.x,norm.y,norm.z);
    fclose(fout);
    
    to_conv();
    sprintf(name,"conv/reflect%03d_id%03d",ind,id);
    fout=fopen(name,"w");
    for(int i=0;i<conv.size();i++)
        fprintf(fout,"%f %f %f\n",conv[i].x,conv[i].y,conv[i].z);
    fclose(fout);
    
}

double sign_of_sc_mult(point a, point b, point c, point norm)
{
    point q;
    double res;
    
    a=b-a;
    b=c-b;
    
    q.x=a.y*b.z-a.z*b.y;
    q.y=a.z*b.x-a.x*b.z;
    q.z=a.x*b.y-a.y*b.x;
    
    return q.x*norm.x+q.y*norm.y+q.z*norm.z;
}

void contour::to_conv()
{
    vector<point> buf;
    int j,right;
    int ind_start=-1;
    
    conv.clear();
    for(int i=0;i<sgs.size();i++)
    {
        point q=sgs[i].a;
        for(j=0;j<buf.size();j++)
            if(buf[j]==q) break;
        if(j==buf.size())
        {
            if(ind_start>-1 && buf[ind_start].z<q.z)
                ind_start=j; 
            else if(ind_start==-1) ind_start=0;
            buf.push_back(q);
        }
        
        q=sgs[i].b;
        for(j=0;j<buf.size();j++)
            if(buf[j]==q) break;
        if(j==buf.size())
        {
            if(ind_start>-1 && buf[ind_start].z<q.z)
                ind_start=j; 
            else if(ind_start==-1) ind_start=0;
            buf.push_back(q);
        }
    }
    
    conv.push_back(buf[ind_start]);
    buf.erase(buf.begin()+ind_start);
    buf.push_back(conv[0]);
    
    while(1)
    {
        right = 0;
        for(int i=0;i<buf.size();i++)
            if (sign_of_sc_mult(conv[conv.size()-1],buf[right],buf[i],norm)<0.)
                right = i;
        if (buf[right]==conv[0]) 
            break;
        else
        {
            conv.push_back(buf[right]);
            buf.erase(buf.begin()+right);
        }
    }
    
    conv.push_back(conv[0]);
}

void parse_poly(poly *p)
{
    int num_of_vertices,num_of_facets,num_of_edges;
    FILE *fin;
    
    fin=fopen("data/poly-init.dat", "r");
    
    fscanf(fin,"# WPolyhedron::Dump:");
    if(fscanf(fin,"\n# num_vertices   num_facets   num_edges %d%d%d",&num_of_vertices,&num_of_facets,&num_of_edges)!=3) printf("Error\n");
    
    fscanf(fin,"\n# vertices:");
    fscanf(fin,"\n#   id   x y z");
    for(int i=0;i<num_of_vertices;i++)
    {
        point a;
        int id;
        if(fscanf(fin,"%d%lf%lf%lf",&id,&a.x,&a.y,&a.z)!=4){ printf("Error1 %d\n",i); break;}
        p->vertices.push_back(a);
    }
    
    fscanf(fin,"\n# facets:");
    fscanf(fin,"\n#   id   num_of_sides   plane_coeff  (ax + by + cz + d = 0)");
    fscanf(fin,"\n#   indices_of_vertices");
    for(int i=0;i<num_of_facets;i++)
    {
        facet a;
        int id, num_of_vert;
        if(fscanf(fin,"%d%d%lf%lf%lf%lf",&id,&num_of_vert,&a.a,&a.b,&a.c,&a.d)!=6){ printf("Error2\n"); break;}
        for(int j=0;j<num_of_vert;j++)
        {
            if(fscanf(fin,"%d",&id)!=1){ printf("Error3\n"); break;}
            a.ind_of_vert.push_back(id);
        }
        p->facets.push_back(a);
    }
    
    fscanf(fin,"\n# edges:");
    fscanf(fin,"\n#    vert1_id  vert2_id  facet_id  ind_in_list");
    for(int i=0;i<num_of_edges;i++)
    {
        edge a;
        int id;
        if(fscanf(fin,"%d%d%d%d",&a.id1,&a.id2,&a.facet_id,&a.ind_in_list)!=4){ printf("Error4\n"); break;}
        p->edges.push_back(a);
    }
}
    
    
    
    


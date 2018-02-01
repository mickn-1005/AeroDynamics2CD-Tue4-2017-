#ifndef   KARMAN_H
#define KARMAN_H

#include <cmath>
#include <vector>

using namespace std;

const float u_0 = 1.0;  //U_infty

/*
definition about grid...
*/
float L = 1.0;   // cube length [m]
float LX = 10.0;   //calculation range for x axis(No dimention)
float LY = 30.0;
int mdx = 500; //how many meshes
int mdy = 300;
int mx = 400; //
int my = 200;
int cx1 = 95;  // set vertex of cube
int cx2 = 105;
int cy1 = 95;
int cy2 = 105;
int icent = (int)((cx1+cx2)*0.5); //center of cube (coordinate origin)
int jcent = (int)((cy1+cy2)*0.5);
float dx = L/((float)(cx2-cx1));  // x axis mesh range[m]
float dy = L/((float)(cy2-cy1));  // y axis mesh range[m]

vector< vector<float> > u;    // verocity grid
vector< vector<float> > v;
vector< vector<float> > x;    //make axis
vector< vector<float> > y;
vector< vector<float> > p;

/*
definition about flow...
*/
float re = 70.0; //Reynolds number
float cfl = 0.2; //CFL number (define delta_t)
// SOR parameters (about pressure field)
float omegap = 1.0;     //?????????
float maxitp = 10000;
float errorp = pow(10.0,-4.0);
//time steps
float t_0 = 0.0;
float simu_time;
int nbegin = 0;
int nlast = 10000;
int nlp = 10;
float resp;
float itrp;

float cd=0.0;
float cl=0.0;


#endif    //KARMAN_H
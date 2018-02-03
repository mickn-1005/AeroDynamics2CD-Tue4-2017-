#ifndef   KARMAN_H
#define KARMAN_H

#include <cmath>
#include <vector>

using namespace std;

const float u_0 = 1.0;  //U_infty

/*
definition about grid...
*/
const float L = 1.0;   // cube length [m]
const float LX = 10.0;   //calculation range for x axis(No dimention)
const float LY = 30.0;
const int mdx = 500; //how many meshes
const int mdy = 300;
const int mx = 400; //
const int my = 200;
const int cx1 = 95;  // set vertex of cube
const int cx2 = 105;
const int cy1 = 95;
const int cy2 = 105;

// const int cx1 = 95;  // set vertex of cube
// const int cx2 = 105;
// const int cy1 = 85;
// const int cy2 = 95;

const int px1 = 145;
const int px2 = 155;
const int py1 = 95;
const int py2 = 105;
const int qx1 = 195;
const int qx2 = 205;
const int qy1 = 95;
const int qy2 = 105;

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

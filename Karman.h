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
const int mx = 600; //
const int my = 200;
const int cx1 = 95;  // set vertex of cube
const int cx2 = 105;
const int cy1 = 95;
const int cy2 = 105;

int px1 = 295;    // another cubes
int px2 = 305;
int py1 = 95;
int py2 = 105;
int qx1 = 195;
int qx2 = 205;
int qy1 = 95;
int qy2 = 105;

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
const float re = 70.0; //Reynolds number
const float cfl = 0.2; //CFL number (define delta_t)
// SOR parameters (about pressure field)
const float omegap = 0.9;     //?????????
const float maxitp = 5000;
const float errorp = pow(10.0,-4.0);
//time steps
float t_0 = 0.0;
float simu_time;
int nbegin = 0;
const int nlast = 10;
int nlp = 10;
float resp;
float itrp;

float cd=0.0;
float cl=0.0;


#endif    //KARMAN_H

#include <iostream>
#include "cond_solver.cpp"
#include "postprocess.cpp"

/*
initialize verocity and axis
*/
int set_grids(void){
  int icent = (int)((cx1+cx2)*0.5); //center of cube (coordinate origin)
  int jcent = (int)((cy1+cy2)*0.5);

  x.resize(mx+1);   //mx -> abort trap
  y.resize(mx+1);
  u.resize(mx+1);
  v.resize(mx+1);
  p.resize(mx+1);
  for(int i = 0; i < mx+1; i++){
    x[i].resize(my+1);
    y[i].resize(my+1);
    u[i].resize(my+1);
    v[i].resize(my+1);
    p[i].resize(my+1);
  }

  simu_time = t_0;

  for(int i = 0; i<mx+1; i++){    // set coordinate
    for(int j=0; j < my+1; j++){
      x[i][j] = dx * (i-icent);
      y[i][j] = dy * (j-jcent);
      u[i][j] = 1.0;
      v[i][j] = 0.0;
      p[i][j] = 0.0;
    }
  }
  return 0;
}

/*
solve flow...
*/
int flow_solve(void){
  float dt = cfl * min(dx, dy) / u_0; // time step from CFL condition

  std::cout << "------Comp. condition------" << '\n';
  std::cout << "CFL = " <<cfl<< '\n' << "dt  = " <<dt<< '\n';
  std::cout << nlast << "time steps to go..." << '\n';
  std::cout << "------Incompressible Flow Solver------" << '\n';
  std::cout << "Re = " << re << '\n';
  std::cout << "No. of Grid points (mx, my) = (" << mx << ", " << my << ")" << '\n';
  std::cout << "Grid parameters (dx,dy) = " << dx << "," << dy << '\n';
  std::cout << "--------------------------------------" << '\n';

  bound_p();
  bound_v();

  float cp1,cp2;

  for(int n=nbegin; n<nlast+1; n++){
    if(n%1 ==0){
      csvout(n);
    }
    poiseq(dt);
    bound_p();
    veloeq(dt);
    bound_v();

    if(n%1 ==0){
      cp1 = p[2*cx1-cx2][cy1];
      cp2 = p[2*cx1-cx2][cy2];
      std::cout << "itr No.//resp//itrp//cd//cl//cp1//cp2   ::  " <<
                  n << "," << resp << "," << itrp  << "," << cd << "," << cl << "," << cp1 << "," << cp2 << '\n';
    }
  }

  /*
  calculate Cd, Cl
  */
  float cpfore;
  float cpback;
  float cpbtm;
  float cptop;

  for(int  j=cy1; j<cy2+1; j++){
    cpfore = (2.0*p[cx1][j]+2.0*p[cx1][j+1])/2.0;
    cpback = (2.0*p[cx2][j]+2.0*p[cx2][j+1])/2.0;
    cd += (cpfore-cpback)*dy;
  }

  for(int i=cx1; i<cx2+1; i++){
    cptop = (2.0*p[i][cy2]+2.0*p[i+1][cy2])/2.0;
    cpbtm = (2.0*p[i][cy1]+2.0*p[i+1][cy2])/2.0;
    cl += (cpbtm-cptop)*dx;
  }

  return 0;
}

#include <iostream>
#include <cmath>

int bound_p(void){
  for(int j=0; j<my+1; j++){
    p[0][j] = 0.0;    // inflow condition
    p[mx][j] = 0.0;   // downstream condition
  }
  for(int i=0; i<mx+1; i++){
    p[i][0] = 0.0;    // bottom condition
    p[i][my] = 0.0;   // bottom condition
  }

  p[cx1][cy1] = p[cx1-1][cy1-1];    //wall condition
  p[cx1][cy2] = p[cx1-1][cy2+1];
  p[cx2][cy1] = p[cx2+1][cy1-1];
  p[cx2][cy2] = p[cx2+1][cy2+1];

  for(int j=cy1+1; j<cy2; j++){
    p[cx1][j] = p[cx1-1][j];
    p[cx2][j] = p[cx2+1][j];
  }
  for(int i=cx1+1; i<cx2; i++){
    p[i][cy1] = p[i][cy1-1];
    p[i][cy2] = p[i][cy2+1];
  }

  return 0;
}

int bound_v(void){
  for(int j=0; j<my+1; j++){
    u[0][j] = u_0;    //inflow condition
    v[0][j] = 0.0;
    u[1][j] = u_0;
    v[1][j] = 0.0;
    u[mx-1][j] = 2.0*u[mx-2][j] - u[mx-3][j];
    v[mx-1][j] = 2.0*v[mx-2][j] - v[mx-3][j];
    u[mx][j] = 2.0*u[mx-1][j] - u[mx-2][j];
    v[mx][j] = 2.0*v[mx-1][j] - v[mx-2][j];
  }

  for(int i=0; i<mx+1; i++){
    u[i][1] = 2.0*u[i][2] - u[i][3];
    v[i][1] = 2.0*v[i][2] - v[i][3];
    u[i][0] = 2.0*u[i][1] - u[i][2];
    v[i][0] = 2.0*v[i][1] - v[i][2];
    u[i][my-1] = 2.0*u[i][my-2] - u[i][my-3];
    v[i][my-1] = 2.0*v[i][my-2] - v[i][my-3];
    u[i][my] = 2.0*u[i][my-1] - u[i][my-2];
    v[i][my] = 2.0*v[i][my-1] - v[i][my-2];
  }

  for(int i=cx1; i<cx2+1; i++){
    for(int j=cy1; j<cy2+1; j++){
      u[i][j] = 0.0;
      v[i][j] = 0.0;
    }
  }
  return 0;
}

int poiseq(float delt){
  vector< vector<float> > rhs;
  rhs.resize(mx+1);
  for(int i = 0; i < mx+1; i++){
    rhs[i].resize(my+1);
  }
  // calculate poisson
  float ux, uy, vx, vy;
  for(int i=1; i<mx; i++)  {
    for(int j=1; j<my; j++){
      if(((i>cx1) and (i<cx2)) and ((j>cy1) and (j<cy2))){    //exclude cube
        continue;
      }
      else{
        ux = (u[i+1][j]-u[i-1][j])/(2.0*dx);
        uy = (u[i][j+1]-u[i][j-1])/(2.0*dy);
        vx = (v[i+1][j]-v[i-1][j])/(2.0*dx);
        vy = (v[i][j+1]-v[i][j-1])/(2.0*dy);
        rhs[i][j] = (ux+vy)/delt - (std::pow(ux,2.0) + 2.0*uy*vx + std::pow(vy,2.0));
      }
    }
  }

  // iterations
  float res;
  float dp;
  for (int itr=0; itr<maxitp+1; itr++){
    res = 0.0;
    for(int i=1; i<mx; i++){
      // if(i=105){
      //     std::cout << itr << '\n';
      // }
      for(int j=1; j<my; j++){
        if(((i>cx1-1) and (i<cx2+1)) and ((j>cy1-1) and (j<cy2+1))){  // exclude cube
          continue;                                                   // 非不連続区間で差分取れる範囲以外を所外
        }
        else{
          dp = (p[i+1][j] + p[i-1][j])/(std::pow(dx,2.0))
             + (p[i][j+1] + p[i][j-1])/(std::pow(dy,2.0))
             - rhs[i][j];
          dp = dp/(2.0/(std::pow(dx,2.0)) + 2.0/(std::pow(dy,2.0))) - p[i][j];
          res = res + std::pow(dp,2.0);
          p[i][j] = p[i][j] + omegap*dp;
        }
      }
    }
    bound_p();
    res = sqrt(res/(mx*my));
    // std::cout << res << '\n';
    if(res < errorp){
      resp = res;
      itrp = itr;
      // std::cout << "finish SOR::" << res << "," << itr << '\n';
      break;
    }
  }
  return 0;
}

int veloeq(float delt){
  vector< vector<float> > urhs;    // verocity grid
  vector< vector<float> > vrhs;
  urhs.resize(mx+1);
  vrhs.resize(mx+1);
  for(int i = 0; i < mx+1; i++){
    urhs[i].resize(my+1);
    vrhs[i].resize(my+1);
  }

  for(int i=1; i<mx; i++){    //pressure radient
    for(int j=1; j<my; j++){
      if(((i>cx1-1) and (i<cx2+1)) and ((j>cy1-1) and (j<cy2+1))){
        continue;
      }
      else{
        urhs[i][j] = -(p[i+1][j] - p[i-1][j])/(2.0*dx);
        vrhs[i][j] = -(p[i][j+1] - p[i][j-1])/(2.0*dy);
      }
    }
  }

  for(int i=1; i<mx; i++){
    for(int j=1; j<my; j++){
      if(((i>cx1-1) and (i<cx2+1)) and ((j>cy1-1) and (j<cy2+1))){
        continue;
      }
      else{
        urhs[i][j] += (u[i+1][j]-2.0*u[i][j]+u[i-1][j])/(re*std::pow(dx,2.0))
                     +(u[i+1][j]-2.0*u[i][j]+u[i-1][j])/(re*std::pow(dy,2.0));
        vrhs[i][j] += (v[i+1][j]-2.0*v[i][j]+v[i-1][j])/(re*std::pow(dx,2.0))
                     +(v[i+1][j]-2.0*v[i][j]+v[i-1][j])/(re*std::pow(dy,2.0));
      }
    }
  }

  for(int j=cy1+1; j<cy2; j++){
    u[cx1+1][j] = 2.0*u[cx1][j]-u[cx1-1][j];
    u[cx2-1][j] = 2.0*u[cx2][j]-u[cx2+1][j];
    v[cx1+1][j] = 2.0*v[cx1][j]-v[cx1-1][j];
    v[cx2-1][j] = 2.0*v[cx2][j]-v[cx2+1][j];
  }

  for(int i=2; i<mx-1; i++){    //advection term for x-axis
    for(int j=2; j<my-1; j++){
      if(((i>cx1-1) and (i<cx2+1)) and ((j>cy1-1) and (j<cy2+1))){
        continue;
      }
      else{
        urhs[i][j] += -u[i][j]*(-u[i+2][j]+8.0*(u[i+1][j]-u[i-1][j]) + u[i-2][j])/(12.0*dx)
                      -abs(u[i][j])*(u[i+2][j]-4.0*u[i+1][j]+6.0*u[i][j]-4.0*u[i-1][j]+u[i-2][j])/(4.0*dx);
        vrhs[i][j] += -u[i][j]*(-v[i+2][j]+8.0*(v[i+1][j]-v[i-1][j])+v[i-2][j])/(12.0*dx)
                      -abs(u[i][j])*(v[i+2][j]-4.0*v[i+1][j]+6.0*v[i][j]-4.0*v[i-1][j]+v[i-2][j])/(4.0*dx);
      }
    }
  }

  for(int i=cx1+1; i<cx2; i++){
    u[i][cy1+1] = 2.0*u[i][cy1] - u[i][cy1-1];
    u[i][cy2-1] = 2.0*u[i][cy2] - u[i][cy2+1];
    v[i][cy1+1] = 2.0*v[i][cy1] - v[i][cy1-1];
    v[i][cy2-1] = 2.0*v[i][cy2] - v[i][cy2+1];
  }

  for(int i=2; i<mx-1; i++){
    for(int j=2; j<my-1; j++){
      if(((i>cx1-1) and (i<cx2+1)) and ((j>cy1-1) and (j<cy2+1))){
        continue;
      }
      else{
        urhs[i][j] += -v[i][j]*(-u[i][j+2]+8.0*(u[i][j+1]-u[i][j-1]) + u[i][j-2])/(12.0*dy)
                      -abs(v[i][j])*(u[i][j+2]-4.0*u[i][j+1]+6.0*u[i][j]-4.0*u[i][j-1]+u[i][j-2])/(4.0*dy);
        vrhs[i][j] += -v[i][j]*(-v[i][j+2]+8.0*(v[i][j+1]-v[i][j-1])+v[i][j-2])/(12.0*dy)
                      -abs(v[i][j])*(v[i][j+2]-4.0*v[i][j+1]+6.0*v[i][j]-4.0*v[i][j-1]+v[i][j-2])/(4.0*dy);
      }
    }
  }

  for(int i=2; i<mx-1; i++){
    for(int j=2; j<my-1; j++){
      if(((i>cx1-1) and (i<cx2+1)) and ((j>cy1-1) and (j<cy2+1))){
        continue;
      }
      else{
        u[i][j] += delt*urhs[i][j];
        v[i][j] += delt*vrhs[i][j];
      }
    }
  }

  return 0;
}

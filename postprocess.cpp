#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

int csvw(FILE *ffile, char *fname, vector<vector<float>> f){
  if((ffile = fopen(fname, "w")) == NULL){
    std::cout << "can't open file:::" << fname << '\n';
  }
  else{
    for(int j=0; j<my+1; j++){    // y-axis fix
      for(int i=0; i<mx; i++){
        fprintf(ffile, "%f,", f[i][j]);
      }
      fprintf(ffile, "%f\n", f[mx][j]);
    }
  }
  return 0;
}


int csvout(int num){
  // std::cout << "csv output... itr::" << num << '\n';

  FILE *fu=nullptr;
  FILE *fv=nullptr;
  FILE *fp=nullptr;
  char uname[30];
  char vname[30];
  char pname[30];
  sprintf(uname, "./uitr/uitr%d.csv", num);
  sprintf(vname, "./vitr/vitr%d.csv", num);
  sprintf(pname, "./pitr/pitr%d.csv", num);
  csvw(fu, uname, u);
  csvw(fv, vname, v);
  csvw(fp, pname, p);

  if(num == nbegin){
    FILE *fx=nullptr;
    FILE *fy=nullptr;
    char xname[30];
    char yname[30];
    sprintf(xname, "xaxis.csv");
    sprintf(yname, "yaxis.csv");
    csvw(fx, xname, x);
    csvw(fy, yname, y);
  }

  return 0;
}

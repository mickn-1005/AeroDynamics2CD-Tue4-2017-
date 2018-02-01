// CFD Simulation of Kalman Vortex

#include <iostream>

#include "Karman.h"
#include "Karman.cpp"

int main(void) {
  set_grids();

  flow_solve();

  return 0;
}

// note: calculation time:: [Finished in 663.476s]

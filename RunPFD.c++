// -------------------------------
// projects/PFD/RunPFD.c++
// Copyright (C) 2016
// -------------------------------

// --------
// includes
// --------

#include <iostream> // cin, cout

#include "PFD.h"

// ----
// main
// ----

int main() {
  using namespace std;
  PFD_solve(cin, cout);
  return 0;
}

/*
% g++-4.8 -pedantic -std=c++11 -Wall -fprofile-arcs -ftest-coverage PFD.c++
RunPFD.c++ -o RunPFD
% ./RunPFD < RunPFD.in > RunPFD.tmp
% diff RunPFD.tmp RunPFD.out
*/

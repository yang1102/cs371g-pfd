// ----------------------------
// projects/PFD/PFD.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <vector>

#include "PFD.h"

using namespace std;

// ------------
// PFD_read
// ------------

bool PFD_read(istream &r, vector<vector<int>>& data) {
  int i,j;
  if (!(r >> i))
    return false;

  r >> j;
  assert( i > 0 && j > 0);
  for (int k = 0; k < i; ++k)
  {
    vector<int> temp(i+1,0);
    data.push_back(temp);
  }
  for( int k = 0; k< j; ++k)
  {
    int ind, num;
    r>> ind;
    r>> num;
    data[ind-1][0] = num;
    for(int m = 0; m< num; ++m)
    {
      int tmp;
      r >> tmp;
      data[ind-1][tmp] = 1;
    }
  }
  return true;
}

// ------------
// PFD_eval

int PFD_eval(int num1, int num2) {
  // <your code>
  return 0;
}

// -------------
// PFD_print
// -------------

void PFD_print(ostream &w, int i, int j, int v) {
  
}

// -------------
// PFD_solve
// -------------

void PFD_solve(istream &r, ostream &w) {
  vector<vector<int>> data;
  while (PFD_read(r,data)) {
    //const int v = PFD_eval(i, j);
    //PFD_print(w, i, j, v);
    for( unsigned int i = 0; i < data.size(); i++)
    {
      for ( unsigned int j = 0; j < data[i].size(); j++)
        cout << data[i][j] << " ";
        cout << endl;
    }
    data.erase(data.begin(), data.end());
  }
}

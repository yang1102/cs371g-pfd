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
#include <list>
#include <queue>
#include "PFD.h"

using namespace std;

priority_queue<int,vector<int>,greater<int>> priorityQueue;
// ------------
// PFD_read
// ------------


bool PFD_read(istream &r, vector<list<int>>& data, vector<int>& degree) {
  int i,j;
  if (!(r >> i))
    return false;

  r >> j;
  assert( i > 0 && j > 0);
  for (int k = 0; k < i; ++k)
  {
    list<int> temp;
    data.push_back(temp);
    degree.push_back(0);
  }
  
  for( int k = 0; k< j; ++k)
  {
    int ind, num;
    r>> ind;
    r>> num;
    degree[ind-1] = num; //degree is number of things it depends on
    for(int m = 0; m< num; ++m)
    {
      int tmp;
      r >> tmp;
      data[tmp-1].push_back(ind); // elements of the list depend on tmp
    }
  }
  for(int k = 0; k < i; k++)
    {
      if(degree[k] ==0)  // if a number doesnt depend on anything add it to the queue
        priorityQueue.push(k+1);
    }
  return true;
}

// ------------
// PFD_eval

vector<int> PFD_eval(vector<list<int>>& data, vector<int>& degree) {
  // <your code>
  vector<int> result;
  while(!priorityQueue.empty()){
    int ele = priorityQueue.top();
    priorityQueue.pop();
    while(!data[ele-1].empty()){
      int dep = data[ele-1].front();
      data[ele-1].pop_front();

      --degree[dep-1];
      if (degree[dep-1] == 0){
        priorityQueue.push(dep);

      }
    }
    result.push_back(ele);
  }
  return result;
}

// -------------
// PFD_print
// -------------

void PFD_print(ostream &w, vector<int> result) {
      for(unsigned int i=0;i<result.size();i++){
        w << result[i] << " ";
      }
      w << endl;
}

// -------------
// PFD_solve
// -------------

void PFD_solve(istream &r, ostream &w) {
  vector<list<int>> data;
  vector<int> degree;
  while (PFD_read(r,data,degree)) {

    vector<int> order = PFD_eval(data,degree);

    PFD_print(w, order);

    data.erase(data.begin(), data.end());
  }
}


int main() {
  using namespace std;
  PFD_solve(cin, cout);
  return 0;
}
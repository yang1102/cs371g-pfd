// --------------------------
// projects/PFD/PFD.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------

#ifndef PFD_h
#define PFD_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <queue>
#include <vector>
#include <list>

using namespace std;

#define OPTMIZE true

#ifdef OPTMIZE
extern priority_queue<int,vector<int>,greater<int>> priorityQueue;
#endif

// ------------
// PFD_read
// ------------

/**
 * read the input into vector of lists and mark the degree of each task 
 * @param r an istream
 * @param data a vector of list<int>
 * @param degree a vector of int
 * @return true if the read is successful, otherwise false
 */
bool PFD_read(istream &r, vector<list<int>>& data, vector<int>& degree);

// ------------
// PFD_eval
// ------------

/**
 * @param data stored the each tasks' dependent tasks
 * @param degree stored the degree of each task
 * @return the a vector which stored the dependent order of tasks
 */
vector<int> PFD_eval(vector<list<int>>& data, vector<int>& degree) ;

// -------------
// PFD_print
// -------------

/**
 * print vector to w
 * @param w an ostream
 * @param result a vector of int which stored the dependent order of tasks
 */
void PFD_print(ostream &w, vector<int> result);

// -------------
// PFD_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void PFD_solve(istream &r, ostream &w);

#endif // PFD_h

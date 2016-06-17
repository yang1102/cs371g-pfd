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

using namespace std;

// ------------
// PFD_read
// ------------

/**
 * read two ints from r into i an j
 * @param r an istream
 * @param i an int
 * @param j an int
 * @return true if the read is successful, otherwise false
 */
bool PFD_read(istream &r, int &i, int &j);

// ------------
// PFD_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j)
 */
int PFD_eval(int i, int j);

// -------------
// PFD_print
// -------------

/**
 * print three ints to w
 * @param w an ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void PFD_print(ostream &w, int i, int j, int v);

// -------------
// PFD_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void PFD_solve(istream &r, ostream &w);

#endif // PFD_h

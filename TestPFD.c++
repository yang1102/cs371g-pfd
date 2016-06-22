// --------------------------------
// projects/PFD/TestPFD.c++
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <list>
#include <vector>
#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;


// ----
// read
// ----

TEST(PFDFixture, read_1) {
    istringstream r("5 4\n3 2 1 5\n 2 2 5 3\n 4 1 3\n 5 1 1");
    vector<list<int>> i;
    vector<int> j;
    const bool b = PFD_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_TRUE(i[0].size() ==2);
    ASSERT_TRUE(i[2].size() ==2);
    ASSERT_TRUE(i[4].size() ==2);
    int degrees[5] = {0,2,2,1,1};
    for(int n = 0; n<5; n++)
      ASSERT_EQ(degrees[n], j[n]);
    }
TEST(PFDFixture, read_2) {
    istringstream r("1 0");
    vector<list<int>> i;
    vector<int> j;
    const bool b = PFD_read(r, i, j);
    ASSERT_TRUE(b);
    ASSERT_TRUE(i[0].empty());
    int degrees[] = {0};
    ASSERT_EQ(degrees[0], j[0]);
}
TEST(PFDFixture, read_3) {
    istringstream r("6 5\n3 2 2 1\n 2 1 1\n 4 3 3 2 1\n 5 4 4 3 2 1\n6 5 5 4 3 2 1");
    vector<list<int>> i;
    vector<int> j;
    const bool b = PFD_read(r, i, j);
    ASSERT_TRUE(b);
    int degrees[6] = {0,1,2,3,4,5};
    for(int n = 0; n<6; n++)
      ASSERT_EQ(degrees[n], j[n]);
}

// ----
// eval
// ----

TEST(PFDFixture, eval_1) {
    //erase the element in priorityQueue which is added in the first 3 reads
    while(!priorityQueue.empty())
      priorityQueue.pop();
    vector<list<int>> i;
    for (int n =0; n< 5; n++)
      {list<int> tmp; i.push_back(tmp);}
    i[0].push_back(3);
    i[0].push_back(5);
    i[2].push_back(2);
    i[2].push_back(4);
    i[4].push_back(3);
    i[4].push_back(2);
    priorityQueue.push(1);
    vector<int> j  {0,2,2,1,1};
    vector<int> ans = {1,5,3,2,4}; 
    const vector<int> v = PFD_eval(i,j);
    for(int n = 0; n<5; n++)
    { ASSERT_EQ(v[n],ans[n]);}
}

TEST(PFDFixture, eval_2) {
    vector<list<int>> i;
    list<int>tmp;
    i.push_back(tmp);
    vector<int> j = {0};
    priorityQueue.push(1);
    const vector<int> v = PFD_eval(i,j);
    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(1, v.size());
}

TEST(PFDFixture, eval_3) {
    vector<list<int>> i;
    for(int n = 0; n< 5; n++)
    { list<int>tmp; i.push_back(tmp);}
    vector<int> j = {0,0,0,0,0};
    priorityQueue.push(5);
    priorityQueue.push(4);
    priorityQueue.push(3);
    priorityQueue.push(2);
    priorityQueue.push(1);
    vector<int> ans = {1,2,3,4,5}; 
    const vector<int> v = PFD_eval(i,j);
    for(int n = 0; n<5; n++)
    { ASSERT_EQ(v[n],ans[n]);}
}

// -----
// print
// -----

TEST(PFDFixture, print_1) {
    ostringstream w;
    vector<int> result = {1,2,3,4,5};
    PFD_print(w, result);
    ASSERT_EQ("1 2 3 4 5 \n", w.str());
}

TEST(PFDFixture, print_2) {
    ostringstream w;
    vector<int> result = {};
    PFD_print(w, result);
    ASSERT_EQ("\n", w.str());
}

// -----
// solve
// -----


TEST(PFDFixture, solve_1) {
    istringstream r("1 0\n");
    ostringstream w;
    PFD_solve(r, w);
    ASSERT_EQ("1 \n", w.str());
 
}

TEST(PFDFixture, solve_2) {
    istringstream r("5 0\n");
    ostringstream w;
    PFD_solve(r, w);
    ASSERT_EQ("1 2 3 4 5 \n", w.str());
 
}

TEST(PFDFixture, solve_3) {
    istringstream r("6 5\n1 5 2 3 4 5 6\n2 4 3 4 5 6\n3 3 4 5 6\n4 2 5 6\n5 1 6");
    ostringstream w;
    PFD_solve(r, w);
    ASSERT_EQ("6 5 4 3 2 1 \n", w.str());
}

TEST(PFDFixture, solve_4) {
    istringstream r("6 5\n1 5 2 3 4 5 6\n\n\n\n");
    ostringstream w;
    PFD_solve(r, w);
    ASSERT_EQ("2 3 4 5 6 1 \n", w.str());
}

/*
% g++-4.8 -pedantic -std=c++11 -Wall -fprofile-arcs -ftest-coverage PFD.c++ TestPFD.c++ -o TestPFD -lgtest -lgtest_main -pthread
% valgrind ./TestPFD                                           >  TestPFD.tmp 2>&1
% gcov-4.8 -b PFD.c++     | grep -A 5 "File 'PFD.c++'"     >> TestPFD.tmp
% gcov-4.8 -b TestPFD.c++ | grep -A 5 "File 'TestPFD.c++'" >> TestPFD.tmp
*/


#include <iostream>
#include <iomanip>  
#include <cstdlib>
#include <string>
#include <chrono>
#include <cmath>
using namespace std;

struct point2D {
     float x; // x coordinate
     float y; // y coordinate
};

// function to print a cyclic sequence of 2D points in 2D plane, given the
// number of elements and the actual sequence stored as an array of 2D points
// SAME AS IN THE PREVIOUS PROGRAM
// YOU NEED TO IMPLEMENT THIS FUNCTION
void print_cycle(int, point2D*, int*);

// function to return the index of a point that is furthest apart from some other point
// YOU NEED TO IMPLEMENT THIS FUNCTION
int farthest_point(int, point2D*);

// function to calculate the nearest unvisited neighboring point
// YOU NEED TO IMPLEMENT THIS FUNCTION
int nearest(int, point2D*, int, bool*);

int main() {
     
     point2D *P;
     int *M;
     bool *Visited;
     int i, n;
     float dist;
     int A, B;

     // display the header
     cout << endl << "CPSC 335-03 - Programming Assignment #3" << endl;
     cout << "Rectilinear traveling salesperson problem: INNI algorithm" << endl;
     cout << "Enter the number of vertices (>2) " << endl;

     // read the number of elements
     cin >> n;

     // if less than 3 vertices then terminate the program
     if (n <3)
          return 0;

     // allocate space for the sequence of 2D points
     P = new point2D[n];

     // read the sequence of distinct points
     cout << "Enter the points; make sure that they are distinct" << endl;
     for (i = 0; i < n; i++) {
          cout << "x = ";
          cin >> P[i].x;
          cout << "y = ";
          cin >> P[i].y;
     }

     // allocate space for the INNA set of indices of the points
     M = new int[n];

     // set the best set to be the list of indices, starting at 0
     for (i = 0; i < n; i++)
          M[i] = i;

     // Start the chronograph to time the execution of the algorithm
     auto start = chrono::high_resolution_clock::now();

     // allocate space for the Visited array of Boolean values
     Visited = new bool[n];

     // set it all to False
     for (i = 0; i < n; i++)
          Visited[i] = false;

     // calculate the starting vertex A
     A = farthest_point(n, P);

     // add it to the path
     i = 0;
     M[i] = A;

     // set it as visited
     Visited[A] = true;

     for (i = 1; i < n; i++) {
          // calculate the nearest unvisited neighbor from node A
          B = nearest(n, P, A, Visited);
          // node B becomes the new node A
          A = B;
          // add it to the path
          M[i] = A;
          Visited[A] = true;
     }

     // calculate the length of the Hamiltonian cycle
     dist = 0;
     for (i = 0; i < n - 1; i++)
          dist += abs(P[M[i]].x - P[M[i + 1]].x) + abs(P[M[i]].y - P[M[i + 1]].y);
     dist += abs(P[M[0]].x - P[M[n - 1]].x) + abs(P[M[0]].y - P[M[n - 1]].y);

     // End the chronograph to time the loop
     auto end = chrono::high_resolution_clock::now();

     // after shuffling them
     cout << "The Hamiltonian cycle of a relative minimum length " << endl;
     print_cycle(n, P, M);
     cout << "The relative minimum length is " << dist << endl;

     // print the elapsed time in seconds and fractions of seconds
     int microseconds = chrono::duration_cast<chrono::microseconds>(end - start).count();
     double seconds = microseconds / 1E6;
     cout << "elapsed time: " << seconds << " seconds" << endl;

     // de-allocate the dynamic memory space
     delete[] P;
     delete[] M;
     return EXIT_SUCCESS;
}

// function to calculate the furthest distance between any two 2D points
// YOU NEED TO IMPLEMENT THIS FUNCTION
int farthest_point(int n, point2D *P) {
     float maxDist = 0;
     int i, j, farthest;
     float dist = 0;
     farthest = 0;

     for (i = 0; i < n; i++) {
          dist = 0;
          for (j = 0; j < n; j++) {
               dist = fabs(P[i].x - P[j].x) + fabs(P[i].y - P[j].y);
               if (maxDist < dist) {
                    maxDist = dist;
                    farthest = 1;
               }
          }
     }
     return farthest;
     //return maxDist;
}

// function to calculate the nearest unvisited neighboring point
// YOU NEED TO IMPLEMENT THIS FUNCTION
int nearest(int n, point2D *P, int A, bool *Visited) {
     float dist;
     float bestDist;
     int nearest, i, j;
     dist = 0;
     bestDist = 0;
     nearest = 0;

     for (i = 0; i < n; i++) {
          if (Visited[i] == false) {
               bestDist = abs(P[A].x - P[i].x) + abs(P[A].y - P[i].y);
               break;
          }
     }
     for (j = 0; j < n; j++) {
          dist = 0;
          if (Visited[j] == false) {
               dist = abs(P[A].x - P[j].x) + abs(P[A].y - P[j].y);
               if (bestDist >= dist) {
                    bestDist = dist;
                    nearest = j;
               }
          }
     }
     return nearest;
}

// YOU NEED TO IMPLEMENT THIS FUNCTION
void print_cycle(int n, point2D *P, int *seq) {
     int i;

     for (i = 0; i < n; i++)
          cout << "(" << P[seq[i]].x << "," << P[seq[i]].y << ")";
     cout << "(" << P[seq[0]].x << "," << P[seq[0]].y << ")";
     cout << endl;
}

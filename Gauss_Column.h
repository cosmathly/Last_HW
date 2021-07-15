#ifndef _Gauss_Column_
#define _Gauss_Column
#define maxsize 7600
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
extern int n;
extern int m;
extern double A[maxsize][maxsize];
extern double b[maxsize];
extern double x[maxsize];
class Matrix_Calc
{
      public:
        Matrix_Calc()=default;
        double Abs(double x);
        void swap(double & a, double & b);
        void print();
        void clc_2();
        void clc_4();
};
#endif
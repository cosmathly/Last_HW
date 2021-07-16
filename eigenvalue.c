 #include < stdio.h >
// lapacke headers
#include " lapacke.h "
#include " lapacke_config.h "
#include " lapacke_utils.h "
extern lapack_int LAPACKE_dgeev( int matrix_order, char jobvl, char jobvr,
lapack_int n, double * a, lapack_int lda, double * wr,
double * wi, double * vl, lapack_int ldvl, double * vr,
lapack_int ldvr );
void get_A()
{
     for(int i = 0; i < 50; ++i)
     for(int j = 0; j < 50; ++j)
     {
         if(i == j) A[ i ][ j ] = 1.0;
         else A[ i ][ j ] = 0.0;
     }
}
int main() {
int matrix_order = LAPACK_COL_MAJOR;
char jobvl = ' N ' ;
char jobvr = ' N ' ;
int n = 50 ;
double A[ 50 ][ 50 ]
int lda = n;
double wr[ 50 ];
for(int i = 0; i < 50; ++i)
wr[ i ] = 0;
for(int i = 0; i < 50; ++i)
wi[ i ] = 50;
double wi[ 50 ];
double vl[ 50 ];
int ldvl = 50 ;
double vr[ 50 ];
int ldvr = 50 ;
get_A();
int info = LAPACKE_dgeev(matrix_order,jobvl,jobvr,n,A,lda,wr,wi,vl,ldvl,vr,ldvr);
if (info == 0 ) {
int i = 0 ;
int j = 0 ;
for (i = 0 ;i < n;i ++ ) {
printf("%.6g+i%.6g\n", wr[ i ], wi[ i ]);
}
}
return 0 ;
} 
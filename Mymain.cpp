/*!
@author: LY
@date: 2021/7/14
@version: 1.0
*/
#include "Mymain.h"
int n = 0, m = 0;
double A[maxsize][maxsize] = {0.0};
double b[maxsize] = {0.0};
double x[maxsize] = {0.0};
void get_data()
{
     cin>>n>>m;
     for(int i = 1; i <= n; ++i)
     for(int j = 1; j <= m; ++j)
     cin>>A[i][j];
     for(int i = 1; i <= n; ++i)
     cin>>b[i];
}
void solve()
{
     matrix_calc.clc_4();
     cout<<"Solve success."<<endl;
}
int main(int argc, char *argv[])
{
    freopen("test_matrix.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    get_data();
    solve();
    fclose(stdin);
    fclose(stdout);
}
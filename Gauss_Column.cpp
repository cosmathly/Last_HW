#include "Gauss_Column.h"
Matrix_Calc matrix_calc;
void Matrix_Calc::clc_2() //!< 上三角阵， n == m;
{
     x[n] = b[n]/A[n][n];
     for(int i = n-1; i >= 1; --i)
     {
         double sum = b[i];
         for(int j = i+1; j <= n; ++j)
         sum -= (A[i][j]*x[j]);
         x[i] = sum/A[i][i];
     }
}
double Matrix_Calc::Abs(double x)
{
     return (x>0.0)?(x):(-1.0*x); 
}
void Matrix_Calc::swap(double & a, double & b)
{
     double tmp = a;
     a = b;
     b = tmp;
}
void Matrix_Calc::print() 
{
     cout<<'[';
     for(int i = 1; i < n; i++)
     cout<<x[i]<<',';
     cout<<x[n]<<']'<<endl;
}
__global__ void Gauss(double A[][], double b[])
{ 
     if(threadIdx.x==0) b[blockIdx.y+1] -= (A[blockIdx.y+1][0]/A[0][0]*b[0]);
     else A[blockIdx.y+1][threadIdx.x] -= (A[blockIdx.y+1][0]/A[0][0]*A[0][threadIdx.x]); 
}
void Matrix_Calc::clc_4() //!< 列主元消去法
{
     int now_i = 1, now_j = 1; //!< 初始时需要阶梯化的矩阵的右上角元素位置
     while(true)
     {
          //!< 考虑当前的A、b
          if(now_i>n||now_j>m) break;
          if(now_i==n&&now_j==m) break;
          int dst_j = -1, dst_i; //!< 存在某行元素不为0的最小的列，以及对应的行
          for(int j = now_j; j <= m; ++j)
         {
              if(dst_j == -1)
              {
                 for(int i = now_i; i <= n; ++i)
                 if(A[i][j]!=0.0) {dst_j = j; dst_i = i; break;}
              }
              else break;
          }
          if(dst_j == -1) break;
          //!< 寻找绝对值最大的列主元
          double MAX = Abs(A[dst_i][dst_j]);
          int tmp_dst_i = dst_i;
          for(int i = dst_i+1; i <= n; ++i)
          if(Abs(A[i][dst_j])>MAX) {MAX = Abs(A[i][dst_j]); tmp_dst_i = i;}
          dst_i = tmp_dst_i;
          for(int j = dst_j; j <= m; ++j)
          swap(A[now_i][j], A[dst_i][j]);
          swap(b[now_i], b[dst_i]);
          double *_A = nullptr;
          double *_b = nullptr;
          size_t nbytes = (n-now_i+1)*(m-dst_j+1)*sizeof(double);
          cudaMallocManaged((void **)(&_A), nbytes);
          for(int i = now_i; i <= n; ++i)
          for(int j = dst_j; j <= m; ++j)
          _A[(i-now_i)*(m-dst_j+1)+j-dst_j] = A[i][j];
          size_t mbytes = (n-now_i+1)*sizeof(double);
          cudaMallocManaged((void **)(&_b), mbytes);
          for(int i = now_i; i <= n; ++i)
          _b[i-now_i] = b[i];
          dim3 grid_dim(1, n-now_i);
          dim3 block_dim(m-dst_j+1, 1);
          Gauss<<<grid, block>>>(_A, _b);
          for(int i = now_i+1; i <= n; ++i)
          {
             A[i][dst_j] = 0.0;
             b[i] = _b[i];
          }
          for(int i = now_i+1; i <= n; ++i)
          for(int j = dst_j+1; j <= m; ++j)
          A[i][j] = _A[(i-now_i)*(m-dst_j+1)+j-dst_j];
          ++now_i; now_j = dst_j+1;
     }
     int first_i = -1;
     for(int i = 1; i <= n; ++i)
     {
         bool flag = true;
         for(int j = 1; j <= m; ++j)
         if(A[i][j]!=0.0) {flag = false; break;}
         if(flag==true) {first_i = i; break;}
     }
     if(first_i!=-1) 
     {
        bool flag = true;
        for(int i = first_i; i <= n; ++i)
        if(b[i]!=0.0) {flag = false; break;}
        if(flag==false) {cout<<"无解"; return ;}
     }
     if(first_i==-1) {clc_2(); print(); return ;} //!< 变换为上三角阵；
     int column[first_i];
     column[0] = 0;
     bool vis[m+1];
     for(int j = 1; j <= m; ++j)
     vis[j] = false;
     for(int i = 1; i < first_i; ++i)
     for(int j = column[i-1]+1; j <= m; ++j)
     if(A[i][j]!=0.0) {column[i] = j; vis[j] = true; break;}
     double special_x[m+1]; //!< 特解;
     for(int j = 1; j <= m; ++j)
     if(vis[j]==false) special_x[j] = 0;
     for(int i = 1; i < first_i; ++i)
     special_x[column[i]] = b[i]/A[i][column[i]];
     cout<<"特解:"<<endl;
     cout<<'[';
     for(int j = 1; j < m; ++j)
     cout<<special_x[j]<<',';
     cout<<special_x[m]<<']'<<endl;
     cout<<"基解向量:"<<endl;
     double basic_x[m+1];
     for(int j = 1; j <= m; ++j)
     if(vis[j]==false)
     {
        int pos = 1;
        for(int k = 1; k <= m; ++k)
        {
            if(k==j) {basic_x[k] = 1.0; continue;}
            if(vis[k]==false) {basic_x[k] = 0.0; continue;}
            if(k>j) {basic_x[k] = 0.0; continue;}
            if(A[pos][j]==0.0) basic_x[k] = 0.0;
            else basic_x[k] = (-1.0*A[pos][j]/A[pos][k]);
            pos++;
        } 
        cout<<'[';
        for(int k = 1; k < m; ++k)
        cout<<basic_x[k]<<',';
        cout<<basic_x[m]<<']'<<endl;
     } 
}
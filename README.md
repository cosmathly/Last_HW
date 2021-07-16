# 作业的github地址

> <git@github.com:cosmathly/Last_HW.git>

# 程序构建

> - 程序环境：
>
>   ubuntu 18.04
>
> - 软件依赖：
>
> ​      求特征值的程序依赖Lapack，求解系数矩阵的程序依赖cuda
>
> - 代码编译：
>
> ​      输入make指令在当前目录下产生eigenvalue和Gauss可执行程序
>
> ​      输入make clean清空产生的文件

# Section_1

> 文件说明：
>
> **eigenvalue.c**通过调用lapack库函数来求解50阶对角占优矩阵的特征值，**eigenvalue.txt**是求解的结果
>
> 方法说明:
>
> 调用lapack的LAPACKE_dgeev函数来求解特征值

# Section_2

> 文件说明：
>
> Gauss_Column(.h & .cpp)是cuda并行化的Gauss列主元消去法的具体实现，数据通过Mymain(.h & .cpp)来进行
>
> 读入和输出，最终的求解结果保存在result119425.txt中
>
> 方法说明:
>
> 在进行Gauss消元的时候可以采用cuda进行并行化，更具体地， 
> $$
> 假设当前的主元为a_{ij}，设置grid为(1, (n-i), 1) (n为A的行数)，设置block为((m-j+1), 1, 1)(m为A的列数)，每一个线程都会对某一个位置的元素进行消元，例如a_{pq}将会被某个线程消去成为:a_{pq}-a_{iq}*a_{pj}/a_{ij}，该功能由kernel函数实现，代码如下：
> $$
>
>   ```c++
>   __global__ void Gauss(double A[][], double b[])
>   { 
>        if(threadIdx.x==0) b[blockIdx.y+1] -= (A[blockIdx.y+1][0]/A[0][0]*b[0]);
>        else A[blockIdx.y+1][threadIdx.x] -= (A[blockIdx.y+1][0]/A[0][0]*A[0][threadIdx.x]); 
>   }
>   ```
>
> 


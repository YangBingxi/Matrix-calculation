/**
	功能：
		输入两个矩阵完成矩阵的转置、加减法、乘法、求逆等运算
	开发平台：DEV-C++ 5.11 
	开发时间：2017.12.1
		By Young Sw	 
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/**
	由于为单文件工程，故在主函数前进行函数申明
	2017.12.1
	By Young Sw	
**/ 
void Function_matrix(int row, int line);
void dynamic_arr(int*** arr, int row, int line); 
void input_arr(int*** arr, int row, int line); 
void free_arr(int*** arr, int x);
void matrix_t(int **a_matrix, int **b_matrix, int krow, int kline);
void matrix_a(int **a_matrix, int **b_matrix, int **c_matrix,   
                    int krow, int kline, int ktrl);    
void matrix_m(int **a_matrix, int **b_matrix, int **c_matrix,  
                int krow, int kline, int kmiddle, int ktrl); 
int  matrix_inv(int **a_matrix, int ndimen); 
void chol(int **a_matrix, int **b_matrix, int ndimen);	
void output_arr(int** arr, int row, int line);			 
/**
	函数：int main()
	入口参数：无
	返回值：0 
	函数功能：主函数 
	2017.12.1
	By Young Sw	
**/
int main()
{            
    int row,line;

    printf("请输入矩阵的行row,列line：\n");                   //输入行列值                              
    scanf("%d", &row); 
	scanf("%d", &line); 		 
    Function_matrix(row, line);                      

    return 0;
} 
/**
	函数：void Function_matrix(int row, int line)
	入口参数：int row, int line
	返回值：无 
	函数功能： 主执行功能函数 
	2017.12.1
	By Young Sw	
**/
void Function_matrix(int row, int line)
{
    int ndimen;
    int** arr_a;
    int** arr_b;
    int** arr_res;

    input_arr(&arr_a, row, line);
    input_arr(&arr_b, line, row);					//为满足乘法arr1的raw=arr2的line 
    dynamic_arr(&arr_res, row, row);				//申请地址		
	matrix_t(arr_res,arr_a,row,line);               //求a转置 
    output_arr(arr_res,row,line);
    matrix_t(arr_res,arr_b,row,line);               //求b转置 
    output_arr(arr_res,row,line);
    getchar();
    printf("please press enter.");
    getchar();
    matrix_a(arr_res,arr_a,arr_b,row,line,1);       //矩阵的加法 
    output_arr(arr_res,row,line);
    printf("please press enter.");
    getchar();
    matrix_a(arr_res,arr_a,arr_b,row,line,0);       //矩阵的减法 
    output_arr(arr_res,row,line);
    printf("please press enter.");
    getchar();
    matrix_m(arr_res,arr_a,arr_b,row,line,(int)row*line/2,1); 
    												//矩阵的乘法					
    output_arr(arr_res,row,line); 
	  
    printf("please press enter.");
    getchar();
    printf("请输入上面输入矩阵a的维数~\n\n");
    scanf("%d",&ndimen);
    matrix_inv(arr_a,ndimen); 						//矩阵求逆 
    output_arr(arr_a,row,line);
	printf("\n\n\nThanks ~\n");   
	printf("Young Sw\n");   
//清除占用的内存 
    free_arr(&arr_a, row);
    free_arr(&arr_b, line);
    free_arr(&arr_res, row);
}
/**
	函数：void dynamic_arr(int*** arr, int row, int line)
	入口参数：int*** arr, int row, int line
	返回值：无 
	函数功能： 申请动态数组
	2017.12.1
	By Young Sw	
**/
void dynamic_arr(int*** arr, int row, int line)                     
{     
    int i;
    *arr = (int **)malloc(sizeof(int *) * row); 
    
    for(i = 0; i < row; i++)                                  
    {
        (*arr)[i] = (int *)malloc(sizeof(int) * line);
        memset((*arr)[i], 0, sizeof(int) * line);
    }     
}
/**
	函数：input_arr(int*** arr, int row, int line)
	入口参数：int*** arr, int row, int line
	返回值：无 
	函数功能：  输入数组
	2017.12.1
	By Young Sw	
**/
void input_arr(int*** arr, int row, int line)                           
{
    int i, j;

    dynamic_arr(arr, row, line); 

    printf("请输入%d*%d个整数：\n", row , line);
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < line; j++)
            scanf("%d", &(*arr)[i][j]);
    }
  printf("\n");
}
/**
	函数：void output_arr(int** arr, int row, int line)
	入口参数：int** arr, int row, int line
	返回值：无 
	函数功能：  输出数组
	2017.12.1
	By Young Sw	
**/
void output_arr(int** arr, int row, int line)
{
	int i,j;
	for (i = 0; i < row; i++)
    {
        for (j = 0; j < line; j++)
            printf("%5d ", arr[i][j]);
        printf("\n");
    }
}
/**
	函数：free_arr(int*** arr, int x)
	入口参数：int*** arr, int x
	返回值：无 
	函数功能：  释放占用的内存
	2017.12.1
	By Young Sw	
**/
void free_arr(int*** arr, int x)                                   
{
    int i;

    for(i = 0; i < x; i++) 
    {
        free((*arr)[i]);
        (*arr)[i] = 0;
    }

    free(*arr);      
    *arr = 0;
}
////////////////////////////////////////////////////////////////////////////  
//  a_matrix:转置后的矩阵  
//  b_matrix:转置前的矩阵  
//  krow    :行数  
//  kline   :列数  
////////////////////////////////////////////////////////////////////////////
/**
	函数：void matrix_t(int** a_matrix, int** b_matrix, int krow, int kline)
	入口参数：int** a_matrix, int** b_matrix, int krow, int kline
	返回值：无 
	函数功能：  矩阵转置运算 
	2017.12.1
	By Young Sw	
**/ 
void matrix_t(int** a_matrix, int** b_matrix, int krow, int kline)   
{  
	printf("下面为所求矩阵的转置！！！\n\n"); 
    int k, k2;     
  
    for (k = 0; k < krow; k++)  
    {  
        for(k2 = 0; k2 < kline; k2++)  
        {  
            a_matrix[k2][k] = b_matrix[k][k2];  
        }  
    }  
}
////////////////////////////////////////////////////////////////////////////  
//  a_matrix=b_matrix+c_matrix  
//   krow   :行数  
//   kline  :列数  
//   ktrl   :大于0: 加法  不大于0:减法  
//////////////////////////////////////////////////////////////////////////// 
/**
	函数：void matrix_a(int **a_matrix, int **b_matrix, int **c_matrix,   
                    int krow, int kline, int ktrl)
	入口参数：int **a_matrix, int **b_matrix, int **c_matrix,   
                    int krow, int kline, int ktrl
	返回值：无 
	函数功能：  矩阵加减运算 
	2017.12.1
	By Young Sw	
**/
void matrix_a(int **a_matrix, int **b_matrix, int **c_matrix,   
                    int krow, int kline, int ktrl)   
{  
	if(ktrl)
		printf("下面为所求矩阵的加法运算！！！\n\n"); 
	else 
		printf("下面为所求矩阵的减法运算！！！\n\n"); 	 
    int k, k2;  
  
    for (k = 0; k < krow; k++)  
    {  
        for(k2 = 0; k2 < kline; k2++)  
        {  
            a_matrix[k][k2] = b_matrix[k][k2]  
                + ((ktrl > 0) ? c_matrix[k][k2] : -c_matrix[k][k2]);   
        }  
    }  
} 
////////////////////////////////////////////////////////////////////////////  
//  a_matrix=b_matrix*c_matrix  
//  krow  :行数  
//  kline :列数  
//  ktrl  : 大于0:两个正数矩阵相乘 不大于0:正数矩阵乘以负数矩阵  
//////////////////////////////////////////////////////////////////////////// 
/**
	函数：void matrix_m(int **a_matrix, int **b_matrix, int **c_matrix,  
                int krow, int kline, int kmiddle, int ktrl)
	入口参数：int **a_matrix, int **b_matrix, int **c_matrix,  
                int krow, int kline, int kmiddle, int ktrl
	返回值：无 
	函数功能：  矩阵乘法运算 
	2017.12.1
	By Young Sw	
**/
void matrix_m(int **a_matrix, int **b_matrix, int **c_matrix,  
                int krow, int kline, int kmiddle, int ktrl)   
{  
	printf("下面为所求矩阵的乘法运算！！！\n\n"); 
    int k, k2, k4;  
    int stmp;  
  
    for (k = 0; k < krow; k++)       
    {  
        for (k2 = 0; k2 < kline; k2++)     
        {  
            stmp = 0;  
            for (k4 = 0; k4 < kmiddle; k4++)    
            {  
                stmp += b_matrix[k][k4] * c_matrix[k4][k2];  
            }  
            a_matrix[k][k2] = stmp;  
        }  
    }  
    if (ktrl <= 0)     
    {  
        for (k = 0; k < krow; k++)  
        {  
            for (k2 = 0; k2 < kline; k2++)  
            {  
                a_matrix[k][k2] = -a_matrix[k][k2];  
            }  
        }  
    }  
}  
////////////////////////////////////////////////////////////////////////////
//  矩阵的求逆  
//  a_matrix:矩阵  
//  ndimen :维数  
////////////////////////////////////////////////////////////////////////////
/**
	函数：int  matrix_inv(int **a_matrix, int ndimen) 
	入口参数：int **a_matrix, int ndimen
	返回值：无 
	函数功能：  矩阵求逆运算 
	2017.12.1
	By Young Sw	
**/ 
int  matrix_inv(int **a_matrix, int ndimen)   
{  
	printf("下面为所求矩阵的逆矩阵！！！\n\n"); 
    int tmp, tmp2, b_tmp[20], c_tmp[20];  
    int k, k1, k2, k3, j, i, j2, i2, kme[20], kmf[20];  
    i2 = j2 = 0;  
  
    for (k = 0; k < ndimen; k++)    
    {  
        tmp2 = 0;  
        for (i = k; i < ndimen; i++)    
        {  
            for (j = k; j < ndimen; j++)    
            {  
                if (fabs(a_matrix[i][j] ) <= fabs(tmp2))   
                    continue;  
                tmp2 = a_matrix[i][j];  
                i2 = i;  
                j2 = j;  
            }    
        }  
        if (i2 != k)   
        {  
            for (j = 0; j < ndimen; j++)     
            {  
                tmp = a_matrix[i2][j];  
                a_matrix[i2][j] = a_matrix[k][j];  
                a_matrix[k][j] = tmp;  
            }  
        }  
        if (j2 != k)   
        {  
            for (i = 0; i < ndimen; i++)    
            {  
                tmp = a_matrix[i][j2];  
                a_matrix[i][j2] = a_matrix[i][k];  
                a_matrix[i][k] = tmp;  
            }      
        }  
        kme[k] = i2;  
        kmf[k] = j2;  
        for (j = 0; j < ndimen; j++)    
        {  
            if (j == k)     
            {  
                b_tmp[j] = 1 / tmp2;  
                c_tmp[j] = 1;  
            }  
            else   
            {  
                b_tmp[j] = -a_matrix[k][j] / tmp2;  
                c_tmp[j] = a_matrix[j][k];  
            }  
            a_matrix[k][j] = 0;  
            a_matrix[j][k] = 0;  
        }  
        for (i = 0; i < ndimen; i++)    
        {  
            for (j = 0; j < ndimen; j++)    
            {  
                a_matrix[i][j] = a_matrix[i][j] + c_tmp[i] * b_tmp[j];  
            }    
        }  
    }  
    for (k3 = 0; k3 < ndimen;  k3++)     
    {  
        k  = ndimen - k3 - 1;  
        k1 = kme[k];  
        k2 = kmf[k];  
        if (k1 != k)     
        {  
            for (i = 0; i < ndimen; i++)    
            {  
                tmp = a_matrix[i][k1];  
                a_matrix[i][k1] = a_matrix[i][k];  
                a_matrix[i][k] = tmp;  
            }    
        }  
        if (k2 != k)     
        {  
            for(j = 0; j < ndimen; j++)    
            {  
                tmp = a_matrix[k2][j];  
                a_matrix[k2][j] = a_matrix[k][j];  
                a_matrix[k][j] = tmp;  
            }  
        }  
    }  
    return (0);  
}   
////////////////////////////////////////////////////////////////////////////  
//  输入参数:  
//      b_matrix:  对称正定方阵    ndimen: 矩阵维数  
//  返回值:  
//      a_matrix: 下三角矩阵 
//矩阵乔里斯基分解函数 
//////////////////////////////////////////////////////////////////////////// 
/**
	函数：void chol(double **a_matrix, const double **b_matrix, int ndimen)  
	入口参数：double **a_matrix, const double **b_matrix, int ndimen
	返回值：无 
	函数功能：矩阵乔里斯基分解函数运算 
	2017.12.1
	By Young Sw	
**/  
void chol(double **a_matrix, const double **b_matrix, int ndimen)  
{  
    int i, j, r;  
    double m = 0;     
    static double **c_matrix;  
    static int flag = 0;  
  
    if (flag == 0)  
    {  
        flag = 1;  
        c_matrix = (double **)malloc(ndimen * sizeof(double *));  
  
        for (i = 0; i < ndimen; i++)  
            c_matrix[i] = (double *)malloc(ndimen * sizeof(double));  
    }  
  
    for (i = 0; i < ndimen; i++)  
    {  
        for (j = 0; j < ndimen; j++)   
            c_matrix[i][j] = 0;  
    }  
  
    c_matrix[0][0] = sqrt(b_matrix[0][0]);  
  
    for (i = 1; i < ndimen; i++)  
    {  
        if (c_matrix[0][0] != 0)   
            c_matrix[i][0] = b_matrix[i][0] / c_matrix[0][0];  
    }  
  
    for (i = 1; i < ndimen; i++)  
    {  
        for (r = 0; r < i; r++)      m = m + c_matrix[i][r] * c_matrix[i][r];  
  
        c_matrix[i][i] = sqrt(b_matrix[i][i] - m);  
        m = 0.0;  
  
        for (j = i + 1; j < ndimen; j++)  
        {  
            for (r = 0; r < i; r++)      m = m + c_matrix[i][r] * c_matrix[j][r];  
            c_matrix[j][i] = (b_matrix[i][j] - m) / c_matrix[i][i];  
            m = 0;  
        }  
    }  
  
    for (i = 0; i < ndimen; i++)  
    {  
        for (j = 0; j < ndimen; j++)   
            a_matrix[i][j] = c_matrix[i][j];  
    }  
}  

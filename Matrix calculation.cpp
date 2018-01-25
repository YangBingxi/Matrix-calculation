/**
	���ܣ�
		��������������ɾ����ת�á��Ӽ������˷������������
	����ƽ̨��DEV-C++ 5.11 
	����ʱ�䣺2017.12.1
		By Young Sw	 
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/**
	����Ϊ���ļ����̣�����������ǰ���к�������
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
	������int main()
	��ڲ�������
	����ֵ��0 
	�������ܣ������� 
	2017.12.1
	By Young Sw	
**/
int main()
{            
    int row,line;

    printf("������������row,��line��\n");                   //��������ֵ                              
    scanf("%d", &row); 
	scanf("%d", &line); 		 
    Function_matrix(row, line);                      

    return 0;
} 
/**
	������void Function_matrix(int row, int line)
	��ڲ�����int row, int line
	����ֵ���� 
	�������ܣ� ��ִ�й��ܺ��� 
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
    input_arr(&arr_b, line, row);					//Ϊ����˷�arr1��raw=arr2��line 
    dynamic_arr(&arr_res, row, row);				//�����ַ		
	matrix_t(arr_res,arr_a,row,line);               //��aת�� 
    output_arr(arr_res,row,line);
    matrix_t(arr_res,arr_b,row,line);               //��bת�� 
    output_arr(arr_res,row,line);
    getchar();
    printf("please press enter.");
    getchar();
    matrix_a(arr_res,arr_a,arr_b,row,line,1);       //����ļӷ� 
    output_arr(arr_res,row,line);
    printf("please press enter.");
    getchar();
    matrix_a(arr_res,arr_a,arr_b,row,line,0);       //����ļ��� 
    output_arr(arr_res,row,line);
    printf("please press enter.");
    getchar();
    matrix_m(arr_res,arr_a,arr_b,row,line,(int)row*line/2,1); 
    												//����ĳ˷�					
    output_arr(arr_res,row,line); 
	  
    printf("please press enter.");
    getchar();
    printf("�����������������a��ά��~\n\n");
    scanf("%d",&ndimen);
    matrix_inv(arr_a,ndimen); 						//�������� 
    output_arr(arr_a,row,line);
	printf("\n\n\nThanks ~\n");   
	printf("Young Sw\n");   
//���ռ�õ��ڴ� 
    free_arr(&arr_a, row);
    free_arr(&arr_b, line);
    free_arr(&arr_res, row);
}
/**
	������void dynamic_arr(int*** arr, int row, int line)
	��ڲ�����int*** arr, int row, int line
	����ֵ���� 
	�������ܣ� ���붯̬����
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
	������input_arr(int*** arr, int row, int line)
	��ڲ�����int*** arr, int row, int line
	����ֵ���� 
	�������ܣ�  ��������
	2017.12.1
	By Young Sw	
**/
void input_arr(int*** arr, int row, int line)                           
{
    int i, j;

    dynamic_arr(arr, row, line); 

    printf("������%d*%d��������\n", row , line);
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < line; j++)
            scanf("%d", &(*arr)[i][j]);
    }
  printf("\n");
}
/**
	������void output_arr(int** arr, int row, int line)
	��ڲ�����int** arr, int row, int line
	����ֵ���� 
	�������ܣ�  �������
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
	������free_arr(int*** arr, int x)
	��ڲ�����int*** arr, int x
	����ֵ���� 
	�������ܣ�  �ͷ�ռ�õ��ڴ�
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
//  a_matrix:ת�ú�ľ���  
//  b_matrix:ת��ǰ�ľ���  
//  krow    :����  
//  kline   :����  
////////////////////////////////////////////////////////////////////////////
/**
	������void matrix_t(int** a_matrix, int** b_matrix, int krow, int kline)
	��ڲ�����int** a_matrix, int** b_matrix, int krow, int kline
	����ֵ���� 
	�������ܣ�  ����ת������ 
	2017.12.1
	By Young Sw	
**/ 
void matrix_t(int** a_matrix, int** b_matrix, int krow, int kline)   
{  
	printf("����Ϊ��������ת�ã�����\n\n"); 
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
//   krow   :����  
//   kline  :����  
//   ktrl   :����0: �ӷ�  ������0:����  
//////////////////////////////////////////////////////////////////////////// 
/**
	������void matrix_a(int **a_matrix, int **b_matrix, int **c_matrix,   
                    int krow, int kline, int ktrl)
	��ڲ�����int **a_matrix, int **b_matrix, int **c_matrix,   
                    int krow, int kline, int ktrl
	����ֵ���� 
	�������ܣ�  ����Ӽ����� 
	2017.12.1
	By Young Sw	
**/
void matrix_a(int **a_matrix, int **b_matrix, int **c_matrix,   
                    int krow, int kline, int ktrl)   
{  
	if(ktrl)
		printf("����Ϊ�������ļӷ����㣡����\n\n"); 
	else 
		printf("����Ϊ�������ļ������㣡����\n\n"); 	 
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
//  krow  :����  
//  kline :����  
//  ktrl  : ����0:��������������� ������0:����������Ը�������  
//////////////////////////////////////////////////////////////////////////// 
/**
	������void matrix_m(int **a_matrix, int **b_matrix, int **c_matrix,  
                int krow, int kline, int kmiddle, int ktrl)
	��ڲ�����int **a_matrix, int **b_matrix, int **c_matrix,  
                int krow, int kline, int kmiddle, int ktrl
	����ֵ���� 
	�������ܣ�  ����˷����� 
	2017.12.1
	By Young Sw	
**/
void matrix_m(int **a_matrix, int **b_matrix, int **c_matrix,  
                int krow, int kline, int kmiddle, int ktrl)   
{  
	printf("����Ϊ�������ĳ˷����㣡����\n\n"); 
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
//  ���������  
//  a_matrix:����  
//  ndimen :ά��  
////////////////////////////////////////////////////////////////////////////
/**
	������int  matrix_inv(int **a_matrix, int ndimen) 
	��ڲ�����int **a_matrix, int ndimen
	����ֵ���� 
	�������ܣ�  ������������ 
	2017.12.1
	By Young Sw	
**/ 
int  matrix_inv(int **a_matrix, int ndimen)   
{  
	printf("����Ϊ������������󣡣���\n\n"); 
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
//  �������:  
//      b_matrix:  �Գ���������    ndimen: ����ά��  
//  ����ֵ:  
//      a_matrix: �����Ǿ��� 
//��������˹���ֽ⺯�� 
//////////////////////////////////////////////////////////////////////////// 
/**
	������void chol(double **a_matrix, const double **b_matrix, int ndimen)  
	��ڲ�����double **a_matrix, const double **b_matrix, int ndimen
	����ֵ���� 
	�������ܣ���������˹���ֽ⺯������ 
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

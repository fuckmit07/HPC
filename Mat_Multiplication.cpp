#include<iostream>
#include<cstdlib>
#include<omp.h>
#include<time.h>
#define MAX 10000
using namespace std;

int A[MAX][MAX],B[MAX][MAX], C[MAX][MAX];

void serial_m(int A[MAX][MAX],int B[MAX][MAX],int C[MAX][MAX],int n)
{
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<n;k++)
			{
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
}

void parallel_m(int A[MAX][MAX],int B[MAX][MAX],int C[MAX][MAX],int n)
{
	int i,j,k;
   #pragma omp parallel for private(i,j,k) shared(A,B,C)
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<n;k++)
			{
				C[i][j]+=A[i][k]*B[k][j];
			}
		}
	}
}

int main()
{
	int n,i,j;
	double e,s,r1,r2;
	cout<<"Enter value of NxN matrix: ";
	cin>>n;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			A[i][j]=rand()%10 + 1;
			B[i][j]=rand()%10 + 1;
		}
	}
	s=omp_get_wtime();
	serial_m(A,B,C,n);
	e=omp_get_wtime();
	r1=e-s;
	s=omp_get_wtime();
	parallel_m(A,B,C,n);
	e=omp_get_wtime();
	r2=e-s;
	cout<<"\nTs: "<<r1;
	cout<<"\nTp: "<<r2;	
	return 0;
}

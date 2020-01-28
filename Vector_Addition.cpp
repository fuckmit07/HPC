#include<iostream>
#include<cstdlib>
#include<omp.h>
#include<time.h>
#include<fstream>
#define MAX 10000000
using namespace std;

void serial_f(int n)
{
	ifstream file1("text1.txt");
	ifstream file2("text2.txt");
	ofstream file3("serial.txt");
	int f1,f2,i;
	for(i=0;i<n;i++)
	{
		file1>>f1;
		file2>>f2;
		file3<<f1+f2<<endl;
	}
	file1.close();
	file2.close();
	file3.close();
}
		
void parallel_f(int n)
{
	ifstream file1("text1.txt");
	ifstream file2("text2.txt");
	ofstream file3("parallel.txt");
	int f1,f2,i;
	#pragma omp parallel for shared(f1,f2) private(i)     //remove shared for minus
	for(i=0;i<n;i++)
	{
		file1>>f1;
		file2>>f2;
		file3<<f1+f2<<endl;
	}
	file1.close();
	file2.close();
	file3.close();
}


int main()
{
	int i,j;
	long int n;
	double s,e,r1,r2;
	cout<<"Enter number of elements to be stored in file: ";
	cin>>n;
	ofstream file1("text1.txt");
	ofstream file2("text2.txt");
	for(i=0;i<n;i++)
		file1<<rand()%MAX<<endl;
	for(i=0;i<n;i++)
		file2<<rand()%MAX<<endl;
	s=omp_get_wtime();
	serial_f(n);
	e=omp_get_wtime();
	r1=e-s;
	s=omp_get_wtime();
	parallel_f(n);
	e=omp_get_wtime();
	r2=e-s;
	cout<<"\nTs: "<<r1;
	cout<<"\nTp: "<<r2;
	return 0;
}

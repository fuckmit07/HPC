#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <time.h>

using namespace  std;


class Pbubblesort
{
 private:
 		int size;// total size of the array
 		int *array;

 public :
 		void initializeArray(); 
 		void displayArray(); 
 		void psortArray();
};


void Pbubblesort::initializeArray()
{
	cout<<"Enter the size of the array:-";
	cin>>size;
	array=new int[size];
	for (int i = 0; i < size; i++)
	{	
		array[i]=rand()%100; //random function  

	}

}// end of initalizeArray

void Pbubblesort::displayArray()
{
	cout<<"Array is:"<<endl;
	for (int i = 0; i < size; i++)
	{
		cout<<"\t"<<array[i];
	}
	cout<<endl;
} //end of displayingArray

void Pbubblesort::psortArray()
{
	int temp;

	for (int i = 0; i < size/2; i++)
	{
		#pragma omp parallel for private(temp)  
		for (int j = 0; j < size-1; j+=2) //for even phase
		{
			if (array[j]>array[j+1])
			{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}
		#pragma omp parallel for private(temp)  
		for (int j = 1; j < size-1; j+=2) //for odd phase
		{
			if (array[j]>array[j+1])
			{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}	
	}	
}// end of parallel bubble sort

int main()
{   double wtime;
	Pbubblesort obj; //creating object of a class
	obj.initializeArray();
	wtime=omp_get_wtime();
	obj.displayArray();
	cout<<"Time taken to initialize Array is:-"<<wtime<<"\ts"<<endl;
	obj.psortArray();
	obj.displayArray();
	wtime=omp_get_wtime()-wtime;
	cout<<"Time taken to sort Array in parallel is:-"<<wtime<<"s"<<endl;
	return 0;
}











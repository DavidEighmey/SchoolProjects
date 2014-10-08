#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int partition(int *array, int p, int r) {
	int pivot, i, j, temp, temp1;
	pivot = array[r];  //create pivot last element
	i = p-1;

	for(j=p; j < r; j++) {
		if(array[j] <= pivot) {
			i++;
			temp = array[j];//switch 
			array[j] = array[i];
			array[i] = temp;
		}
	}
	temp1 = array[i+1];
	array[i+1] = array[r];
	array[r] = temp1;

	return i+1;
}

void quickSort(int *array, int p, int r) {
	int q, temp;
	if(p < r) {	
		srand(time(NULL));
		int randomPivot = rand()%(r-p)+p; //create randomPivot
		cout << "randomPivot= " << randomPivot<< endl;
		temp = array[r]; //swap
		array[r] = array[randomPivot];
		array[randomPivot] = temp;

		q = partition(array,p,r); //create partition
		quickSort(array,p,q-1); 
		quickSort(array,q+1,r); 
	}
}

int main() {
	int lenArray=1;

	while( lenArray != 0) {
		cin >> lenArray;

		int *array = new int[lenArray];
		for(int i=0; i<lenArray; i++){
			cin >> array[i];
      	 	}

		quickSort(array, 0, (lenArray-1));
		for(int i=0; i<lenArray; i++){
			cout << array[i] << endl;
        	}
		delete []array;
	}
	return 0;
}

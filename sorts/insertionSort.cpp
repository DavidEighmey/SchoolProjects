/*
* Created by David Eighmey
*/
#include <iostream>
using namespace std;

void insertionSort(int *array, int lenArray){
	int key, i;
	for (int j=1; j < lenArray; j++){	
		key = array[j];//create key
		i = j - 1;
		//insert the array in the correct sequence
		while (i >= 0 && array[i] > key){
			array[i + 1] = array[i];
			i = i-1;
		}
		array[i+1]=key;
	}
}

int main(){
	int lenArray = 1;
	while( lenArray != 0) {
		cin >> lenArray;//get the length of the array

		
		int *array = new int[lenArray]; //create the array
		for(int i=0; i < lenArray; i++){
			cin >> array[i];
        	}		
		insertionSort(array, lenArray); //sort array using intersion sort

		for(int l=0; l < lenArray; l++){
			cout << array[l] << endl; //display the sorted array
        	}
		delete []array;
	}
	
	return 0;
}

/*
* Created by David Eighmey
*/
#include <iostream>
using namespace std;

void merge(int *array,int p,int q,int r){	
	//p=left, q=middle, r=right
	//declerations
    	int n1= q-p+1;
	int n2= r-q;
    	int i, j;
	int leftArray[n1];
	int rightArray[n2];
	//create left & right arrays
	for(i=0; i < n1; i++){
		leftArray[i]= array[p+i];
    	}

	for(j=0; j < n2; j++){
		rightArray[j]= array[q+j+1];
    	}

    	//re initizlize
	i=0;
	j=0;	
	for(int k=p; k <= r; k++){
		//compare the values and then merge the left and right arrays in the correct order
		if (leftArray[i] <= rightArray[j]){
			array[k] = leftArray[i];
			i++;
		} else {
			array[k] = rightArray[j];
			j++;
		}
		//if array finishes
		if(j == n2){
			for(; i < n1; i++){
				k++;
				array[k] = leftArray[i];
			}
		}
		//if array finishes
		else if (i == n1){
			for(; j < n2; j++){
				k++;
				array[k] = rightArray[j];
			}
		}
	}
}

void mergeSort(int *array,int p,int r){
	//p = left; r = right	
	if (p < r){
		int q = (p+r)/2; //create midpoint
		mergeSort(array, p, q); //left side
		mergeSort(array, q+1, r); //right side
		merge(array, p, q, r); //merge both
	}
}

int main(){
	
	int lenArray=1;	
	while(lenArray !=0){
		cin >> lenArray; // get length of array
		
		int *array= new int[lenArray]; //create array
		for(int i=0; i < lenArray; i++){
			cin >> array[i];
        	}
		mergeSort(array, 0, (lenArray-1)); //use merge sort to sort the array
		
		for(int i=0; i < lenArray; i++){
			cout << array[i] << endl; //display the array
        	}
		delete []array;
	}
	
	return 0;
}	

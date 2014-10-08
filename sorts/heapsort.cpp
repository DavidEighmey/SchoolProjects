/*
* Created by David Eighmey
*/
#include <iostream>

using namespace std;

void maxHeapify(int *array, int i, int length)
{
	int largest, temp;
	int left_child = 2*i+1;		//left
	int right_child= 2*i+2;		//right
    
	if(left_child < length  && array[left_child] > array[i]){
		largest = left_child;
    	} else {
		largest = i;
    	}

	if(right_child < length && array[right_child] > array[largest]) {
		largest = right_child;
    	}
	if(largest != i) {
		temp = array[i]; //change		
		array[i] = array[largest];
		array[largest] = temp;
		maxHeapify(array, largest, length);  //maxHeapify
	}
}

void buildMaxHeap(int *A, int length) {
	for(int i = ((length/2)-1); i > -1; i--){
		maxHeapify(A, i, length); //maxHeapify
   	}
}

void heapSort(int *array, int length) {
	int temp;
	buildMaxHeap(array, length);

	for(int i=(length-1); i > 0; i--) {
		temp = array[0];
		array[0] = array[i];
		array[i] = temp;
		length--;
		maxHeapify(array, 0, length);
	}

}

int main() {
	int lenArray=1, i;

	while (lenArray != 0) {
		cin >> lenArray;

		int *array = new int[lenArray];
		for(i=0; i < lenArray; i++){
			cin >> array[i];
        	}

		heapSort(array, lenArray);

		for(i=0; i < lenArray; i++){
			cout << array[i] << endl;
        	}
		delete []array;
	}
	return 0;
}



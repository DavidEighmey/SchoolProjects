#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main ()
{
	int counter=-1;
        string STRING;
	ifstream infile;
	infile.open ("test.txt");
     	while(infile >> STRING){
     	    counter++;
	    
	
     }
	cout<<counter;
	infile.close();
	return 0;
}

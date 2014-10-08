#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main ()
{
	int counter=0;
        string STRING;
	string word;
	cin>>word;
	ifstream infile;
	infile.open ("test.txt");
     	while(infile >> STRING){
		if(word==STRING){
			counter++;
		}
     }
	cout<<counter;
	infile.close();
	return 0;
}

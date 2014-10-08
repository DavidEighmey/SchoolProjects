#include <string>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;
int main() {

	vector<string> v;
	ifstream in("test.txt");
	string line;
	while(getline(in, line)){
		cout<<line;
		cin.ignore();
	}
}


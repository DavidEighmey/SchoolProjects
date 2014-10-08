#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int main() {
	vector<string> v;
	ifstream in("test.txt");
	string line;
	while(getline(in, line))
		v.push_back(line); // Add the line to the end
		// Add line numbers:
	for(int i = v.size()-1; i>=0; i--)
		cout << i << ": " << v[i] << endl;
}


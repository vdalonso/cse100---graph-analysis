#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "Graph.hpp"

using namespace std;

int main( int argc , char* argv[]){
	cout << "let this work please" <<endl;
	char* file1 = argv[1];
	//char* file2 = argv[2];
	char* outfile = argv[2];
	
	ifstream f1(file1);
//	ifstream f2(file2);
	ofstream out(outfile);
	
	while(f1){
		string s;
		getline(f1 , s );
	
		s = s + " " + to_string(rand() % 100);
		out << s << endl;
	

	}
	
}

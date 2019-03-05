#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"

using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file test_pairs_file output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  
  if (argc != 4) {
    usage(argv[0]);
  }
  

  char* graph_filename = argv[1];
  char* pairs_filename = argv[2];
  char* output_filename = argv[3];

  cout << "i wonder if this will work \n";

  //TODO   
 /* You can call the pathfinder function from here */

  Graph mygraph;
  mygraph.loadFromFile(graph_filename);

  ofstream outfile(output_filename);
  

  

  vector<string> paths = mygraph.splice(pairs_filename);
  for(unsigned int i = 0; i < paths.size() ; i++){
	//cout << paths[paths.size()-(1+i)] << endl;
	outfile << paths[paths.size()-(1+i)] << endl;

  }

  
	

  //cout << "This is the end.\n";
    
}  

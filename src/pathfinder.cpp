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

  //create graph and send it the filename to build it.
  Graph mygraph;
  mygraph.loadFromFile(graph_filename);
  //create a ofstream to write the the output file.
  ofstream outfile(output_filename);

  cout << mygraph.nodes.size() << endl;

  //paths will contain the list of paths between two nodes.
  vector<string> paths = mygraph.splice(pairs_filename);
  //for loop that goes through paths vector and prints out to outfile.
  for(unsigned int i = 0; i < paths.size() ; i++){
	outfile << paths[i] << endl;
  }
  outfile.close();
    
}  

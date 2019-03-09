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

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file k_value output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    usage(argv[0]);
  }
  char* graph_filename = argv[1];
  char* output_filename = argv[3];
  //istringstream ss(argv[2]);

  int k = atoi(argv[2]);

 //TODO
 /* You can call the social gathering function from here */
  //int k = atoi(ss.str());
  //cout << k << endl;
  

  Graph mygraph;
  mygraph.loadFromFile(graph_filename);
  vector<int> invitees = mygraph.socialgathering(k);
  sort(invitees.begin() , invitees.end());

  //cout << mygraph.nodes.size() << endl;

  ofstream out(output_filename);  

  for(unsigned int i = 0 ; i < invitees.size() ; i++)
	out << invitees[i] << endl;

 //cout << k << endl;

}

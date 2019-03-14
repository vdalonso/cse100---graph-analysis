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
       << " friendship_pairs_file user_id output_file"
       << endl;
  exit(-1);
}

int main(int argc , char* argv[]){
	//check if arguments are correct.
	if(argc != 4)
		usage(argv[0]);	

	char* graph_filename = argv[1];
  	string user = argv[2];
	char* output_filename = argv[3];

	Graph mygraph;
	//cout << "building...\n";
	mygraph.loadFromFile3(graph_filename);

	//ofstream out(output_filename);
	//cout << "graph built\n";
	
	mygraph.prims(output_filename , user);
	
	cout << endl << "Done. Visit " << output_filename << " to get your friends you'll need to make to be the most popular kid in school." << endl;
	//cout << "People in the top of the list are easier to approach and befriend, where as people lower are the most popular, stuck up kids." <<endl;
	//cout << "You'll need to start forming a clique before you attempt to befriend any popular kids, which is why we provided you with this order." <<endl;
	//cout << "Good luck user: " << user << "." <<endl;


}

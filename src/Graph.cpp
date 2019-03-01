#include "Graph.hpp"

#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

Graph::Graph(void)
    : nodes(0) {}

Graph::~Graph(void) {
  for (auto itr : nodes) {
    delete itr.second;
  }
}

/* Add a node to the graph representing person with id idNumber and add a connection between two nodes in the graph. */
//TODO

void Graph::addNode(string id1, string id2 ){

	//First, check if ID's already exist in nodes map. If not, create them and store them.
	if(nodes.find(id1) == nodes.end()){
		Node* n1 = new Node();
		nodes.insert({id1,n1});
	}
	if(nodes.find(id2) == nodes.end()){
		Node* n2 = new Node();
		nodes.insert({id2,n2});
	}
	nodes[id1]->adj[id2] = nodes[id2];
	nodes[id2]->adj[id1] = nodes[id1];	
	
}
//this method is for finding pairs. calls pathfinder.
vector<string> Graph::splice(const char* in_filename){
	ifstream infile(in_filename);
	vector<string> paths;
	int count = 0;
	
	while(infile){
	string s;
    	if (!getline(infile, s)) break;

   	 istringstream ss(s);
   	 vector<string> record;

    	while (ss) {
     	 string s;
     	 if (!getline(ss, s, ' ')) break;
     	 record.push_back(s);
    	}

    	if (record.size() != 2) {
    	  continue;
   	}
	
	Node* n1 = nodes[record[0]];
	Node* n2 = nodes[record[1]];
	paths[count] = pathfinder(n1,n2);
	
	
	count++;	
	}
	return paths;

}
 
/* Read in relationships from an inputfile to create a graph */

bool Graph::loadFromFile(const char* in_filename) {
  ifstream infile(in_filename);
  int count = 0;
	
  while (infile) {
    string s;
    if (!getline(infile, s)) break;

    istringstream ss(s);
    vector<string> record;

    while (ss) {
      string s;
      if (!getline(ss, s, ' ')) break;
      record.push_back(s);
    }

    if (record.size() != 2) {
      continue;
    }

    //TODO - YOU HAVE THE PAIR OF IDS OF 2 FRIENDS IN 'RECORD'. WHAT DO NEED TO DO NOW?

    addNode(record[0] , record[1]);
    count++;	
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  
  cout << count << endl;
  infile.close();
  return true;
}

/* Implement pathfinder*/
//TODO 
string Graph::pathfinder(Node* from, Node* to) {


  
}

/* Implement social gathering*/
//TODO
void Graph::socialgathering(vector<string>& invitees, const int& k) {

}


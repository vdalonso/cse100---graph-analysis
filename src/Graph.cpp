#include "Graph.hpp"

#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <climits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <queue>

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

	//undirected graph
	nodes[id1]->adj[id2] = nodes[id2];
	nodes[id1]->id = id1;

	nodes[id2]->adj[id1] = nodes[id1];
	nodes[id2]->id = id2;
	
}
//this method is for finding pairs. calls pathfinder.
vector<string> Graph::splice(const char* in_filename){
	ifstream infile(in_filename);
	vector<string> paths;
	int count = 0;
	
	//cout << "this is inside the splice function.\n";
	
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

	//cout << record[0] << " , " << record[1] <<endl;
	

	//check if these nodes actually exist.
	
	Node* n1 = nodes[record[0]];
	Node* n2 = nodes[record[1]];

	paths.push_back( pathfinder(n1 , n2));
	
	//cout << "read line\n";	
	
	count++;	
	}
	
		
	//cout << "exiting splice\n";
	//cout << "count\n";
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
  
  //cout << count << endl;
  infile.close();
  return true;
}

/* Implement pathfinder*/
//TODO 
string Graph::pathfinder(Node* from, Node* to) {
	//initialize  dist and prev to infinity and nullptr respectively.
	for(auto n = nodes.begin(); n != nodes.end() ; n++){
		n->second->dist = INT_MAX;
		n->second->prev = nullptr;
	}
	//initialize the queue. push source node in, set its distance to 0.
	queue<Node*> q;
	q.push(from);
	from->dist = 0;

	//cout << "this is inside the pathfinder function \n";
	
	//set distances for everyone.
	while(!q.empty()){
		Node * curr = q.front();
		q.pop();

		for(auto i = curr->adj.begin() ; i != curr->adj.end() ; i++){
			if(i->second->dist == INT_MAX){
				i->second->dist = curr->dist + 1;
				i->second->prev = curr;
				q.push(i->second);
			}
			//check
			//q.push(i->second);
		}
	}
	//cout << "this is after the while loop inside pathfinder \n";

		
	string path = "";

	//check if node * to was even reached.
	if(to->dist == INT_MAX)
		return path;
	
	//if not start creating the path;
	Node * back = to;
	while(back->prev != nullptr){
		path = " " + back->id + path;
		
		//cout << "ID: " << back->id << " prev: " << back->prev->id << endl;

		//if(back->prev == nullptr)
		//	cout << "this thing is null despite there being an ID for it.\n";
	
		back = back->prev;
	}
	//cout << "leaving pathfinder\n";
	path = back->id + path;

	//cout << path << endl;

	return path;	
  
}

/* Implement social gathering*/
//TODO
void Graph::socialgathering(vector<string>& invitees, const int& k) {

}


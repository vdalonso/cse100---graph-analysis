#include "Graph.hpp"

#include <unordered_map>
#include <vector>
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

struct compare3
{
	bool operator() (pair<Node* , Node*> n1 , pair<Node* , Node* > n2)
	{
		return (n1.first->weights[n1.second->id] > n2.first->weights[n2.second->id]);
	}

};

struct compare
{
	bool operator()( pair<int , Node* > n1 ,  pair<int , Node*> n2 )
	{
		return ( n1.first > n2.first );
	}

};

Graph::Graph(void)
    : nodes(0) {}

Graph::~Graph(void) {
  for (auto itr : nodes) {
    delete itr.second;
  }
}

/* Add a node to the graph representing person with id idNumber and add a connection between two nodes in the graph. */

void Graph::addNode(string id1, string id2 , int w){

	//First, check if ID's already exist in nodes map. If not, create them and store them.
	if(nodes.find(id1) == nodes.end()){
		Node* n1 = new Node();
		//cout << "inserting node1\n";
		nodes.insert({id1,n1});
	}
	if(nodes.find(id2) == nodes.end()){
		Node* n2 = new Node();
		//cout << "inserting node2\n";
		nodes.insert({id2,n2});
	}

	//if the ID's returned are of the same node, don't add a connection
	//IE: self loop case.
	if(id1 == id2)
		return;

	//undirected graph: for each pair, add both in both's adj list.
	nodes[id1]->adj[id2] = nodes[id2];
	nodes[id1]->weights[id2] = w;
	nodes[id1]->id = id1;
	nodes[id1]->degree++;

	nodes[id2]->adj[id1] = nodes[id1];
	nodes[id2]->weights[id1] = w;
	nodes[id2]->id = id2;
	nodes[id2]->degree++;

	
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

	//check if either node doesn't exist. if it does not, ignore that pair.	
	if(nodes.find(record[0]) == nodes.end() || nodes.find(record[1]) == nodes.end() ){
		paths.push_back(" ");
		//cout << "IDs in line: " << count << " doesn't exist in our graph \n";
	}
	else{
		Node* n1 = nodes[record[0]];
		Node* n2 = nodes[record[1]];	
		paths.push_back( pathfinder(n1 , n2));

	}
	
	count++;	
	}
	//returns a vector filled with paths beginning with the source node and ending with the requested node.
	//if no path was found or nodes didn't exist, it will be a blank path for that pair.
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

    addNode(record[0] , record[1] , 1);
    count++;	
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  
  infile.close();
  return true;
}


bool Graph::loadFromFile3(const char* in_filename) {
  ifstream infile(in_filename);
  int count = 0;
	
  while (infile) {
    string s;
    string delimiter = " ";
    if (!getline(infile, s)) break;

    //istringstream ss(s);
    //cout << s <<endl;
    vector<string> record;
    size_t pos = 0;
    string token;

    while ( (pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0 , pos);
	//cout << token <<endl;
      //if (!getline(ss, s, ' ')) break;
      record.push_back(token);
      s.erase(0, pos + delimiter.length() );
    }
	record.push_back(s);
	//cout << "out of while loop\n";

    if (record.size() != 3) {
      continue;
    }
    //cout << record[0] << " " << record[1] << " " << record[2] << endl;
    addNode(record[0] , record[1] , stoi(record[2]));
    count++;	
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  
  infile.close();
  return true;
}
//Prim's Algorithm, used to find the Minimun Spanning Tree of a build graph.
//in this case, we will use it to see the order of which we can make friends.

void Graph::prims(const char* outfile , string user){
	
	ofstream out(outfile);

	if(nodes.empty())
		cout << "nodes is empty...\n";
		
	for(auto n = nodes.begin(); n != nodes.end() ; n++){
		n->second->visited = false;
		n->second->prev = nullptr;
	}
	//priority queue of two nodes <from , to> 
	//less cost/weight between then means higher priority.
	priority_queue< pair<Node* , Node*> , vector< pair<Node* , Node*> > , compare3 > list; 
	nodes[user]->visited = true;
	
	//for all neighbors of "user" add them as pairs to the queue <user , neighbor_i>
	for(auto itr = nodes[user]->adj.begin() ; itr != nodes[user]->adj.end() ; itr++){

		//cout << nodes[user]->weights[itr->second->id] << endl;
		list.push({nodes[user] , itr->second});

	}


	//cout << "before while loop\n";	
	while(!list.empty()){
		pair<Node* , Node*> top = list.top();
		list.pop();
		if(!top.second->visited){
			if(nodes[user]->adj.find(top.second->id) == nodes[user]->adj.end()){
				out << top.second->id <<endl;
			}
			top.second->visited = true;
			top.second->prev = top.first;
			for(auto itr = top.second->adj.begin() ; itr != top.second->adj.end() ; itr++){
				list.push({top.second , itr->second});
			}
		}
	}
	//cout << "out of the while loop, no infinite loops!\n";
	
	out.close();	
}



/* Implement pathfinder*/
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
		}
	}
	//create string that will contain the path from "from" node to "to" node.	
	string path = "";


	//check if node * to was even reached. IE nodes aren't connected.
	if(to->dist == INT_MAX)
		return path;
	
	//if nodes were connected start creating the path by backtracking.
	Node * back = to;
	while(back->prev != nullptr){
		path = " " + back->id + path;
		
	
		back = back->prev;
	}
	path = back->id + path;


	return path;	
  
}


/* Implement social gathering*/
//TODO
//seems to work, while loop is identical to k-core count algorithm.
vector<int> Graph::socialgathering( const int& k) {
	
	priority_queue< pair<int , Node*> , vector< pair<int , Node*> > , compare > list;
	//store nodes in vector list in accending order of adj list size.
	for(auto itr = nodes.begin() ; itr != nodes.end() ; itr++){
	//	cout << "Node ID: " << itr->second->id << " with degree : " << itr->second->degree << endl;
		list.push({itr->second->degree , itr->second});
	}
	
	//this vector bellow is going to be the one we return with all id's (ints) that we invited to the party.
	vector<int> invitees;
	
	//while we still have elements in our priority queue, look at the top
	//and determine if it's less than k. if so remove it from queue and from all adj lists it belongs to.
	//if not, push it into the array of invitees and pop it off.
	while(!list.empty()){
		if(!list.top().second->visited){
			pair<int , Node*> top = list.top();
			top.second->visited = true;
			list.pop();
			top.second->core = top.first;
			for(auto itr2 = top.second->adj.begin() ; itr2 != top.second->adj.end() ; itr2++ ){
				if(itr2->second->degree > top.second->degree){
					itr2->second->degree--;
					list.push({itr2->second->degree , itr2->second});
				}
			}
		}
		else
			list.pop();
	}
	
	for(auto itr3 = nodes.begin() ; itr3 != nodes.end() ; itr3++){
		if(itr3->second->core >= k)
			invitees.push_back(stoi(itr3->second->id));

	}	
	return invitees;

}



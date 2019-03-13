#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

//implementation of node class.
class Node{
public:
	unordered_map<string , Node*> adj;
	string id;
	int degree = 0;
	int core;
	bool visited = 0;
	Node * prev;
	int dist;

	Node() : adj(0) , visited(0) , prev(0){}

};

class Graph {
 public:
   unordered_map<string, Node*> nodes;

  Graph(void);

  ~Graph(void);

  vector<string> splice(const char* in_filename);

  void addNode(string id1, string id2);

  bool loadFromFile(const char* in_filename);

  string pathfinder(Node* from, Node* to);
    
  vector<int> socialgathering(const int& k);

 // bool myfunction(Node* n1 , Node* n2);

};


#endif  // GRAPH_HPP

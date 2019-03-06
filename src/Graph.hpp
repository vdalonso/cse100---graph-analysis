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

	bool visited;
	Node * prev;
	int dist;

	Node() : adj(0) , visited(0) , prev(0){}

};

class Graph {
 protected:
   unordered_map<string, Node*> nodes;

 public:
  Graph(void);

  ~Graph(void);

  vector<string> splice(const char* in_filename);

  void addNode(string id1, string id2);

  bool loadFromFile(const char* in_filename);

  string pathfinder(Node* from, Node* to);
    
  void socialgathering(vector<string>& invitees, const int& k);

};


#endif  // GRAPH_HPP

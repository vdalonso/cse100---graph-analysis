#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;


class Node{
public:
	unordered_map<string , Node*> adj;
	bool visited;
	int prev;

	Node() : adj(0) , visited(0) , prev(0){}

};

class Graph {
 protected:
  //MAYBE ADD CLASS DATA STRUCTURE(S) HERE
   unordered_map<string, Node*> nodes;

 public:
  Graph(void);

  ~Graph(void);

  //MAYBE ADD SOME MORE METHODS HERE SO AS TO ANSWER QUESTIONS IN YOUR PA
	
  /* YOU CAN MODIFY THIS IF YOU LIKE , in_filename : THE INPUT FILENAME */
  vector<string> splice(const char* in_filename);

  void addNode(string id1, string id2);

  bool loadFromFile(const char* in_filename);

  string pathfinder(Node* from, Node* to);
    
  void socialgathering(vector<string>& invitees, const int& k);

};


#endif  // GRAPH_HPP

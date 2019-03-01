#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
	vector<int> adj;
	bool visited;
	int prev;

	//constructor
	Node(){

	}
	//deconstructor
	~Node(){

	}

};
#endif

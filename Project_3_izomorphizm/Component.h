#pragma once
#include "Node.h"
#include <vector>
#include <string>
#include <ctime>

class Component 
{
private:
	int amount_of_edges; //total amout of edges inour graph
	
	std::vector<Node*> nodes;//set of nodes in this component
public:
	Component();

	~Component();
	
	void AddNode(Node* A);

	int Size();

	int GetNumberOfEdges();
	
	static std::string FindIsomorphism(Component& A, Component& B);//return string list of all permutations, if graphs are
	//izomorphic, return "", if they are not
	
};


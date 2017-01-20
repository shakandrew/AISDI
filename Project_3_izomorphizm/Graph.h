#pragma once
//in comments TODO
#include "Component.h"
#include <map>
#include <vector>

class Graph
{
private:
	int amount_of_edges;
	std::vector<Node*> nodes;//starts from 1 to n 
	std::vector<Component*> components;// o .. k
public:
	Graph();
	
	Graph(int n);//create graph with 1 .. n nodes
	
	~Graph();
	
	void Union(int a, int b);

	void GraphIsReady();

	int GetAmountOfEdges();

	int GetAmountOfNodes();

	int GetAmountOfComponents();
	
	static std::string FindGraphIsomorphism(Graph& A, Graph& B);
private:
	void Union(Node* A, Node* B);
	
	Node * Find(Node* A);

	Node * AddNode(int i);

	Component * AddComponent();

	//Izomorphizm
	//AddNode
};


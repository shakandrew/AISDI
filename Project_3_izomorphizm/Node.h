#pragma once
#include <vector>
#include <algorithm>
#include <string>

class Node
{
private:

	std::vector<Node*> neighbor;// array of nodes
	
	int value;// value of a node

	Node * root;

	std::string note;
public:
	Node();//empty constructor

	Node(int _value);//set only value without any nodes
	
	Node(Node& A);

	Node(Node&& A);

	~Node();

	int GetValue();// get value
	
	void SetValue(int& _value);//set value

	Node * GetRoot();

	void SetRoot(Node * A);

	std::string GetNote();

	void SetNote(std::string s);

	int NumberOfNeighbors();

	static bool FindConformity(Node& A, Node& B);
	
	void AddNeighbor(Node* A);//add new neighbor

	bool operator<(Node& A);// <

	bool operator>(Node& A);// >

	friend bool operator==(Node& A, Node& B);// ==

	static bool Check(Node* A, Node* B);

	void SortNeighbors();
};


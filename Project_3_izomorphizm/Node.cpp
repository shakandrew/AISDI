#include "stdafx.h"
#include "Node.h"

Node::Node()
{
	value = NULL;
	root = this;
	note = "";
}

Node::Node(int _value)
{
	value = _value;
	root = this;
	note = "";
}

Node::Node(Node& A)
{
	value = A.value;
	neighbor = A.neighbor;
	root = A.root;
	note = A.note;
}

Node::Node(Node&& A)
{
	value = A.value;
	neighbor = A.neighbor;
	root = A.root;
	note = A.note;
	A.value = 0;
	A.neighbor.clear();
	A.root = NULL;
	A.note = "";
}

Node::~Node()
{
	
}

int Node::GetValue()
{
	return value;
}

void Node::SetValue(int& _value)
{
	value = _value;
}

Node * Node::GetRoot()
{
	return root;
}

void Node::SetRoot(Node * A)
{
	root = A;
}

int Node::NumberOfNeighbors()
{
	return neighbor.size();
}

bool Node::FindConformity(Node& A, Node& B)//find conformity in neighbors
{
	for (auto i = A.neighbor.begin(), j = B.neighbor.begin(); i != A.neighbor.end(); i++, j++)
		if ((*i)->NumberOfNeighbors() != (*j)->NumberOfNeighbors())
			return false;
	return true;
}

void Node::AddNeighbor(Node* A)
{
	neighbor.push_back(A);
}

std::string Node::GetNote()
{
	return note;
}

void Node::SetNote(std::string s)
{
	note = s;
}

bool Node::operator<(Node& A)
{
	return this->value < A.value;
}

bool Node::operator>(Node& A)
{
	return this->value > A.value;
}

bool operator==(Node& A, Node& B)
{
	return (A.value == B.value) && (A.neighbor == A.neighbor);
}

bool Node::Check(Node*A, Node*B)
{
	bool mark = false;
	// have we seen all the neighbors
	for (auto i : A->neighbor)
		if (i->GetNote() == "")
			mark = true;
	if (!mark)
	{
		if (A->GetNote() == "")
		{
			B->SetNote("+");
			A->SetNote(std::to_string(A->GetValue()) + "-->" + std::to_string(B->GetValue()));
		}
		return true;
	}
	// if no, so check are A and B similar
	for (auto i = A->neighbor.begin(); i < A->neighbor.end(); i++)
	if ((*i)->GetNote()=="")
	{
		mark = false;
		for (auto j = B->neighbor.begin(); j < B->neighbor.end(); j++)
		if ((*j)->GetNote() == "")
		{
			if (FindConformity(*(*i), *(*j)))
			{
				(*i)->SetNote(std::to_string((*i)->GetValue()) + "-->" + std::to_string((*j)->GetValue()));
				(*j)->SetNote("+");
				if (Check((*i), (*j)))
				{
					mark = true;
					break;
				}
				(*i)->SetNote("");
				(*j)->SetNote("");
			}
		}
		if (!mark)
		{
			return false;
		}
	}
	return true;
}

void Node::SortNeighbors()
{
	std::sort(this->neighbor.begin(), this->neighbor.end(), [](Node* a, Node* b)->bool {
		return a->NumberOfNeighbors() > b->NumberOfNeighbors();
	});
}
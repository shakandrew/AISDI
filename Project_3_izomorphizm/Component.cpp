#include "stdafx.h"
#include "Component.h"
#include "Node.h"

Component::Component()
{
	amount_of_edges = 0;
}

Component::~Component()
{

}

void Component::AddNode(Node* A)
{
	nodes.push_back(A);
	amount_of_edges += A->NumberOfNeighbors();
}

int Component::Size()
{
	return nodes.size();
}

int Component::GetNumberOfEdges()
{
	return amount_of_edges;
}

std::string Component::FindIsomorphism(Component& A, Component& B)
{
	bool temp;
	//_________________first check
	for (auto i = A.nodes.begin(); i < A.nodes.end(); i++)(*i)->SortNeighbors();
		
	for (auto i = B.nodes.begin(); i < B.nodes.end(); i++)(*i)->SortNeighbors();

	for (auto i = A.nodes.begin(); i < A.nodes.end(); i++)
	{
		temp = false;
		for (auto j = B.nodes.begin(); j < B.nodes.end(); j++)
		{
			if ((*i)->NumberOfNeighbors() != (*j)->NumberOfNeighbors())
				continue;
			if (!Node::FindConformity(*(*i), *(*j)))	continue;
			temp = true;
		}
		if (!temp)
			return "";
	}
	//_________________second check | silly check
	std::string str="";// string to return  
	bool mark;// 
	for (auto i = B.nodes.begin(); i < B.nodes.end(); i++)
	{
		mark = false;

		for (auto j = A.nodes.begin(); j < A.nodes.end(); j++)	(*j)->SetNote("");
		for (auto j = B.nodes.begin(); j < B.nodes.end(); j++)	(*j)->SetNote("");

		A.nodes[0]->SetNote(std::to_string(A.nodes[0]->GetValue()) + "-->" + std::to_string((*i)->GetValue()));
		(*i)->SetNote("+");
		Node::Check(A.nodes[0], (*i));
		for (auto j = A.nodes.begin(); j < A.nodes.end(); j++)
			if ((*j)->GetNote() == "")
			{
				mark = true;
				break;
			}
		if (mark) continue;
		for (auto j = A.nodes.begin(); j < A.nodes.end(); j++)
			str += (*j)->GetNote() + '\n';
		break;
	}
	return str;
}


#include "stdafx.h"
#include "Graph.h"
#include "Component.h"
#include "Node.h"

Graph::Graph()
{
	nodes.reserve(0);
	amount_of_edges = 0;
}

Graph::Graph(int n)
{
	nodes.assign(n + 1, NULL);
	for (int i = 1; i <= n; i++)
	{
		nodes[i] = AddNode(i);
	}
}

Graph::~Graph()
{
	for (auto i : nodes) delete(i);
	for (auto i : components) delete(i);
}

void Graph::Union(int a, int b)
{
	Union(nodes[a], nodes[b]);
}

void Graph::Union(Node* A, Node* B)
{
	Node * a_temp = Find(A);
	Node * b_temp = Find(B);
	if (a_temp!=b_temp)
	{
		std::srand(unsigned(std::time(0)));
		int random_variable = std::rand() % 2;
		if (random_variable)
		{
			a_temp->SetRoot(b_temp);
		}
		else
		{
			b_temp->SetRoot(a_temp);
		}
	}
	A->AddNeighbor(B);
	B->AddNeighbor(A);
	amount_of_edges += 2;
}

Node * Graph::Find(Node* A)
{
	if (A->GetRoot() != A)
		A->SetRoot(Find(A->GetRoot()));
	return A->GetRoot();
}

int Graph::GetAmountOfEdges()
{
	return amount_of_edges;
}

int Graph::GetAmountOfNodes()
{
	return nodes.size();
}

int Graph::GetAmountOfComponents()
{
	return components.size();
}

void Graph::GraphIsReady()//when our graph is ready we should create components
{
	std::map<Node*, Component*> temp;
	for (int i = 1; i < nodes.size(); i++)//create the component
	{
		Find(nodes[i]);
		if (nodes[i]->GetRoot() == nodes[i])
		{
			components.push_back(AddComponent());
			temp.emplace(nodes[i], components[components.size()-1]);
		}
	}
	for (int i = 1; i < nodes.size(); i++)//add nodes to components
	{
		temp.find(nodes[i]->GetRoot())->second->AddNode(nodes[i]);
	}
}

std::string Graph::FindGraphIsomorphism(Graph& A, Graph& B)
{
	if (A.GetAmountOfEdges() != B.GetAmountOfEdges() ||
		A.GetAmountOfComponents() != B.GetAmountOfComponents() ||
		A.GetAmountOfNodes() != B.GetAmountOfNodes())
		return "";
	std::vector<bool> shown(A.components.size(), false);
	std::vector<std::vector<std::string>> table(A.components.size(),
		std::vector<std::string>(A.components.size(), ""));
	for (int i = 0; i < table.size(); i++)
		for (int j = i; j < table[i].size(); j++)
		{
			if (A.components[i]->Size() == B.components[j]->Size() &&
				A.components[i]->GetNumberOfEdges() == B.components[j]->GetNumberOfEdges())
				table[i][j] = Component::FindIsomorphism(*A.components[i], *B.components[j]);
			shown[i] = true; shown[j] = true;
		}
	std::string ans; 
	for (auto i : shown) // if ew have no izomorphizm
		if (!i) return "";
	for (int i = 0; i < table.size(); i++)
	{
		bool temp = false;
		for (int j = i + 1; j < table[i].size(); j++)
		{
			if (table[i][j] != "")
				ans += table[i][j];
			temp = true;
			break;
		}
		if (temp) continue;
		if (table[i][i] != "")
			ans += table[i][i];
		else
			return "ERROR";
	}
	return ans;
}

Node* Graph::AddNode(int i)
{
	Node * temp = new Node(i);
	return temp;
}

Component* Graph::AddComponent()
{
	Component* temp = new Component();
	return temp;
}
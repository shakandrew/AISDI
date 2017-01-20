#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

int main()
{
	size_t n, m;
	ifstream finA("11.in");
	ifstream finB("12.in");
	finA >> n;
	finB >> m;
	Graph A(n), B(m);
	while (!finA.eof())
	{
		int x, y;
		finA >> x >> y;
		A.Union(x, y);
	}

	while (!finB.eof())
	{
		int x, y;
		finB >> x >> y;
		B.Union(x, y);
	}
	finA.close();
	finB.close();
	A.GraphIsReady();
	B.GraphIsReady();
	std::string ans =Graph::FindGraphIsomorphism(A, B);
	if (ans == "")
		std::cout << "There is no izomorphizm in current graphs";
	else
		std::cout << ans;
	getchar();
	return 0;
}
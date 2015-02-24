#include <stdio.h>
#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
	Graph graph = Graph();
	graph.CreateGrid(4, 4, 100, 100);

	cout << graph;
	vector<int>path = graph.FindPath(1, 15);
	for (int i = 0; i < path.size(); i++) {
		cout << path[i] << ", ";
	}
	cout << endl;
	system("pause");
	return 0;
}
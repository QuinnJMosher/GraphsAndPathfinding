#include <stdio.h>
#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
	Graph graph = Graph();
	graph.CreateGrid(4, 4, 100, 100);

	cout << graph;
	cout << endl;
	system("pause");
	return 0;
}
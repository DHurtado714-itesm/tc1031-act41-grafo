/*
 * main.cpp
 *
 *  Created on: 3/11/2018
 *      Author: pperezm
 */
#include <iostream>
#include <cstring>
#include "ugraph.h"

int main(int argc, char* argv[]) {
	/***********************************************************/
	/************************ UMatrixGraph *********************/
	/***********************************************************/
	UMatrixGraph<char> umg(5);
	
	umg.addEdge('A', 'B');
	umg.addEdge('B', 'C');
	umg.addEdge('B', 'D');
	umg.addEdge('C', 'E');
	umg.addEdge('D', 'C');
	umg.addEdge('E', 'D');
	
	std::cout << umg.toString();
	
	std::set<char> edges = umg.getConnectionFrom('B');
	std::set<char>::iterator itr;
	
	std::cout << "B ->\t";
	for (itr = edges.begin(); itr != edges.end(); itr++) {
		std::cout << (*itr) << "\t";
	}
	std::cout << "\n\n";
	
	std::cout << "DFS(B) ->\t";
	edges = dfs('B', &umg);
	for (itr = edges.begin(); itr != edges.end(); itr++) {
		std::cout << (*itr) << "\t";
	}
	std::cout << "\n\n";
	
	std::cout << "BFS(B) ->\t";
	edges = bfs('B', &umg);
	for (itr = edges.begin(); itr != edges.end(); itr++) {
		std::cout << (*itr) << "\t";
	}
	std::cout << "\n\n";
	
	/***********************************************************/
	/************************ UListGraph ***********************/
	/***********************************************************/
	UListGraph<char> ulg(5);
	
	ulg.addEdge('A', 'B');
	ulg.addEdge('B', 'C');
	ulg.addEdge('B', 'D');
	ulg.addEdge('C', 'E');
	ulg.addEdge('D', 'C');
	ulg.addEdge('E', 'D');
	
	std::cout << ulg.toString();
	
	edges = ulg.getConnectionFrom('B');
	
	std::cout << "B ->\t";
	for (itr = edges.begin(); itr != edges.end(); itr++) {
		std::cout << (*itr) << "\t";
	}
	std::cout << "\n\n";
	
	std::cout << "DFS(B) ->\t";
	edges = dfs('B', &ulg);
	for (itr = edges.begin(); itr != edges.end(); itr++) {
		std::cout << (*itr) << "\t";
	}
	std::cout << "\n\n";
	
	std::cout << "BFS(B) ->\t";
	edges = bfs('B', &ulg);
	for (itr = edges.begin(); itr != edges.end(); itr++) {
		std::cout << (*itr) << "\t";
	}
	std::cout << "\n\n";
	
}

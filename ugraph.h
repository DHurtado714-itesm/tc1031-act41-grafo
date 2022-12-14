/*
 * ugraph.h
 *
 *  Edited on: 8/11/2022
 *      Template: pperezm
 * 		Repurpose: Daniel Hurtado
 */

#ifndef UGRAPH_H_
#define UGRAPH_H_

#include <sstream>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include "exception.h"
#include "header.h"

using namespace std;

/***********************************************************/
/********************** UnweightedGraph ********************/
/***********************************************************/

template<class Vertex>
class UnweightedGraph {
public:
	virtual void addEdge(Vertex, Vertex) = 0;
	virtual bool containsVertex(Vertex) const = 0;
	virtual vector<Vertex> getVertexes() const = 0;
	virtual set<Vertex> getConnectionFrom(Vertex) const = 0;
	virtual string toString() const = 0;
};

/***********************************************************/
/************************ UMatrixGraph *********************/
/***********************************************************/
template<class Vertex>
class UMatrixGraph : public UnweightedGraph<Vertex>{
private:
	int next, size;
	bool direction;
	vector<Vertex> vertexes;
	vector<vector<bool> > edges;

	int indexOf(Vertex v) const;

public:
	UMatrixGraph(int, bool dir = true);
	void addEdge(Vertex from, Vertex to);
	bool containsVertex(Vertex v) const;
	vector<Vertex> getVertexes() const;
	set<Vertex> getConnectionFrom(Vertex v) const;
	string toString() const;
};

template <class Vertex>
UMatrixGraph<Vertex>::UMatrixGraph(int max, bool dir) {
	size = max;
	if (size == 0) {
        throw RangeError();
	}

	next = 0;
	direction = dir;
	vertexes.resize(size);
	edges.resize(size);
	for (int i = 0; i < size; i++) {
		edges[i].resize(size, false);
		edges[i][i] = true;
	}
}

template <class Vertex>
int UMatrixGraph<Vertex>::indexOf(Vertex v) const {
	for (int i = 0; i < next; i++) {
		if (vertexes[i] == v) {
			return i;
		}
	}
	return -1;
}

// Add an edge to the graph
template <class Vertex>
void UMatrixGraph<Vertex>::addEdge(Vertex from, Vertex to) {
	int fp = indexOf(from);
	if (fp == -1) {
		if (next == size) {
			throw OutOfMemory();
		}

		vertexes[next++] = from;
		fp = next - 1;
	}

	int tp = indexOf(to);
	if (tp == -1) {
		if (next == size) {
			throw OutOfMemory();
		}

		vertexes[next++] = to;
		tp = next - 1;
	}

	edges[fp][tp] = true;
	if (!direction) {
		edges[tp][fp] = true;
	}
}

// Returns true if the graph contains the vertex v
template <class Vertex>
bool UMatrixGraph<Vertex>::containsVertex(Vertex v) const {
	return (indexOf(v) != -1);
}

// Returns a vector with all the vertexes in the graph
template <class Vertex>
vector<Vertex> UMatrixGraph<Vertex>::getVertexes() const {
	vector<Vertex> result(vertexes);
	return result;
}

// Returns a set with the vertexes that are connected to the given vertex
template <class Vertex>
set<Vertex> UMatrixGraph<Vertex>::getConnectionFrom(Vertex v) const {
	int i = indexOf(v);
	if (i == -1) {
		throw NoSuchElement();
	}

	set<Vertex> result;
	for (int j = 0; j < next; j++) {
		if (i != j && edges[i][j]) {
			result.insert(vertexes[j]);
		}
	}
	return result;
}

template <class Vertex>
string UMatrixGraph<Vertex>::toString() const {
	stringstream aux;

	for (int i = 0; i < next; i++) {
		aux << vertexes[i] << "\t";
		for (int j = 0; j < next; j++) {
			aux << edges[i][j] << "\t";
		}
		aux << "\n";
	}
	aux << "\n";
	return aux.str();
}

/***********************************************************/
/************************ UListGraph ***********************/
/***********************************************************/

template<class Vertex>
class UListGraph : public UnweightedGraph<Vertex>{
private:
	bool direction;
	set<Vertex> vertexes;
	map<Vertex, set<Vertex> > edges;

public:
	UListGraph(bool dir = true);
	void addEdge(Vertex from, Vertex to);
	bool containsVertex(Vertex v) const;
	vector<Vertex> getVertexes() const;
	set<Vertex> getConnectionFrom(Vertex v) const;
	string toString() const;
};

template <class Vertex>
UListGraph<Vertex>::UListGraph(bool dir) {
	direction = dir;
}

// Method: addEdge
// Description: Agrega un arco entre dos v??rtices
template <class Vertex>
void UListGraph<Vertex>::addEdge(Vertex from, Vertex to) {
	typename set<Vertex>::iterator it;
	typename list<Vertex>::iterator j;

	it = vertexes.find(from);
	if (it == vertexes.end()) {
		vertexes.insert(from);
		edges.insert(pair<Vertex,set<Vertex> >(from, set<Vertex>()));
	}

	it = vertexes.find(to);
	if (it == vertexes.end()) {
		vertexes.insert(to);
		edges.insert(pair<Vertex,set<Vertex> >(to, set<Vertex>()));
	}

	edges[from].insert(to);
	if (!direction) {
		edges[to].insert(from);
	}
}

// Method: containsVertex
// Description: Retorna true si el v??rtice v est?? en el grafo
template <class Vertex>
bool UListGraph<Vertex>::containsVertex(Vertex v) const {
	return (vertexes.find(v) != vertexes.end());
}

// returns a vector with all the vertexes of the graph
template <class Vertex>
vector<Vertex> UListGraph<Vertex>::getVertexes() const {
	vector<Vertex> result(vertexes.begin(), vertexes.end());
	return result;
}

// returns a set with the vertexes that are connected to the given vertex
template <class Vertex>
set<Vertex> UListGraph<Vertex>::getConnectionFrom(Vertex v) const {
	set<Vertex> result(edges.at(v));
	return result;
}

// returns a string with the graph representation
template <class Vertex>
string UListGraph<Vertex>::toString() const {
	stringstream aux;

	typename set<Vertex>::iterator i;
	typename set<Vertex>::const_iterator j;

	for (i = vertexes.begin(); i != vertexes.end(); i++) {
		aux << (*i) << "\t";
		for (j = edges.at((*i)).begin(); j != edges.at((*i)).end(); j++) {
			aux << (*j) << "\t";
		}
		aux << "\n";
	}
	aux << "\n";
	return aux.str();
}

/***********************************************************/
/**************************** DFS **************************/
/***********************************************************/


// Method: DFS
// Description: Depth First Search

template <class Vertex>
set<Vertex> dfs(const Vertex& origin,
	const UnweightedGraph<Vertex>* graph) {

	set<Vertex> visited;
	stack<Vertex> pending;
	typename set<Vertex>::iterator itr;

	pending.push(origin);
	while (!pending.empty()) {
		Vertex v = pending.top(); pending.pop();
		if (visited.find(v) == visited.end()) {
			visited.insert(v);
			set<Vertex> connected =
					graph->getConnectionFrom(v);
			for (itr = connected.begin();
					itr != connected.end(); itr++) {
				pending.push( (*itr) );
			}
		}
	}
	return visited;
}

// Complexity: O(V + E)

/***********************************************************/
/**************************** BFS **************************/
/***********************************************************/


// Method: BFS
// Description: Breadth First Search

template <class Vertex>
set<Vertex> bfs(const Vertex& origin, const UnweightedGraph<Vertex>* graph) {
	set<Vertex> visited;
	queue<Vertex> pending;
	typename set<Vertex>::iterator itr;

	pending.push(origin);
	while (!pending.empty()) {
		Vertex v = pending.front(); pending.pop();
		if (visited.find(v) == visited.end()) {
			visited.insert(v);
			set<Vertex> connected =
					graph->getConnectionFrom(v);

			for (itr = connected.begin();
					itr != connected.end(); itr++) {
				pending.push( (*itr) );
			}
		}
	}
	return visited;
}

// Complexity: O(V + E)

#endif

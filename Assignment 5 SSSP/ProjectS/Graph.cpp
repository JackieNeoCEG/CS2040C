#include "Graph.h"
#include "heap.h"

std::ostream& operator<<(std::ostream& os, nodeWeightPair const& n) {
	return os << " (idx:" << n._node << " w:" << n._weight << ")";
}


Graph::Graph(int n)
{
	_al = new List<nodeWeightPair> [n];
	_nv = n;
}

int Graph::shortestDistance(int s, int d) {
	Heap<nodeWeightPair> queue;

	const int INF = 1000000; //large enough no.

	int* dist = new int[_nv];
	int* path = new int[_nv];

	for (int i = 0; i < _nv; ++i) {
		dist[i] = INF;
		path[i] = -1;
	}
	dist[s] = 0;

	queue.insert(nodeWeightPair(s, 0)); //start from source node

	if (s == d) {
		cout << "Path: " << s << endl;
		delete[] path;
		delete[] dist;
		return 0; // Distance from a node to itself is 0
	}

	while (!queue.empty()) {
		nodeWeightPair u = queue.extractMax(); //weights inverted so extracted node is min instead
		int uNode = u.nodeIndex();
		int uDist = -u.weight();  //weights are corrected back again



		if (uNode == d) {
			int currentNode = d; //start from destination first then reverse
			int pathLength = 0;
			int* pathArray = new int[_nv];  //backtracked nodes as array
		
			while (currentNode != -1) {
				pathArray[pathLength] = currentNode;
				pathLength++;
				currentNode = path[currentNode]; //traverse in reverse
			}

			// Print the path as an array
			cout << "Path: ";
			for (int i = pathLength - 1; i >= 0; i--) {
				cout << pathArray[i];
				if (i != 0) {  // Only add a space if it's not the last element
					cout << " ";
				}
			}
			cout << endl;

			//delete[] pathArray;
			delete[] path;
			delete[] dist;
			return uDist;  // Found shortest path to destination node
		}

		if (uDist > dist[uNode]) {
			continue;
		}

		List<nodeWeightPair>& adjList = _al[uNode];
		adjList.start();
		while (!adjList.end()) {
			int v = adjList.current().nodeIndex();
			int weight = adjList.current().weight();

			if (uDist + weight < dist[v]) { //check if new path is shorter
				dist[v] = uDist + weight;
				queue.insert(nodeWeightPair(v, -dist[v]));  //updates shortest dist
				path[v] = uNode;
			}

			adjList.next();  // Move to the next element
		}
	}

	/*
	if (dist[d] == INF) {
		// Destination node is not reachable using Dijkstra's algorithm
		// Run Bellman-Ford as a fallback

		// Reset dist array
		for (int i = 0; i < _nv; ++i) {
			dist[i] = INF;
			path[i] = -1;
		}

		// Bellman-Ford Algorithm
		for (int i = 0; i < _nv - 1; ++i) {
			for (int u = 0; u < _nv; ++u) {
				List<nodeWeightPair>& adjList = _al[u];
				adjList.start();
				while (!adjList.end()) {
					int v = adjList.current().nodeIndex();
					int weight = adjList.current().weight();
					if (dist[u] != INF && dist[u] + weight < dist[v]) {
						dist[v] = dist[u] + weight;
						path[v] = u;
					}
					adjList.next();
				}
			}
		}
	}
	*/
	delete[] dist;
	delete[] path;
	return -1;
}

void Graph::addEdge(int s, int d, int w)
{
	_al[s].insertHead(nodeWeightPair(d, w));
}

void Graph::printGraph()
{
	for (int i=0; i < _nv; i++)
	{
		cout << "Node " << i << ": ";
		for (_al[i].start(); !_al[i].end(); _al[i].next())
			cout << " (" << _al[i].current().nodeIndex() << "," << _al[i].current().weight() << ")";
		cout << endl;

	}

}
Graph::~Graph()
{

	delete[] _al;

}
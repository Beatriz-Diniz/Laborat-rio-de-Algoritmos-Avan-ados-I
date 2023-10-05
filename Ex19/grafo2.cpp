#include <iostream>
#include <vector>
#include <algorithm>

//Kruskal
class UnionFind{
private:
	std::vector<int> parent, rank;

public:
	UnionFind(int numCities){
		parent.resize(numCities);
		rank.resize(numCities);

		for(int i = 0; i < numCities; i++){
			parent[i] = i;
			rank[i] = 0;
		}
	}

	int find(int x){
		if(parent[x] != x)
			parent[x] = find(parent[x]);
		return parent[x];
	}

	void unite(int x, int y){
		int rootX = find(x);
		int rootY = find(y);

		if(rootX != rootY){
			if(rank[rootX] < rank[rootY])
				parent[rootX] = rootY;
			else if(rank[rootX] > rank[rootY])
				parent[rootY] = rootX;
			else{
				parent[rootX] = rootY;
				rank[rootY]++;
			}
		}
	} 
};

//Sort the edges based on the cost (third element)
bool compareEdges(const std::vector<int>& cityA, const std::vector<int>& cityB){
	return cityA[2] < cityB[2];
}

int main(){
	int numCities = 0, numRoads = 0;
	std::cin >> numCities >> numRoads;

	//Read the edge information
	std::vector<std::vector<int>> edges(numRoads, std::vector<int>(3));
	for(int i = 0; i < numRoads; i++)
		std::cin >> edges[i][0] >> edges[i][1] >> edges[i][2];

	sort(edges.begin(), edges.end(), compareEdges);

	UnionFind uf(numCities + 1);
	long long totalCost = 0;
	int numEdges = 0;

	for(const std::vector<int>& edge : edges){
		int sourceCity = edge[0];
		int destinationCity = edge[1];
		long long cost = edge[2];

		//Check if the cities are connected
		if(uf.find(sourceCity) != uf.find(destinationCity)){
			uf.unite(sourceCity, destinationCity);
			totalCost += cost;
			numEdges++;
		}

		//All cities are connected, we can stop adding edges
		if(numEdges == numCities -1)
			break;
	}

	if(numEdges == numCities - 1)
		std::cout << totalCost << std::endl;
	else
		std::cout << "IMPOSSIBLE" << std::endl;

	return 0;
}

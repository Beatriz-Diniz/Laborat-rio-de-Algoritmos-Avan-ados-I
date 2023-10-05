#include <iostream>
#include <limits>

const long long INF = (1LL << 60);

void floydWarshall(long long** distances, int numCities){
	for(int k = 0; k < numCities; k++){
		for(int i = 0; i < numCities; i++){
			if(distances[i][k] != INF){
				for(int j = 0; j < numCities; j++){
					if(distances[k][j] != INF)
						distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
				}
			}
		}
	}
}

int main() {
	int numCities = 0, numRoads = 0, numQueries = 0;
	std::cin >> numCities >> numRoads >> numQueries;

	long long** distances = new long long* [numCities];
	for(int i = 0; i < numCities; i++){
		distances[i] = new long long[numCities];
		std::fill_n(distances[i], numCities, INF);
	}

	//Initialize distance matrix with direct road lengths
	for(int i = 0; i < numCities; i++)
		distances[i][i] = 0;

	//Read road information and update the distance matrix
	for(int i = 0; i < numRoads; i++){
		int cityA = 0, cityB = 0;
		long long weight = 0;

		std::cin >> cityA >> cityB >> weight;

		distances[cityA - 1][cityB - 1] = std::min(distances[cityA - 1][cityB - 1], weight);
		distances[cityB - 1][cityA - 1] = std::min(distances[cityB - 1][cityA - 1], weight);
	}

	floydWarshall(distances, numCities);

	// Process the queries
	for(int i = 0; i < numQueries; i++){
		int cityA = 0, cityB = 0;
		std::cin >> cityA >> cityB;

		long long shortestPath = distances[cityA - 1][cityB - 1];
		if(shortestPath == INF || shortestPath < 0)
			shortestPath = -1;

		std::cout << shortestPath << std::endl;
	}

	// Clean up memory
	for(int i = 0; i < numCities; i++)
		delete[] distances[i];
	delete[] distances;

	return 0;
}

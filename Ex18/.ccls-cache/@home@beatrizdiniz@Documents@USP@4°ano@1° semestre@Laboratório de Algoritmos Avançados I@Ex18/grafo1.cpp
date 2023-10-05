#include <iostream>
#include <vector>
#include <limits>

const long long INF = std::numeric_limits<long long>::max(); 

int main(){
	int numCities = 0, numRoads = 0, numQueries = 0;
	std::cin >> numCities >> numRoads >> numQueries;
	
	std::vector<std::vector<long, long>> distances(numCities, std::vector<long, long>(numCities, INF));

	
	return 0;
}

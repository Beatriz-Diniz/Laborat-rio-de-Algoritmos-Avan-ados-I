#include <iostream>
#include <vector>

bool canWalkNights(std::vector<int>& distances, int nNights, int maxDist){
	int nightsWalked = 0;
	int currentDist = 0;

	for(long unsigned int i = 0; i < distances.size(); i++){
		currentDist += distances[i];
		if(currentDist > maxDist){
			currentDist = distances[i];
			nightsWalked++;
			if(nightsWalked > nNights)
				return false;
		}
	}
	return true;
}


int minMaxDistance(std::vector<int>& distances, int nNights, int left, int right){
	if(left == right)
		return distances[left];
	
	int mid = left + (right - left)/2;
	int maxLeft = minMaxDistance(distances, nNights, left, mid);
	int maxRight = minMaxDistance(distances, nNights, mid+1, right);
	int maxDist = std::max(maxLeft, maxRight);

	while(!canWalkNights(distances, nNights, maxDist))
		maxDist++;
	
	return maxDist;
}

int main(){
	int nCampsites = 0, nNights = 0;
	while(std::cin >> nCampsites >> nNights){

		std::vector<int> distances(nCampsites + 1);
		for(int i = 0; i<=nCampsites; i++)
			std::cin >> distances[i];
	
		std::cout <<  minMaxDistance(distances, nNights, 0, nCampsites) << std::endl;
	}
	return 0;
}

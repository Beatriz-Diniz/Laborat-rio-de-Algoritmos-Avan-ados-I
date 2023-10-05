#include <iostream>
#include <vector>
#include <queue>

bool bfs(std::vector<std::vector<int>>& adj, std::vector<int>& team, int start) {
	std::queue<int> q;
	q.push(start);
	team[start] = 1;

	while(!q.empty()){
		int v = q.front();
		q.pop();

		for(int u : adj[v]){
			if(team[u] == 0){
				team[u] = 3 - team[v];
				q.push(u);
			}else if(team[u] == team[v]){
				return false;
			}
		}
	}

	return true;
}

int main() {
	int numPupils = 0, numFriendships = 0;
	std::cin >> numPupils >> numFriendships;

	std::vector<std::vector<int>> adj(numPupils + 1);
	std::vector<int> team(numPupils + 1);

	for(int i = 0; i < numFriendships; i++){
		int pupils = 0, frieds = 0;
		std::cin >> pupils >> frieds;

		adj[pupils].push_back(frieds);
		adj[frieds].push_back(pupils);
	}

	for(int i = 1; i <= numPupils; i++){
		if(team[i] == 0 && !bfs(adj, team, i)){
			std::cout << "IMPOSSIBLE" << std::endl;
			return 0;
		}
	}

	for(int i = 1; i <= numPupils; i++)
		std::cout << team[i] << " ";

	std::cout << std::endl;

	return 0;
}


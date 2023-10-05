#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Edge {
	int dest;
	long long capacity;
	long long flow;
	int rev;

	Edge(int dest, long long capacity, int rev) : dest(dest), capacity(capacity), flow(0), rev(rev) {}
};

void addEdge(std::vector<std::vector<Edge>>& graph, int src, int dest, long long capacity){
	//forward edge from src to dest
	graph[src].push_back(Edge(dest, capacity, graph[dest].size()));
    
	//backward edge from dest to src
	graph[dest].push_back(Edge(src, 0, graph[src].size() - 1));
}

bool bfs(std::vector<std::vector<Edge>>& graph, int src, int dest, std::vector<int>& level){
	level.assign(graph.size(), -1);
	level[src] = 0;
	
	std::queue<int> q;
	q.push(src);

	while(!q.empty()){
		int currentNode = q.front();
		q.pop();

		for(const Edge& edge : graph[currentNode]){
			int neighbour = edge.dest;
			long long capacity = edge.capacity;
			long long flow = edge.flow;

			//if the node is not visited and there is residual capacity on the edge
			if(level[neighbour] == -1 && capacity > flow){
				level[neighbour] = level[currentNode] + 1;
				q.push(neighbour);
			}
		}
	}

	return level[dest] != -1;
}

long long sendFlow(std::vector<std::vector<Edge>>& graph, int source, int dest, std::vector<int>& level, std::vector<std::size_t>& ptr, long long flow){
	//if we have reached the destination node
	if (source == dest)
		return flow;

	while(ptr[source] < graph[source].size()){
		Edge& edge = graph[source][ptr[source]];

		if(level[edge.dest] == level[source] + 1 && edge.capacity > edge.flow){
            
			//find the minimum of the remaining flow and the capacity of the edge
			long long minCap = std::min(flow, edge.capacity - edge.flow);
            
			//recursively send flow along the path
			long long tempFlow = sendFlow(graph, edge.dest, dest, level, ptr, minCap);

			if(tempFlow > 0){
				//update the flow in the current edge
				edge.flow += tempFlow;
				
				//update the flow in the reverse edge
				graph[edge.dest][edge.rev].flow -= tempFlow;
               
				return tempFlow;
			}
		}

        ptr[source]++;
	}

    	return 0;
}

//function to find the maximum flow in the graph using Dinic's Algorithm
long long maxFlow(std::vector<std::vector<Edge>>& graph, int src, int dest) {
	int lenGraph = graph.size();
	long long maxFlow = 0;

	std::vector<int> level(lenGraph);
	std::vector<std::size_t> ptr(lenGraph);
	
	while(bfs(graph, src, dest, level)){
		//reset the pointer array
		std::fill(ptr.begin(), ptr.end(), 0);
		long long flow = 0;

		//send flow along the augmenting path until no more flow can be sent
		while((flow = sendFlow(graph, src, dest, level, ptr, LLONG_MAX)) > 0)
			maxFlow += flow;
	}

	return maxFlow;
}

int main() {
	int numComputers = 0, numConnections = 0;
	int src = 0;
    
	std::cin >> numComputers >> numConnections;
    
	int dest = numComputers - 1;
	std::vector<std::vector<Edge>> graph(numComputers);

  
	for(int i = 0; i < numConnections; i++){
		int computerA = 0, computerB = 0;
		long long speed = 0;
		
		std::cin >> computerA >> computerB >> speed;
		addEdge(graph, computerA - 1, computerB - 1, speed);
	}

	//find the maximum flow from source to destination
	std::cout << maxFlow(graph, src, dest) << std::endl;

	return 0;
}


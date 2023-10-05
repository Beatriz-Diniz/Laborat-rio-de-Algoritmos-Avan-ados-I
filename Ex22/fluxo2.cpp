#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Edge{
    std::size_t destination;
    int capacity;
    std::size_t reverseEdge;
};

// Function to add an edge to the graph
void addEdge(std::vector<std::vector<Edge>>& graph, std::size_t source, std::size_t destination, int capacity){
    graph[source].push_back({ destination, capacity, graph[destination].size() });
    graph[destination].push_back({ source, 0, graph[source].size() - 1 });
}

// Breadth-First Search (BFS) algorithm to find augmenting paths
bool BFS(const std::vector<std::vector<Edge>>& graph, std::vector<int>& levels, std::size_t source, std::size_t target){
    std::fill(levels.begin(), levels.end(), -1);
    levels[source] = 0;

    std::queue<std::size_t> q;
    q.push(source);

    while (!q.empty()){
        std::size_t currentVertex = q.front();
        q.pop();

        for(const Edge& e : graph[currentVertex]){
            if(e.capacity > 0 && levels[e.destination] < 0){
                levels[e.destination] = levels[currentVertex] + 1;
                q.push(e.destination);
            }
        }
    }

    return levels[target] >= 0;
}

// Depth-First Search (DFS) algorithm to find augmenting paths and update flow
int DFS(std::vector<std::vector<Edge>>& graph, std::vector<int>& levels, std::vector<std::size_t>& iterators, std::size_t currentVertex, std::size_t targetVertex, int flow){
    if (currentVertex == targetVertex || flow == 0) 
        return flow;

    for(std::size_t& i = iterators[currentVertex]; i < graph[currentVertex].size(); i++){
        Edge& e = graph[currentVertex][i];
        if(e.capacity > 0 && levels[currentVertex] + 1 == levels[e.destination]){
            int minFlow = std::min(flow, e.capacity);
            int currentFlow = DFS(graph, levels, iterators, e.destination, targetVertex, minFlow);
            
		  if(currentFlow > 0){
                e.capacity -= currentFlow;
                graph[e.destination][e.reverseEdge].capacity += currentFlow;
                return currentFlow;
            }
        }
    }

    return 0;
}

// Ford-Fulkerson algorithm to find the maximum flow in a network
int maxFlow(std::vector<std::vector<Edge>>& graph, std::size_t source, std::size_t target){
    int flow = 0;
    std::vector<int> levels(graph.size(), 0);
    std::vector<std::size_t> iterators(graph.size(), 0);

    while(BFS(graph, levels, source, target)){
        std::fill(iterators.begin(), iterators.end(), 0);
        int currentFlow = 0;
        
	   while ((currentFlow = DFS(graph, levels, iterators, source, target, std::numeric_limits<int>::max())) > 0)
            flow += currentFlow;
    }

    return flow;
}

// Depth-First Search (DFS) to find all vertices reachable from the source
void findReachableVertices(const std::vector<std::vector<Edge>>& graph, std::vector<bool>& visited, std::vector<std::vector<bool>>& traversed, std::size_t source){
    visited[source] = true;

    for(const Edge& e : graph[source]){
        if(!visited[e.destination] && e.capacity > 0)
            findReachableVertices(graph, visited, traversed, e.destination);
    }
}

int main(){
    std::size_t numVertices = 0, numEdges = 0;

    while(std::cin >> numVertices >> numEdges){
        if(numVertices == 0 && numEdges == 0)
            break;

        std::vector<std::vector<Edge>> graph(numVertices + 1);
        for(std::size_t i = 0; i < numEdges; i++){
            std::size_t source = 0, destination = 0;
            int capacity = 0;
            std::cin >> source >> destination >> capacity;

            addEdge(graph, source, destination, capacity);
            addEdge(graph, destination, source, capacity);
        }

        maxFlow(graph, 1, 2);

        std::vector<bool> visited(numVertices + 1, false);
        std::vector<std::vector<bool>> traversed(numVertices + 1, std::vector<bool>(numVertices + 1, false));

        findReachableVertices(graph, visited, traversed, 1);

        for(std::size_t i = 1; i <= numVertices; i++){
            if(!visited[i])
                continue;

            for(const Edge& e : graph[i]){
                if(!visited[e.destination] && !traversed[i][e.destination]){
                    std::cout << i << " " << e.destination << std::endl;
                    traversed[i][e.destination] = traversed[e.destination][i] = true;
                }
            }
        }

        std::cout << std::endl;
    }

    return 0;
}



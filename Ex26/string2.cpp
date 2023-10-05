#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int MAX_N = 1e5 + 5;

struct Node {
    int length, link;
    std::vector<int> next;
};

void extend(char c, std::vector<Node>& nodes, int& size, int& last) {
    int current = size++;
    int previous = last;
    
    nodes[current].length = nodes[last].length + 1;

    while (previous != -1 && nodes[previous].next[c] == -1) {
        nodes[previous].next[c] = current;
        previous = nodes[previous].link;
    }
    
    if (previous == -1) {
        nodes[current].link = 0;
    } else {
        int nextNode = nodes[previous].next[c];
        
        if (nodes[previous].length + 1 == nodes[nextNode].length) {
            nodes[current].link = nextNode;
        } else {
            int clone = size++;
            nodes[clone] = nodes[nextNode];
            nodes[clone].length = nodes[previous].length + 1;

            while (previous != -1 && nodes[previous].next[c] == nextNode) {
                nodes[previous].next[c] = clone;
                previous = nodes[previous].link;
            }
            
            nodes[nextNode].link = nodes[current].link = clone;
        }
    }
    last = current;
}

void bfs(int start, const std::vector<Node>& nodes, std::vector<int>& distances, std::vector<int>& answer) {
    std::queue<int> queue;
    distances[start] = 0;
    queue.push(start);
    
    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();
        
        answer[distances[current]]++;
        answer[nodes[current].length + 1]--;
        
        for (int next : nodes[current].next) {
            if (next != -1 && distances[next] == -1) {
                distances[next] = distances[current] + 1;
                queue.push(next);
            }
        }
    }
}

int main() {
    std::vector<Node> nodes(2 * MAX_N);
    std::vector<int> distances(2 * MAX_N, -1);
    std::vector<int> answer(MAX_N, 0);
    char S[MAX_N];

    std::cin >> S;
    int length = std::strlen(S);
    int size = 1, last = 0;

    nodes[0].link = -1;

    // Construct the suffix automaton
    for (int i = 0; i < length; i++) {
        int character = S[i] - 'a';
        nodes[last].next.resize(26, -1);
        extend(character, nodes, size, last);
    }

    bfs(0, nodes, distances, answer);

    // Calculate the number of distinct substrings for each length
    for (int i = 1; i <= length; i++) {
        answer[i] += answer[i - 1];
        std::cout << answer[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}


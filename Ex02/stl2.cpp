#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// encontrar o valor medio atual
int Median(priority_queue<long int, vector<long int>, greater<long int>> minHeap, 
            priority_queue<long int> maxHeap){
    
    long int currentMedian = 0;
    if(minHeap.size() > maxHeap.size())
        currentMedian = minHeap.top();
    else if(minHeap.size() < maxHeap.size())
        currentMedian = maxHeap.top();
    else    
        currentMedian = (minHeap.top() + maxHeap.top())/2;

    cout << currentMedian << endl; 
    
    return currentMedian;
}

int main(){
    long int N;
    priority_queue<long int, vector<long int>, greater<long int>> minHeap;
    priority_queue<long int> maxHeap;

    long int currentMedian = -1; 
    while(cin >> N){

        // insere o valor atual dentro de umas das listas de prioridade 
        // se N for menor que a media anterior vai para a maxHeap
        // caso contrario vai para a minHeap
        if (N < currentMedian)
            maxHeap.push(N);
        else 
            minHeap.push(N);
        
        // balanceamento das listas de prioridade
        if (maxHeap.size() > minHeap.size() + 1){
            minHeap.push(maxHeap.top());
            maxHeap.pop();

        }else if(minHeap.size() > maxHeap.size()+1){
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }

        currentMedian = Median(minHeap, maxHeap);      
    }

    return 0;
}
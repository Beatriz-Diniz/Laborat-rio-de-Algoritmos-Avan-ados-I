#include <iostream>
#include <queue>

using namespace std;

void printJobs(queue<pair<int, int>> jobs, int yourJob){
    int time = 0;
    while(!jobs.empty()){
        queue<pair<int, int>> copy = jobs;
        pair<int, int> p; 
        bool canPrint = true;

        //verifica se existe um trabalho com maior prioridade 
        //que o primeiro da fila, se existir o primeiro elemento vai para o fim da fila
        while(!copy.empty()){
            if(copy.front().second > jobs.front().second){
                p.first = jobs.front().first;
                p.second = jobs.front().second;
                jobs.pop();
                jobs.push({p.first, p.second});
                canPrint = false;
                break;
            }
            copy.pop();
        }

        //imprime o primeiro elemento com maior prioridade encontrado
        if(canPrint){
            time++;
            if(jobs.front().first == yourJob){
                cout << time << endl;
                return;
            }
            jobs.pop();
        }
    }
}

//criando a fila inicial de impressoes
void queueJobs(){
    int  nJobs, yourJob;
    cin >> nJobs >> yourJob;

    queue<pair<int, int>> jobs;

    for(int j = 0; j < nJobs; j++){
        int priorities;
        cin >> priorities;

        jobs.push({j, priorities});
    }

    printJobs(jobs, yourJob);

}

int main(){
    
    int testCases;    
    cin >> testCases;

    for(int i = 0; i<testCases; i++){
        queueJobs();
    }
    return 0;
}
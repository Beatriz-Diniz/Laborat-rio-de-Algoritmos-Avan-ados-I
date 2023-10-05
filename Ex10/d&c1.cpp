#include <iostream>
#include <cmath>
#include <vector>

struct Query{
    int L, R;
};

// faz o preprocessamento do vetor e preenche a tabela esparsa(lookup)
void preprocess(std::vector<int>& array, int N, std::vector<std::vector<int>>& lookup){
    for (int i = 0; i < N; i++) 
        lookup[i][0] = i;

    for (int j = 1; (1 << j) <= N; j++){
        for (int i = 0; (i + (1 << j) - 1) < N; i++){
            if (array[lookup[i][j - 1]] < array[lookup[i + (1 << (j - 1))][j - 1]]) 
                lookup[i][j] = lookup[i][j - 1];
             else 
                lookup[i][j] = lookup[i + (1 << (j - 1))][j - 1];
        }
    }
}

// retorna o menor valor em um intervalo
int query(std::vector<int>& array, std::vector<std::vector<int>>& lookup, int L, int R){

    // encontra a maior potencia de dois dentro do intervalo
    int j = (int)log2(R - L + 1);
    
    if (array[lookup[L][j]] <= array[lookup[R - (1 << j) + 1][j]]) 
        return array[lookup[L][j]];
    else 
        return array[lookup[R - (1 << j) + 1][j]];
}

void RMQ(std::vector<int>& array, int N, Query *q, int Q) {
    int maxJ = 0;
    int size = 1;
    
    // encontra o número máximo de bits necessário para 
    // representar o índice da tabela esparsa
    while (size < N) {
        size <<= 1;
        maxJ++;
    }
    
    // tabela esparsa que armazena os índices dos elementos mínimos 
    // em intervalos de tamanho potência de 2
    std::vector<std::vector<int>> lookup(N, std::vector<int>(maxJ));
    preprocess(array, N, lookup);
    for (int i = 0; i < Q; i++){
        int L = q[i].L, R = q[i].R;
        std::cout << query(array, lookup, L, R) << std::endl;
    }
}

int main(){
    int N = 0, Q = 0;
    std::cin >> N;

    std::vector<int> array(N);
    for(int i = 0; i<N; i++)
        std::cin >> array[i];

    std::cin >> Q;
    Query *q = new Query[Q];
    for(int i = 0; i<Q; i++)
        std::cin >> q[i].L >> q[i].R;

    RMQ(array, N, q, Q);

    delete[]q;
    return 0;
}
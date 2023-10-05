#include <iostream>
#include <vector>

int countPaths(int N, const std::vector<std::vector<char>>& grid){
	std::vector<std::vector<int>> dp(N, std::vector<int>(N,0));
	int MOD = 1000000007;	
	//Preenche a ultima posicao com 1
	dp[N-1][N-1] = 1;

	// Preenche a tabela de baixo para cima
	for (int i = N - 1; i >= 0; i--) {
		for (int j =  N - 1; j >= 0; j--) {
			if (grid[i][j] == '.') {
			// Verifica se é possível mover para a direita
			if (j < N - 1)
				dp[i][j] = (dp[i][j] + dp[i][j + 1]) % MOD;
			// Verifica se é possível mover para baixo
			if (i < N - 1)
				dp[i][j] = (dp[i][j] + dp[i + 1][j]) % MOD;
			}
		}
	}

	return dp[0][0];
}

int main(){
      int N = 0;
      std::cin >> N;
      std::vector<std::vector<char>> grid(N, std::vector<char>(N));
	for(int i = 0; i<N; i++)
            for(int j = 0; j<N; j++)
                  std::cin >> grid[i][j];
      std::cout << countPaths(N, grid) << std::endl;
      return 0;
}

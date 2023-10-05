#include <iostream>
#include <vector>

using namespace std;

void backtracking(vector<vector<int>> &field, vector<vector<bool>> &visited,
				  int x, int y, int &minPath, int steps, int L, int C){
	
	//movimentos permitidos dentro do campo
	int dx[] = { -1, 0, 0, 1 };
	int dy[] = { 0, -1, 1, 0 };

    // retorna o menor valor enconrado
	if(y == C-1 || steps > minPath){
        minPath = min(minPath, steps);
        return;
    }

	visited[x][y] = true;

	// percorre um caminho
    for (int i = 0; i < 4; i++){
        int x2 = x + dx[i];
        int y2 = y + dy[i];
        if ((x2 < L && y2 < C) && (x2 >= 0 && y2 >= 0) && field[x2][y2] == 1 && visited[x2][y2] == 0)
            backtracking(field, visited, x2, y2, minPath, steps + 1, L, C);	
    }
		
	visited[x][y] = false;
}



int main(){
	int L = 0, C = 0;
	cin >> L >> C;
	vector<vector<int>> field(L, vector<int>(C, -1));
	for(int i = 0; i<L; i++){
        for(int j = 0; j<C; j++){
			int value = 0;
            cin >> value;
            if(field[i][j] == -1){
                field[i][j] = value;
                //bloquear os vizinhos de 0
                if(value == 0){
                    if(i-1 >=0)
                        field[i-1][j] = 0;
                    if(i+1 < L)
                        field[i+1][j] = 0;
                    if(j-1 >=0)
                        field[i][j-1] = 0;
                    if(j+1 < C)
                        field[i][j+1] = 0;
                }
            }
		}
	}

	int minPath = L*C;

	for (int i = 0; i < L; i++){
		if (field[i][0] == 1){
			vector<vector<bool>> visited(L, vector<bool>(C, false));
			backtracking(field, visited, i, 0, minPath, 0, L, C);
		}
	}

	if(minPath != L*C){
        cout << "Comprimento da rota = " << minPath << endl;
    }
    else{
        cout << "Nao ha caminho valido" << endl;
    }

	return 0;
}
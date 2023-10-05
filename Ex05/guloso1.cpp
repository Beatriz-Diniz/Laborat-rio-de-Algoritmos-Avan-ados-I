#include <iostream>
#include <queue>

using namespace std;

int main(){
    int B = -1, S = -1, _case = 1;

    while(cin >> B >> S && B!=0 && S!=0){
        
        int aux = 0, singleBachelors = 0;
        priority_queue<int, vector<int>, greater<int>> spinsters, bachelors;

        for(int i = 0; i<B; i++){
            cin >> aux;
            bachelors.push(aux);
        }
            
        for(int i = 0; i<S; i++){
            cin >> aux;
            spinsters.push(aux);
        }

        if(B == S || B < S)
            cout << "Case " << _case++ << ": " << singleBachelors << endl;
        else{
            singleBachelors = B-S;
            cout << "Case " << _case++ << ": " << singleBachelors << " " << bachelors.top() << endl;
        }

    }
    return 0;
}
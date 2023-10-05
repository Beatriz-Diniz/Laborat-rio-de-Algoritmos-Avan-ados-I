#include <iostream>
#include <string>

using namespace std;

void largestNumber(string num, long unsigned int k, long unsigned int index){

    char maxNum = num[index];
    int maxNumIndex = index;

    if(index == k || index == num.size()){
        cout << num << endl;
        return;
    }

    // encontra o maior valor e su posicao
    for(long unsigned int i = index; i < num.size(); i++){
        if(num[i] >= maxNum){
            maxNum = num[i];
            maxNumIndex = i;
        }
    }

    // troca os valores da posicao atual com a posicao com maio valor    
    swap(num[index], num[maxNumIndex]);
    largestNumber(num, k, index+1);
}

int main(){
    string num;
    long unsigned int k;

    while(cin >> num >> k){
        largestNumber(num, k, 0);
    }

    return 0;
}
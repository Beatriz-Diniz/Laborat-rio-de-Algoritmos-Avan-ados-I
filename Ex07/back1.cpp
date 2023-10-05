#include <iostream>
#include <vector>

using namespace std;

void generateStrings(string str, long unsigned int index){
    
    // imprime a nova string 
    if(index == str.size()-1){
        cout << str << endl;
        return;
    }
        
    // string sem o espaço em branco
    generateStrings(str, index+1);

    // adiciona o espaço em branco
    str = str.substr(0, index+1) + " " + str.substr(index+1);
    generateStrings(str, index+2);
}

int main(){
    string str;
    
    while(cin >> str){
        generateStrings(str, 0);
        cout << endl;
    }

    return 0;
}
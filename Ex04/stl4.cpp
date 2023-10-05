#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;
typedef pair<int, int> pi;

void printFirstK(priority_queue<pi, vector<pi>, greater<pi>> queries, 
                 multimap<int, int, greater<int>> queriesCopy){
    
    int Kqueries = 0;
    cin >> Kqueries;

    for(int i = 0; i<Kqueries; i++){
        pair <int, int> top = queries.top();
        cout << top.second << endl;

        // insert a new repetition from ID with a new period
        // the new period is current value + original value of that ID
        queries.push(make_pair((top.first + queriesCopy.find(top.second)->second), top.second));
        queries.pop();
    }

}

int main(){

    string _register;
    priority_queue<pi, vector<pi>, greater<pi>> queries;
    multimap<int, int, greater<int>> queriesCopy;

    cin >> _register;
    while(_register[0] != '#'){
        int id = 0;
        int period = 0;

        cin >> id >> period;

        queries.push(make_pair(period, id));
        
        // save a copy of original values from period
        queriesCopy.insert(pair<int, int>(id, period));
        _register.clear();
        cin >> _register;
    }

    printFirstK(queries, queriesCopy);
    
    return 0;
}
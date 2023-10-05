#include <iostream>
#include <map>

using namespace std;

int main(){
    int _cases = 0;
    cin >> _cases; 
    
    for(int i= 0; i <_cases; i++){
        // sort map in descending order using the keys
        multimap<double, int, greater<double>> jobs;
        double  day, fine;
        int N = 0;
        cin >> N;

        for(int j = 0; j<N; j++){
            cin >> day >> fine;
            jobs.insert({fine/day, j+1});
        }

        multimap<double, int>::iterator it; 
        int count = 0;
 
        // print the sequence of jobs with minimal fine
        for (it = jobs.begin(); it != jobs.end(); it++, count++){
            cout << (*it).second; 
            if(count < N-1)
                cout << " ";
            else
                cout << endl;
        }
         
        if(i < _cases-1)
            cout << endl;
    }   
    return 0;
}
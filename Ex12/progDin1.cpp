#include <iostream>
#include <vector>
#include <algorithm>

int _minCost(int totalDays, std::vector<int> &days, std::vector<int> &prices){
    // Initialize the cost vector with the cost of the first day
    std::vector<int> minCost(totalDays, prices[0]);
    
    for(int i = 0; i < totalDays; i++){
        int count = 0;
        // Calculate the cost using the daily pass
        if(i > 0)
           minCost[i] = minCost[i-1] + prices[0];
        
        // Calculate the cost using the weekly pass
        while(days[count] < days[i] - 6)
             count++;
        minCost[i] = std::min(minCost[i], (minCost[count-1]+ prices[1]));
        count = 0;

        // Calculate the cost using the monthly pass
        while(days[count] < days[i] - 29)
            count++;
        minCost[i] = std::min(minCost[i], (minCost[count-1] + prices[2]));
    }
    return minCost[totalDays-1];
}

int main(){
    std::vector<int> prices(3);
    int totalDays = 0;
    
    std::cin >> totalDays;
    std::vector<int> days(totalDays);

    // Prices of the passes
    for(int i = 0; i < 3; i++)
        std::cin >> prices[i];
 
    // Days on which it will be necessary to stay
    for(int i = 0; i < totalDays; i++)
        std::cin >> days[i];

    // Calculate the minimum cost of passing through all days
    std::cout << _minCost(totalDays, days, prices) << std::endl;
    
    return 0;
}

#include <iostream>
#include <vector>

int _minCoins(std::vector<int> &coins, int totalCoins, int value){
	// Initializes the vector with high values
      std::vector<int> minCoins(value+1, value*2);
	
      minCoins[0] = 0;
      // Finds the minimum number of coins to reach a value greater than 0
      for(int i = 1; i <= value; i++)
	      for(int j = 0; j < totalCoins; j++)
                  if(coins[j] <= i)
                        minCoins[i] = std::min(minCoins[i], minCoins[i - coins[j]] + 1);
            
      return minCoins[value];
}

int main(){
      int totalCases = 0;
      std::cin >> totalCases;

      for(int i = 0; i < totalCases; i++){
            int value = 0, totalCoins = 0;
            std::cin >> value >> totalCoins;
           
            std::vector<int> coins(totalCoins);
            for(int j = 0; j < totalCoins; j++)
                  std::cin >> coins[j];

            // Finds the minimum number of coins needed
            std::cout << _minCoins(coins, totalCoins, value) << std::endl;
      }

      return 0;
}

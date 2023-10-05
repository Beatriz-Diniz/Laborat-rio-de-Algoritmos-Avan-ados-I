#include <iostream>
#include <vector>
#include <algorithm>

//Função que calcula o máximo número de páginas que podem ser compradas com um valor maximo determinado
int maxPages(int numBooks, int maxPrice, const std::vector<int>& bookPrices, const std::vector<int>& bookPages) {
	std::vector<std::vector<int>> dp(numBooks + 1, std::vector<int>(maxPrice + 1, 0));

	for(int book = 1; book <= numBooks; book++){
		for(int price = 1; price <= maxPrice; price++){
			if(bookPrices[book - 1] <= price)
				dp[book][price] = std::max(dp[book - 1][price], dp[book - 1][price - bookPrices[book - 1]] + bookPages[book - 1]);
			else
				dp[book][price] = dp[book - 1][price];
		}
	}

	return dp[numBooks][maxPrice];
}

int main() {
    int numBooks, maxPrice;
    std::cin >> numBooks >> maxPrice;

    std::vector<int> bookPrices(numBooks);
    std::vector<int> bookPages(numBooks);

	for(int i = 0; i < numBooks; i++)
		std::cin >> bookPrices[i];
    

	for(int i = 0; i < numBooks; i++)
		std::cin >> bookPages[i];
    

	std::cout << maxPages(numBooks, maxPrice, bookPrices, bookPages) << std::endl;

	 return 0;
}


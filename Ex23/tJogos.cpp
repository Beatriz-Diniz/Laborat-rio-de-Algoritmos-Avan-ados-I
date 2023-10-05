#include <iostream>
#include <vector>

//Calculate the Nim sum by taking the XOR of heap sizes modulo 4
bool canWin(std::vector<int>& heaps) {
	size_t nimSum = 0;
	for(size_t i = 0; i < heaps.size(); i++)
		nimSum ^= heaps[i] % 4;

    return nimSum != 0;
}

int main() {
	int numTests = 0;
	std::cin >> numTests;

	while(numTests--){
		int numHeaps = 0;
		std::cin >> numHeaps;

		std::vector<int> heaps(numHeaps);
		for(int i = 0; i < numHeaps; i++)
			std::cin >> heaps[i];

		if(canWin(heaps))
			std::cout << "first" << std::endl;
		else
			std::cout << "second" << std::endl;
	}
	return 0;
}


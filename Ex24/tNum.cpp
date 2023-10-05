#include <iostream>
#include <vector>

const long long MOD = 1e9 + 7;

long long expo(long long base, long long pow){
	long long ans = 1;
	
	while(pow){
		if(pow & 1) 
			ans = ans * base % MOD;
		
		base = base * base % MOD;
		pow >>= 1;
	}
	
	return ans;
}

int main(){
	long long divCnt = 1, divSum = 1, divProd = 1, divCnt2 = 1;
	int numParts = 0;
	std::cin >> numParts;


	for(int i = 0; i < numParts; i++){
		long long prime = 0, exponent = 0;
		std::cin >> prime >> exponent;
	    
		divCnt = divCnt * (exponent + 1) % MOD;
		
		//calculate the sum of divisors
		divSum = divSum * (expo(prime, exponent + 1) - 1) % MOD * expo(prime - 1, MOD - 2) % MOD;
		
		//calculate the product of divisors
		divProd = expo(divProd, exponent + 1) * expo(expo(prime, (exponent * (exponent + 1) / 2)), divCnt2) % MOD;
		
		//calculate the exponent for the count of divisors
		divCnt2 = divCnt2 * (exponent + 1) % (MOD - 1);
	}

	std::cout << divCnt << ' ' << divSum << ' ' << divProd << std::endl;

	return 0;
}


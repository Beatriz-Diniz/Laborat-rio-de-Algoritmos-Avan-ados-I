#include <iostream> 
#include <vector>

int editStrLen(const std::string str1, const std::string str2){
	int str1Len = str1.length(), str2Len = str2.length();
	std::vector<std::vector<int>> dp(2, std::vector<int>(str1Len + 1, 0));
	
	// condition when second string is empty
	for(int i = 0; i <= str1Len; i++)
		dp[0][i] = i;

	for(int i = 1; i <= str2Len; i++){
		int currRow = i % 2;
		int prevRow = (i - 1) % 2;
		for(int j = 0; j <= str1Len; j++){
			if(j == 0)
				dp[currRow][j] = i;
			else if (str1[j - 1] == str2[i - 1])
				dp[currRow][j] = dp[prevRow][j -1];
			else
				dp[currRow][j] = 1 + std::min(dp[prevRow][j], std::min(dp[currRow][j - 1], dp[prevRow][j - 1]));
		}
	}
	return dp[str2Len % 2][str1Len];
}

int main(){
	std::string str1;
	std::string str2;

	std::cin >> str1 >> str2;
	std:: cout << editStrLen(str1, str2) << std::endl;

	return 0;
}

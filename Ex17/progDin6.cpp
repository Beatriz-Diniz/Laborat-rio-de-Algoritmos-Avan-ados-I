#include <iostream>
#include <vector>

std::string LCS(const std::string str1, const std::string str2){
	std::string lcs;
	int str1Len = str1.length(), str2Len = str2.length();
	std::vector<std::vector<int>> dp(str1Len + 1, std::vector<int>(str2Len + 1, 0));	
	
	//fill in the table dynamic programming
	for(int i = 1; i <= str1Len; i++){
		for(int j = 1; j <= str2Len; j++){
			if(str1[i - 1] == str2[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	// reconstruct the longest common subsequence
	while(str1Len > 0 && str2Len > 0){
		if(str1[str1Len - 1] == str2[str2Len - 1]){
			lcs = str1[str1Len - 1] + lcs;
			str1Len --;
			str2Len --;
		}else if (dp[str1Len - 1][str2Len] > dp[str1Len][str2Len - 1])
			str1Len--;
		else
			str2Len--;
	}

	return lcs;
}

int main(){
	
	std::string str1, str2;
	std::cin >> str1 >> str2;
	std::cout << LCS(str1, str2) << std::endl;

	return 0;
}

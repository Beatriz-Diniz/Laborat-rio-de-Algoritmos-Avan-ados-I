#include <iostream>
#include <string>
#include <vector>

// Function to calculate the prefix array
std::vector<int> calculatePrefix(const std::string& pattern){
	int patternLength = pattern.length();
	std::vector<int> prefix(patternLength);

	int k = 0;
	for(int i = 1; i < patternLength; i++){
		while(k > 0 && pattern[k] != pattern[i])
			k = prefix[k - 1];

		if(pattern[k] == pattern[i])
			k++;

		prefix[i] = k;
	}
	return prefix;
}

// Function to count the occurrences of the pattern in the text
int countPatternOccurrences(const std::string& text, const std::string& pattern){
	int textLength = text.length();
	int patternLength = pattern.length();
	int count = 0;

	// Calculate the prefix array
	std::vector<int> prefix = calculatePrefix(pattern);

	int k = 0;
	for(int i = 0; i < textLength; i++){
		while(k > 0 && pattern[k] != text[i])
			k = prefix[k - 1];
        
		if(pattern[k] == text[i])
			k++;
     
		if(k == patternLength){
			count++;
			k = prefix[k - 1];
		}
	}
	return count;
}

int main(){
	std::string text, pattern;
	std::cin >> text >> pattern;

	// Count the occurrences of the pattern in the text
	int occurrences = countPatternOccurrences(text, pattern);
	std::cout << occurrences << '\n';

	return 0;
}


#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

class StringUtility {
private:
    void dpForLongestSubsequence(const std::string& s1, const std::string& s2, std::vector<std::vector<int>>& dp) {
        const size_t length1 = dp.size(), length2 = dp[0].size();

        for (size_t i = 0; i <= length1; i++) {
            for (size_t j = 0; j <= length2; j++) {
                if (i == 0 || j == 0)
                    dp[i][j] = 0;
                else if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    //adds a separator between each char of s (helper for Manacher's algorithm, see method longestPalindromeLength(..))
    std::string addSeparator(const std::string& s, std::string separator = "|") {
        if (!s.size()) return "";

        std::stringstream ss;
        for (unsigned i = 0; i < s.size(); i++)
            ss << separator << s[i];
        ss << separator;
        return ss.str();
    }

public:
    //computes the length of the longest palindrome in the 'input' string
    //using Manacher's algorithm (https://en.wikipedia.org/wiki/Longest_palindromic_substring)
    unsigned longestPalindromeLength(const std::string& input) {
        const int size_input = input.size();
        const int size_s = 2 * size_input + 1;
        std::string s = addSeparator(input);
        std::vector<int> palindrome_radii(size_s, 0);

        int center = 0, radius = 0, old_center, old_radius, mirrored_center, max_mirrored_radius;
        while (center < size_s) {
            while (center - (radius + 1) >= 0 && center + (radius + 1) < size_s && s[center - (radius + 1)] == s[center + (radius + 1)])
                radius++;

            palindrome_radii[center] = radius;

            old_center = center;
            old_radius = radius;
            center++;
            radius = 0;

            while (center <= old_center + old_radius) {
                mirrored_center = old_center - (center - old_center);
                max_mirrored_radius = old_center + old_radius - center;
                if (palindrome_radii[mirrored_center] < max_mirrored_radius) {
                    palindrome_radii[center] = palindrome_radii[mirrored_center];
                    center++;
                }
                else if (palindrome_radii[mirrored_center] > max_mirrored_radius) {
                    palindrome_radii[center] = max_mirrored_radius;
                    center++;
                }
                else {
                    radius = max_mirrored_radius;
                    break;
                }
            }
        }

        unsigned longest_palindrome_s = 2 * (*max_element(palindrome_radii.begin(), palindrome_radii.end())) + 1;
        return (longest_palindrome_s - 1) / 2;
    }

    //check if a given string s can be an anadrome
    bool canBeAnadrome(const std::string& s) {
        std::map<char, unsigned> occurrences;
        for (unsigned i = 0; i < s.size(); i++)
            occurrences[s[i]] += 1;

        unsigned odd = 0;
        for (auto iter = occurrences.begin(); iter != occurrences.end(); iter++)
            if (iter->second % 2 == 1)
                odd++;

        return odd <= 1 ? true : false;
    }

    int longestCommonSubsequenceLength(const std::string& s1, const std::string& s2) {
        std::vector<std::vector<int>> dp(s1.size() + 1, std::vector<int>(s2.size() + 1)); 
        dpForLongestSubsequence(s1, s2, dp);
        return dp[s1.size()][s2.size()];
    }

    std::string longestCommonSubsequence(const std::string& s1, const std::string& s2) {
        std::vector<std::vector<int>> dp(s1.size() + 1, std::vector<int>(s2.size() + 1));
        dpForLongestSubsequence(s1, s2, dp);
        
        size_t i = s1.size(), j = s2.size();
        std::string longest_common_subsequence; 
        while (i > 0 && j > 0) {
            if (s1[i - 1] == s2[j - 1]) {
                longest_common_subsequence = s1[i - 1] + longest_common_subsequence;
                i--, j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1])
                i--;
            else
                j--;
        }
        
        return longest_common_subsequence;
    }

    int longestPalindromeSubsequenceLength(const std::string& s) {
        const size_t n = s.size();
        std::vector<int> dp(n, 0), dp_prev(n, 0);

        for (int i = n - 1; i >= 0; i--) {
            dp[i] = 1; 
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j])
                    dp[j] = dp_prev[j - 1] + 2;
                else
                    dp[j] = std::max(dp_prev[j], dp[j - 1]);
            }

            swap(dp, dp_prev);
        }

        return dp_prev[n - 1];
    }
};
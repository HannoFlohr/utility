#ifndef ARRAYSTUFF_H_
#define ARRAYSTUFF_H_

#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>
#include <deque>
#include <iostream>

//returns the longest increasing subarray length of vector v
int longestIncreasingSubsequenceLength(std::vector<int>& v) {
	std::vector<int> lis;
	
	for(size_t i=0; i<v.size(); i++) {
		auto it = std::lower_bound(lis.begin(), lis.end(), v[i]);
		
		if(it == lis.end())
			lis.push_back(v[i]);
		else
			*it = v[i];
	}
	
	return lis.size();
}

//generates all subsets of length k of the elements of array a 
std::vector<std::vector<int>> subsets = std::vector<std::vector<int>>();
void makeSubsets(const std::vector<int>& a, const unsigned int& k, std::vector<int> subset=std::vector<int>(), unsigned int index_subset=0, unsigned int index_a=0) {
	if(subset.size()!=k) 
		subset.resize(k);
	
	//k element subset created -> add to subsets 
	if(index_subset == k) {
		subsets.push_back(subset);
		return;
	}
	
	//no more elements in a to add
	if(index_a >= a.size()) return;
	
	subset[index_subset] = a[index_a];
	makeSubsets(a, k, subset, index_subset+1, index_a+1);
	makeSubsets(a, k, subset, index_subset, index_a+1);
}

//returns the maximum subarray sum of 'v' ("Kadane's Algorithm") 
int maxSubarraySum(const std::vector<int>& v) {
	//make sure that the input is not empty
	assert(v.size() > 0);

	int curSum = v[0]; 
	int maxSum = v[0];
	for (unsigned int i = 1; i < v.size(); i++) {
		curSum = std::max(v[i], curSum + v[i]);
		maxSum = std::max(maxSum, curSum);
	}
	return maxSum;
}

//returns the maximum subarray sum of 'v', and sets the 'start' and 'end' indices of the maximum subarray sum
int maxSubarraySumWithIndices(const std::vector<int>& v, unsigned int& start, unsigned int& end) {
	//make sure that the input is not empty
	assert(v.size() > 0);
	
	int maxSum = std::numeric_limits<int>::min();
	int curSum = 0, curStart = 0;
	for (unsigned int i = 0; i < v.size(); i++) {
		curSum += v[i]; 
		if (maxSum < curSum) {
			maxSum = curSum;
			start = curStart;
			end = i;
		}
		if (curSum < 0) {
			curSum = 0;
			curStart = i + 1;
		}
	}
	return maxSum;
}

//returns a vector with the max element for each k-sized subarray of v
std::vector<int> maxSubarrayElements(const std::vector<int>& v, const int& k){
	const int n = v.size();
    std::deque<int> Q(k);
	std::vector<int> results;
    
    int i;
    for(i=0; i<k; i++) {
        while( (!Q.empty()) && v[i] >= v[Q.back()]) 
            Q.pop_back();
        Q.push_back(i);
    }
    for( ; i<n; i++) {
		results.push_back(v[Q.front()]);
        
        while( (!Q.empty()) && Q.front() <= i-k )
            Q.pop_front();

        while( (!Q.empty()) && v[i] >= v[Q.back()]) 
            Q.pop_back();
            
        Q.push_back(i);
    }
	results.push_back(v[Q.front()]);
	return results;
}

#endif 
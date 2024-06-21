#pragma once
#include <vector> 
#include <stdio.h>
#include "StdIOHelper.h"

/*
	computes the solution to the 0/1 knapsack problem:
	maximizing the profit of items with given weights and values for a knapsack of size capacity
*/
void computeMaxProfit(const std::vector<int>& weights, const std::vector<int>& values, int capacity, std::vector<std::vector<int>>& dp) {
	for (int i = 1; i <= values.size(); ++i) {
		int weight = weights[i - 1], value = values[i - 1];

		for (int size = 1; size <= capacity; ++size) {
			//don't pick item
			dp[i][size] = dp[i - 1][size];
			//pick item if picking it leads to better profit 
			if (size >= weight) {
				dp[i][size] = std::max(dp[i][size], dp[i - 1][size - weight] + value);
			}
		}
	}
}

//returns the max profit for the given weights and values for the 0/1 Knapsack problem 
int knapsack01MaxProfit(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
	//rows: items, columns: weight
	std::vector<std::vector<int>> dp(values.size() + 1, std::vector<int>(capacity + 1, 0));
	computeMaxProfit(weights, values, capacity, dp);
	return dp[values.size()][capacity];
}

//returns the items needed to get the max profit for the given weights and values for the 0/1 Knapsack problem 
std::vector<int> knapsack01ItemsForMaxProfit(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
	//rows: items, columns: weight
	std::vector<std::vector<int>> dp(values.size() + 1, std::vector<int>(capacity + 1, 0));
	computeMaxProfit(weights, values, capacity, dp);

	std::vector<int> items;
	for (int i = values.size(); i > 0; --i) {
		//item is needed if the profit when taking the item (dp[i][capacity]) is greater than the profit when not taking it (dp[i-1][capacity])
		if (dp[i][capacity] != dp[i - 1][capacity]) {
			items.push_back(i - 1);
			capacity -= weights[i - 1]; 
		}
	}

	return items;
}
#pragma once
#include <unordered_map>

class DisjointSet {
	std::unordered_map<int, int> parent;
	std::unordered_map<int, int> rank;  //depth of each tree
public:
	DisjointSet(int n) {
		for (int i = 1; i <= n; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}

	int find(int i) {
		if (parent[i] == i)
			return i;
		else
			return find(parent[i]);
	}

	bool Union(int set1, int set2) {
		if (rank[set1] > rank[set2])
			parent[set2] = set1;
		else if (rank[set1] < rank[set2])
			parent[set1] = set2;
		else {
			parent[set1] = set2;
			rank[set2]++;
		}
		return true;
	}
};
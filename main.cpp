
#include "VectorUtility.h"
#include "PrimeGenerator.h"
#include "StringUtility.h"
#include "Trie.h"
#include "ScopedTimer.h"
#include "StdIOHelper.h"
#include<iostream>
#include<math.h>

#include "Knapsack.h"

using namespace std;

void scopedTimerTest() {
	ScopedTimer timer;
	long long sum = 1;
	for (long long i = 0; i < 10000000000; i++) 
		sum *= i;
}

int main() {
	vector<int> weights = { 3,3,5,6 };
	vector<int> values = { 1,4,6,8 };
	cout << knapsack01MaxProfit(weights,values,10) << endl;

	vector<int> items = knapsack01ItemsForMaxProfit(weights, values, 10);
	for (int i : items) cout << i << " "; cout << endl;

	/*TrieNode* root = new TrieNode();
	root->insert("hello");
	cout << root->search("hello") << endl;
	root->insert("helloworld");
	cout << root->search("hellow") << endl;
	root->insert("world");
	root->insert("hell");
	root->insert("h");
	root->remove(root, "hello");
	cout << root->search("hello") << endl;
	cout << root->search("helloworld") << endl;

	root->remove(root, "h");
	cout << root->search("h") << endl;
	cout << root->search("hell") << endl;
	cout << root->search("helloworld") << endl;*/


	//makeSubsets(a,3);

	//for(auto sub:subsets) { for(auto s:sub) { cout<<s<<" ";} cout<<endl; } 
	
	//string s = "THIS IS A TEST TEXT$"; 
	//SuffixTree sft (s);
	//cout << sft.getNodeCount() << endl;

	//sft.checkIfSubstring(" TEXT$");
	/*sft.checkIfSubstring("A");
	sft.checkIfSubstring(" ");
	sft.checkIfSubstring("IS A");
	sft.checkIfSubstring(" IS A ");
	sft.checkIfSubstring("TEST1");
	sft.checkIfSubstring("THIS IS GOOD");
	sft.checkIfSubstring("TES");
	sft.checkIfSubstring("TESA");
	sft.checkIfSubstring("ISB");*/

	system("pause");
	return 0;
}
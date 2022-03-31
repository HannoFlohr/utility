#include<bits/stdc++.h>
//#include "SuffixTree.h"
#include "ArrayUtility.h"

using namespace std;



int main() {

	vector<int> a = {1,2,3,4,5};

	makeSubsets(a,3);

	for(auto sub:subsets) { for(auto s:sub) { cout<<s<<" ";} cout<<endl; } 
	
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

	return 0;
}
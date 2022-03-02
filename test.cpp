#include<bits/stdc++.h>
#include "SuffixTree.h"

using namespace std;



int main() {

	
	string s = "THIS IS A TEST TEXT$"; 
	SuffixTree sft (s);
	cout << sft.getNodeCount() << endl;

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
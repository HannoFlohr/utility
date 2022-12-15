
#include "VectorUtility.h"
#include "PrimeGenerator.h"
#include "StringUtility.h"
#include "Trie.h"
#include<iostream>

using namespace std;



int main() {
	TrieNode* root = new TrieNode();
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
	cout << root->search("helloworld") << endl;


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
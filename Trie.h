#pragma once
#include<map>
#include<string>
#include<vector>

class TrieNode {
private:
	bool is_leaf;
	std::map<char,TrieNode*> children;

	bool hasChildren(TrieNode*& node) {
		for (auto& child : children)
			if (child.second != nullptr)
				return true;
	}

	bool deleteNode(TrieNode*& node, bool leaf) {
		//if the node doesn't have children, delete it
		if (!hasChildren(node)) {
			delete node;
			node = nullptr;
			return true;
		}
		else { //if it has, just set the leaf status to false
			if(leaf)
				node->is_leaf = false;
			return false;
		}
	}

public:
	TrieNode() {
		this->is_leaf = false;
	}

	void insert(const std::string& key) {
		//start from root node of trie
		TrieNode *current_node = this, *child_node; 

		for (int i = 0; i < key.length(); i++) {
			child_node = current_node->children[key[i]];
			//create a new node if the path to key[i] doesn't exist
			if (child_node == nullptr) {
				child_node = new TrieNode();
				current_node->children[key[i]] = child_node; 
			}
			//go to next node for the next char
			current_node = child_node;
		}

		//mark last node of key as leaf
		current_node->is_leaf = true;
	}

	bool search(const std::string& key) {
		if (this == nullptr) return false;

		//start from root node of trie;
		TrieNode* current_node = this;

		for (int i = 0; i < key.length(); i++) {
			//go to next node of the trie according to key[i]
			current_node = current_node->children[key[i]];
			//if that node doesn't exist the searched key value is not in the trie
			if (current_node == nullptr)
				return false;
		}

		//end of key reached, check if it also is a leaf of the trie
		return current_node->is_leaf;
	}

	bool remove(TrieNode*& node, const std::string& key) {
		if (node == nullptr) return false;
		
		//end of key reached
		if (key.length() == 0 && node->is_leaf)
			return deleteNode(node, true);

		//end of key not reached
		if (key.length()) 
			//recursively go through the next node of the key - if true is returned delete the node if it is not a leaf
			if (node->children[key[0]] != nullptr && remove(node->children[key[0]], key.substr(1)) && node->is_leaf == false) 
				deleteNode(node, false);

		return false;
	}
};
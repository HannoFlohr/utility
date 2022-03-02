#include<iostream>
#include<string>

#define MAX_CHAR 256

struct SuffixTreeNode {
	struct SuffixTreeNode *children[MAX_CHAR];
	
	//pointer to other node via suffix link
	struct SuffixTreeNode *suffixLink;
	
	// (start,end) specifies the edge, by which the node is connected to its parents node
	int start;
	int *end;
	
	//leaf nodes; stores suffix index for path from root to leaf
	int suffixIndex;
};
typedef struct SuffixTreeNode Node;

class SuffixTree {
public:	
	//build the suffix tree
	SuffixTree(std::string input) {
		s = input;
		size = input.length();
		
		rootEnd = (int*) malloc(sizeof(int));
		*rootEnd = -1;
		
		root = newNode(-1, rootEnd);
		
		activeNode = root;
		for(int i=0; i<size; i++)
			extendSuffixTree(i);
		
		int height = 0;
		setSuffixIndexByDFS(root, height);
	}
	
	//destructor
	~SuffixTree() {
		//freeSuffixTreeByPostOrder(root);
	}

private:
	//input string 
	std::string s; 
	//pointer to root node
	Node *root = NULL;
	//pointer created to newly created internal node
	Node *lastNewNode = NULL;
	//pointer to current active node
	Node *activeNode = NULL;
	
	int nodeCount = 0;
	
	//active edge represented by string character index
	int activeEdge = -1;
	int activeLength = 0;
	
	int remainingSuffixCount = 0;
	int leafEnd = -1;
	int *rootEnd = NULL;
	int *splitEnd = NULL;
	int size = -1;
	
	Node* newNode(int start, int *end) {
		nodeCount++;
		Node* node = (Node*) malloc(sizeof(Node));
		for(int i=0; i<MAX_CHAR; i++)
			node->children[i] = NULL;
		
		node->suffixLink = root;
		node->start = start;
		node->end = end;
		node->suffixIndex = -1;
		return node;
	}
	
	int edgeLength(Node* n) {
		return *(n->end) - (n->start) + 1;
	}
	
	int walkDown(Node* curNode) {
		if(activeLength >= edgeLength(curNode)) {
			activeEdge = (int)s[activeEdge + edgeLength(curNode)] - (int)' ';
			activeLength -= edgeLength(curNode);
			activeNode = curNode;
			return 1;
		}
		return 0;
	}
	
	void extendSuffixTree(int pos) {
		//Extension Rule 1
		leafEnd = pos;
		//increment to indicate new suffix yet to be added to the tree
		remainingSuffixCount++;
		//indicate that there is no internal node waiting for its suffix link reset in current phase
		lastNewNode = NULL;
		
		//add all suffixes into the tree
		while(remainingSuffixCount > 0) {
			if(activeLength == 0)
				activeEdge = (int)s[pos] - (int)' ';
			
			//no outgoing edge starting with activeEdge from activeNode
			if(activeNode->children[activeEdge] == NULL) {
				//Extension Rule 2
				activeNode->children[activeEdge] = newNode(pos, &leafEnd);
				
				/*A new leaf edge was created above; if there is any internal node waiting for its suffix link
				to get reset, point suffixLink form that last internal node to the current activeNode;
				then set lastNewNode to NULL to indicate no more waiting nodes */
				if(lastNewNode != NULL) {
					lastNewNode->suffixLink = activeNode;
					lastNewNode = NULL;
				}
			}
			//outgoing edge exists
			else{
				//get next node 
				Node* next = activeNode->children[activeEdge];
				//walkdown to new activeNode
				if(walkDown(next))
					continue;
				
				//Extension Rule 3
				if(s[next->start + activeLength] == s[pos]) {
					//if newly created node is waiting for its suffix link to be set, set suffix link of that node to current activeNode
					if(lastNewNode != NULL && activeNode != root) {
						lastNewNode->suffixLink = activeNode;
						lastNewNode = NULL;
					}
					
					activeLength++;
					break;
				}
				
				/*At this point activePoint is in the middle of the edge being traversed and the current character being processed is not on the edge.
				Therefore, a new internal node and a new leaf edge are added. (Extension Rule 2)*/
				splitEnd = (int*) malloc(sizeof(int));
				*splitEnd = next->start + activeLength - 1;
				
				//new internal node
				Node *split = newNode(next->start, splitEnd);
				activeNode->children[activeEdge] = split;
				
				//new leaf
				split->children[(int)s[pos]-(int)' '] = newNode(pos, &leafEnd);
				next->start += activeLength;
				split->children[activeEdge] = next;
				
				//check for internal node created in same phase that still needs its suffix link reset and do that 
				if(lastNewNode != NULL)
					lastNewNode->suffixLink = split;
				
				//make new created internal node waiting for suffix link reset
				lastNewNode = split;
			}
			
			//suffix got added to tree, decrement count
			remainingSuffixCount--;
			
			if(activeNode == root && activeLength > 0) {
				activeLength--;
				activeEdge = (int)s[pos - remainingSuffixCount + 1] - (int)' ';
			}
			else if(activeNode != root)
				activeNode = activeNode->suffixLink;
		}
	}
	
	void print(int i, int j) {
		for( ; i<=j; i++)
			std::cout << s[i];
	}
	
	//print suffix tree with suffix index (DFS)
	void setSuffixIndexByDFS(Node* n, int height) {
		if(n==NULL) return;
		
		//non-root node
		if(n->start != -1) print(n->start, *(n->end));
		
		int leaf=1;
		for(int i=0; i<MAX_CHAR; i++)
			if(n->children[i] != NULL) {
				if(leaf==1 && n->start!=-1) 
					std::cout << " [" << n->suffixIndex << "]" << std::endl;

				leaf = 0;
				setSuffixIndexByDFS(n->children[i], height+edgeLength(n->children[i]));
			}
			
		if(leaf==1) {
			n->suffixIndex = size - height;
			std::cout << " [" << n->suffixIndex << "]" << std::endl;
		}
	}
	
	void freeSuffixTreeByPostOrder(Node* n) {
		if(n==NULL) return;
		
		for(int i=0; i<MAX_CHAR; i++)
			if(n->children[i] != NULL)
				freeSuffixTreeByPostOrder(n->children[i]);
		
		if(n->suffixIndex == -1)
			free(n->end);
		free(n);
	}
	
	int traverseEdge(std::string substr, int index, int start, int end) {
		for(int i=start; i<=end && substr[index] != '\0'; i++, index++)
			if(s[i] != substr[index])
				return -1;
		
		if(substr[index] == '\0')
			return 1;
		
		return 0;
	}
	
	int traverse(Node* n, std::string substr, int index) {
		if(n==NULL) return -1;
		
		int res = -1;
		if(n->start != -1) {
			res = traverseEdge(substr, index, n->start, *(n->end));
			if(res!=0)
				return res;
		}
		
		index = index + edgeLength(n);
		
		if(n->children[(int)substr[index]-(int)' '] != NULL)
			return traverse(n->children[(int)substr[index]-(int)' '], substr, index);
		else
			return -1;
	}
	
public:
	bool checkIfSubstring(std::string str) {
		if(traverse(root,str,1) == 1) 
			{std::cout << str << " is a substring" << std::endl; return true;}
		else
			{std::cout << str << " is not a substring" << std::endl; return false; }
	}
	
	int getNodeCount() {return nodeCount; }
};

//https://en.wikipedia.org/wiki/Ukkonen%27s_algorithm
//https://www.geeksforgeeks.org/suffix-tree-application-1-substring-check/?ref=lbp
//TODO: substring not working correctly in all cases


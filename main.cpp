//#include "SuffixTree.h"
//#include "ArrayUtility.h"
#include "PrimeGenerator.h"
#include<iostream>

using namespace std;



int main() {

	//MillerRabinPrimalityTest test; 
	//auto number = 5852260055929319999;
	//cout << number << (test.is_prime(number) == 1 ? " is prime" : " is not prime") << endl;
	
	PrimeGenerator<int> pg;
	vector<int> primes = pg.primesUpTo(100);

	for (auto& p : primes)
		cout << p << " ";
	cout << endl;

	for (int i = 1; i < 100; i++) {
		cout << i << " - ";
		cout << pg.countPrimeFactorsOf(i) << " - ";
		vector<int> pf = pg.getPrimeFactorsOf(i);
		for (auto& f : pf)cout << f << " ";
		cout << endl;
	} */
	//vector<int> a = {1,2,3,4,5};

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
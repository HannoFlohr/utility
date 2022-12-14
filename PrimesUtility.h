#include <iostream>
#include <cstring>

using namespace std;

//computes all primes up to MAXP and stores them
vector<int> primes;
const int MAXP = 100;
void sieveOfEratosthenes() {
    vector<bool> prime(MAXP+1,true);
    for(int p=2; p*p<=MAXP; p++) 
        if(prime[p] == true) 
            for(int i=p*p; i<=MAXP; i+=p) 
                prime[i] = false;

    for(int p=2; p<=MAXP; p++) 
        if(prime[p])
            primes.push_back(p);
}

/* void sieveOfEratosthenes(int n) {
	bool prime[n+1];
	memset(prime, true, sizeof(prime));
	
	for(int p=2; p*p<=n; p++) {
		if(prime[p] == true) {
			for(int i=p*p; i<=n; i+=p) {
				prime[i] = false;
			}
		}
	}

	for(int p=2; p<=n; p++) 
		if(prime[p])
			primes.push_back(p)
} */

//computes euler's totient function from 1..n (O(nloglogn)
vector<int> phi_1_n(int n) {
    vector<int> phi (n+1);
    for(int i=0; i<=n; i++)
        phi[i] = i;
    for(int i=2; i<=n; i++) 
        if(phi[i] == i)
            for(int j=i; j<=n; j+=i)
                phi[j] -= phi[j] / i;
                
    return phi;
}
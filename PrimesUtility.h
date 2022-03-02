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

//returns a vector of bool values for prime numbers in range [left,right] without pre-generating all prime numbers
vector<bool> segmentedSieveNoPreGen(long long int left, long long int right) {
    vector<bool> isPrime (right-left+1, true);
    long long int limit = sqrt(right);
    for(long long int i=2; i<=limit; i++) 
        for(long long int j=max(i*i, (left+i-1)/i*i); j<=right; j+=i)
            isPrime[j-left] = false;
    if(left==1)
        isPrime[0] = false;
    return isPrime;
}

//returns the amount of prime factors of 'n'
int countPrimeFactors(int n) {
	if (isPrime(n)) return 1;
	int primeFactors = 0;
	while (n % 2 == 0) {
		n /= 2;
		primeFactors++;
	}
	for (int i = 3; i <= sqrt(n); i += 2) {
		while (n%i == 0) {
			primeFactors++;
			n /= i;
		}
	}
	if (n > 2)
		primeFactors++;
	return primeFactors;
}



/*-- start -- Miller-Rabin test for high primes -- */
typedef unsigned long long int ull;

//returns (a * b) % mod
ull mulMod(ull a, ull b, ull mod) {
	//using optimzed gcc extension for 128bit integers
	return ((unsigned __int128)a * b) % mod;
}

//returns (base^exp) % mod
ull powMod(ull base, ull exp, ull mod) {
	ull result = 1;
	while (exp > 0) {
		//odd exponent a^b = a*a^(b-1)
		if (exp & 1)
			result = mulMod(result, base, mod);
		//even exponent a^b = (a*a)^(b/2)
		base = mulMod(base, base, mod);
		exp >>= 1;
	}
	return result;
}

//Miller-Rabin test
	bool millerRabin(ull p) {
		//trivial cases
		const unsigned int bitmaskPrimes2to31 = (1 << 2) | (1 << 3) | (1 << 5) | (1 << 7) | (1 << 11) | (1 << 13) | (1 << 17) | (1 << 29) | (1 << 23) | (1 << 29);
		//check if p is one of the small primes
		if (p < 31)
			return (bitmaskPrimes2to31 & (1 << p)) != 0;
		//filter all composite number < 17*19
		if (p % 2 == 0 || p % 3 == 0 || p % 5 == 0 || p % 7 == 0 || p % 11 == 0 || p % 13 == 0 || p % 17 == 0)
			return false;
		//all others < 17*19 are prime
		if (p < 17 * 19)
			return true;

		//bases/"witnesses" to test p against (miller-rabin.appspot.com)
		//first three good up to 2^32
		const unsigned int STOP = 0;
		const unsigned int test1[] = { 377687, STOP };
		const unsigned int test2[] = { 31, 73, STOP };
		const unsigned int test3[] = { 2, 7, 61, STOP };
		const unsigned int test4[] = { 2, 13, 23, 1662803, STOP };
		//good up to 2^64
		const unsigned int test7[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022, STOP };

		const unsigned int* test = test7;
		//use less tests for smaller p
		if (p < 5329) test = test1;
		else if (p < 9080191) test = test2;
		else if (p < 4759123141ULL) test = test3;
		else if (p < 1122004669633ULL) test = test4;

		//find p-1 = d * 2^j
		auto d = p - 1;
		d >>= 1;
		unsigned int shift = 0;
		while ((d & 1) == 0) {
			shift++;
			d >>= 1;
		}

		//test p against the bases
		do {
			auto x = powMod(*test++, d, p);
			if (x == 1 || x == p - 1)
				continue;

			//now prime or strong pseudo-prime
			// test^(d*2^r); 0<=r<shift
			bool maybePrime = false;
			for (unsigned int r = 0; r < shift; r++) {
				// x = x^2 % p
				x = powMod(x, 2, p);
				// x % p == 1 -> not prime
				if (x == 1)
					return false;

				//even larger chance to be prime
				if (x == p - 1) {
					maybePrime = true;
					break;
				}
			}

			if (!maybePrime) //=not prime
				return false;
		} while (*test != STOP);

		return true;
	}
/*-- end -- Miller-Rabin test for high primes -- */
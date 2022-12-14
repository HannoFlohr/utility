#pragma once
#include<vector> 
#include "ModuloForHighIntegers.h"

/*
computes the Miller-Rabin primality, a probabilistic primality test: 
an algorithm which determines whether a given number 'p' is likely to be prime
see https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test for more information
*/

typedef unsigned long long int ull;

class MillerRabinPrimalityTest {
private:
	const std::vector<unsigned int> primesTo29{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
	
	//different bases to test p against and their limits (https://miller-rabin.appspot.com/) 
	const std::vector<std::vector<ull>> bases{	
		{ 377687 },
		{ 2, 299417 },
		{ 2, 7, 61 },
		{ 2, 13, 23, 1662803 },
		{ 2, 75088, 642735, 203659041, 3613982119ull },
		{ 2, 123635709730000, 9233062284813009, 43835965440333360, 761179012939631437, 1263739024124850375 },
		{ 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }
	};
	const std::vector<ull> limits{ 5329, 19471033, 4759123141, 1122004669633, 3071837692357849, 585226005592931977, 18446744073709551615 };  

	int findLimit(const ull& n) {
		for (size_t i=0; i<limits.size(); i++)
			if (n <= limits[i])
				return i;
		return limits.size()-1;
	}

public:
	bool is_prime(ull p) {
		//check if p is one of the first primes
		for (auto& prime : primesTo29)
			if (p == prime)
				return true;
		//check composite numbers < 17*19
		for (size_t i = 0; i < 7; i++)
			if (p % primesTo29[i] == 0)
				return false;
		//other numbers < 17*19 are prime
		if (p < 17 * 19)
			return true;

		//set the correct base for p <= limit
		const std::vector<ull>& tests = bases[findLimit(p)]; 

		//find p-1 = d * 2^j
		unsigned int shift = 0;
		auto d = p - 1;
		d >>= 1;
		while ((d & 1) == 0) {
			shift++;
			d >>= 1;
		}

		//test p against the bases
		bool probably_prime;
		ull x;
		for (auto& test : tests) {
			x = powMod<ull>(test, d, p); 
			if (x == 1 || x == p - 1) continue;

			//now prime or strong pseudo-prime
			//check test^(d*2^r) for 0<=r<shift
			probably_prime = false;
			for (unsigned int r = 0; r < shift; r++) {
				x = powMod<ull>(x, 2, p);
				//x % p == 1 -> not prime
				if (x == 1) return false;

				//larger chance to be prime
				if (x == p - 1) {
					probably_prime = true;
					break;
				}
			}

			//most likely not a prime so return false
			if (!probably_prime) return false;
		}

		return true;
	}
};
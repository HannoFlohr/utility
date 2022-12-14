#pragma once
#include<vector>

template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type> 
class PrimeGenerator {
private:
	T limit;
	std::vector<T> primes;
	std::vector<bool> is_prime;

	void falsifyMultiplesOf(const T& p) {
		for (T i = p * p; i <= limit; i += p)
			is_prime[i] = false;
	}

	void sieveOfEratosthenes() {
		is_prime = std::vector<bool>(limit + 1, true);
		is_prime[0] = false, is_prime[1] = false;

		for (T i = 2; i * i <= limit; i++)
			if (is_prime[i])
				falsifyMultiplesOf(i);
	}

	void fillVectorWithPrimeNumbers() {
		for (int i = 0; i <= limit; i++)
			if (is_prime[i])
				primes.push_back(i);
	}

public:
	PrimeGenerator(const T& n) : limit(n) {
		sieveOfEratosthenes();
		fillVectorWithPrimeNumbers();
	}

	const std::vector<T>& getPrimes() const {
		return primes;
	}

	T countPrimeFactorsOf(T n) {
		if (n > limit) return -1; 
		if (is_prime[n]) return 1;

		T prime_factor_count = 0;
		while (n != 1) 
			for (auto& p : primes) 
				while (n % p == 0) {
					prime_factor_count++;
					n /= p;
				}

		return prime_factor_count;
	}

	std::vector<T> getPrimeFactorsOf(T n) {
		if (n > limit || n < 2) return {}; 
		if (is_prime[n]) return { n };
		 
		vector<T> prime_factors; 
		while(n != 1)
			for(auto &p : primes)
				while (n % p == 0) {
					prime_factors.push_back(p);
					n /= p;
				}

		return prime_factors; 
	}
};
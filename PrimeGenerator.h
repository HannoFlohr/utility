#pragma once
#include<vector>

template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type> 
class PrimeGenerator {
private:
	T limit = 0;
	std::vector<T> primes;
	std::vector<bool> is_prime;

	void falsifyMultiplesOf(const T& p) {
		for (T i = p * p; i <= limit; i += p) {
			is_prime[i] = false;
		}
	}

	void sieveOfEratosthenes() {
		is_prime = std::vector<bool>(limit + 1, true);
		is_prime[0] = false, is_prime[1] = false;

		for (T i = 2; i * i <= limit; i++) {
			if (is_prime[i]) {
				falsifyMultiplesOf(i);
			}
		}
	}

	void fillVectorWithPrimeNumbers() {
		for (int i = 0; i <= limit; i++) {
			if (is_prime[i]) {
				primes.push_back(i);
			}
		}
	}

public:
	const std::vector<T>& primesUpTo(const T& n) {
		primes.clear();
		limit = n;
		sieveOfEratosthenes();
		fillVectorWithPrimeNumbers();
		return primes;
	}

	const std::vector<bool> isPrimeInRange(const T& left, const T& right) {
		std::vector<bool> prime (right - left + 1, true);
		for (long long int i = 2; i <= sqrt(right); i++) {
			for (long long int j = max(i * i, (left + i - 1) / i * i); j <= right; j += i) {
				prime[j - left] = false;
			}
		}

		if (left == 1) {
			prime[0] = false;
		}
		return prime;
	}

	T countPrimeFactorsOf(T n) {
		if (n > limit) {
			primesUpTo(n);
		}
		if (is_prime[n]) {
			return 1;
		}

		T prime_factor_count = 0;
		while (n != 1) {
			for (T p : primes) {
				while (n % p == 0) {
					prime_factor_count++;
					n /= p;
				}
			}
		}

		return prime_factor_count;
	}

	std::vector<T> getPrimeFactorsOf(T n) {
		if (n > limit) {
			primesUpTo(n);
		}
		if (is_prime[n]) {
			return { n };
		}

		vector<T> prime_factors; 
		while (n != 1) {
			for (T p : primes) {
				while (n % p == 0) {
					prime_factors.push_back(p);
					n /= p;
				}
			}
		}

		return prime_factors; 
	}
};
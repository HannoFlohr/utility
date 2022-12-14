#pragma once
#include<type_traits>

//returns (a * b) % mod
template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
T multiplyMod(T a, T b, const T& mod) {
	T result = 0;
	a %= mod;
	
	while (b) {
		if (b & 1)
			result = (result + a) % mod;
		a = (2 * a) % mod;
		b >>= 1;
	}

	return result;
}

//returns (base^exp) % mod
template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
T powMod(T base, T exp, const T& mod) {
	T result = 1;

	while (exp > 0) {
		//odd exponent a^b = a*a^(b-1)
		if (exp & 1)
			result = multiplyMod<T>(result, base, mod); 
		//even exponent a^b = (a*a)^(b/2)
		base = multiplyMod(base, base, mod);
		exp >>= 1;
	}

	return result;
}
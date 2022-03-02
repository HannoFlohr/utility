#ifndef LONGINTEGERMOD_H_
#define LONGINTEGERMOD_H_

typedef unsigned long long int ull;

//returns (a * b) % mod
ull mulMod128(ull a, ull b, ull mod) {
	//using optimzed gcc extension for 128bit integers
	return ((unsigned __int128)a * b) % mod;
}

//calculates (a*b) % mod, taking into account that (a*b) might overflow
ull mulMod(ull a, ull b, ull mod) {
	ull x = 0, y = a % mod;
	while (b > 0) {
		if (b % 2 == 1)
			x = (x + y) % mod;
		y = (y * 2) % mod;
		b /= 2;
	}
	return x % mod;
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

#endif
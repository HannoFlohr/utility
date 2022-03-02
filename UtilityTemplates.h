#ifndef UTILITYTEMPLATES_H_
#define UTILITYTEMPLATES_H_

#include<cstdlib>
#include<ctime>

/*
counts the digits of the given number n and returns a number resembling that count
e.g.    0   -> 1
        2   -> 100
        9   -> 1000000000
        771 -> 20000010
numbers with the same count of digits are permutations of each other
*/
template<typename T>
T countDigits(T n) {
    T digits = 0, digit, position;
    while(n>0) {
        digit = n%10;
        n /= 10;
        
        position = 1;
        for(T i=0; i<digit; i++)
            position *= 10;
            
        digits += position;
    }
    return digits;
}

//returns the greatest common divisor of a and b
template<typename T> 
T gcd(const T& a, const T& b) {
    if(!b) return a;
    return gcd(b, a % b);
}

//returns the least common multiple of a and b
template<typename T> 
T lcm(const T& a, const T& b) {
    return a * b / gcd(a, b);
}

//returns the reduced fration a/b
template<typename T>
void reduceFraction(T &a, T &b) {
	const T div (gcd(a, b));
	a /= div;
	b /= div;
}

template<typename T> void chmin(T& a, T b) { a = (a > b) ? b : a; }
template<typename T> void chmax(T& a, T b) { a = (a < b) ? b : a; } 

//returns a random number in range [low, high]
template<typename T>
T randomNumber(const T& low, const T& high) {
    static bool first = true;
    if(first) {
        srand( time(NULL) ); //seeding for the first cast
        first = false;
    }
    return low + rand() % ((high+1) - low);
}


//russian peasant exponentiation
//http://lafstern.org/matt/col3.pdf
template<typename T, class Integer>
T exponentiate(T x, Integer n) {
	while ((n & 1) == 0) {
		x *= x;
		n >>= 1;
	}
	T p = x;
	n >>= 1;
	while (n > 0) {
		x *= x;
		if ((n & 1) != 0)
			p *= x;
		n >>= 1;
	}
	return p;
}

#endif
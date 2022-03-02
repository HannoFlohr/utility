#ifndef BIGINT_H_
#define BIGINT_H_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

class BigInt {
private: 
	std::vector<int> value;
	bool positive;
	static const int base = 1000000000;
	unsigned int skip;

public: 
	// Constructors
	BigInt();
	BigInt(long long);
	BigInt(std::string);
	BigInt(const BigInt& b);

	// Addition
	BigInt operator+(const BigInt&) const;
	BigInt &operator+=(const BigInt&);
	BigInt operator+(const long long &) const;
	BigInt &operator+=(long long);

	// Subtraction
	BigInt operator-(BigInt const &) const;
	BigInt &operator-=(BigInt const &);

	// Multiplication
	BigInt operator*(const BigInt &);
	BigInt &operator*=(const BigInt &);
	BigInt operator*(const long long &);
	BigInt &operator*=(const int &);

	// Comparison
	int compare(BigInt const &) const; //0 a == b, -1 a < b, 1 a > b
	bool operator==(const BigInt &) const;
	bool operator<(const BigInt &) const;
	bool operator>(const BigInt &) const;

	// Power
	BigInt &pow(int const &);
	BigInt pow(int const &, std::map<int, BigInt> &);

	// I/O
	friend std::ostream &operator<<(std::ostream &out, const BigInt &b);

	// helper 
	int segment_length(int segment) const {
		int length = 0;
		while (segment) {
			segment /= 10;
			length++;
		}
		return length;
	}

	std::string toString();

	int digits();
};

// Constructors
BigInt::BigInt() {
	positive = true;
	skip = 0;
}

BigInt::BigInt(long long v) {
	skip = 0;
	if (v >= 0)
		positive = true;
	else {
		positive = false;
		v *= -1;
	}

	while (v) {
		value.push_back((int)(v % base));
		v /= base;
	}
}

BigInt::BigInt(std::string s) {
	positive = s[0] != '-';
	skip = 0;
	int length, number, prefix, size = s.length();

	while ((positive && size > 0) || (!positive && size > 1)) {
		length = 0;
		number = 0;
		prefix = 1;
		for (int i = size - 1; i >= 0 && i >= size - 9; --i) {
			if (s[i] < '0' || s[i] > '9') break;
			number += (s[i] - '0') * prefix;
			prefix *= 10;
			length++;
		}
		value.push_back(number);
		size -= length;
	}
}

BigInt::BigInt(const BigInt& b) : value(b.value), positive(b.positive), skip(b.skip) {}

// Addition
BigInt BigInt::operator+(const BigInt &b) const {
	BigInt c = *this;
	c += b;
	return c;
}

BigInt &BigInt::operator+=(const BigInt &b) {
	if (!b.positive)
		return *this -= b;

	std::vector<int>::iterator it1 = value.begin();
	std::vector<int>::const_iterator it2 = b.value.begin();
	int sum = 0;
	while (it1 != value.end() || it2 != b.value.end()) {
		if (it1 != value.end())
			sum += *it1;
		else {
			value.push_back(0);
			it1 = value.end() - 1;
		}
		if (it2 != b.value.end()) {
			sum += *it2;
			it2++;
		}
		*it1 = sum % base;
		it1++;
		sum /= base;
	}
	if (sum) value.push_back(1);

	return *this;
}

BigInt BigInt::operator+(const long long &b) const {
	BigInt c = *this;
	c += b;
	return c;
}

BigInt &BigInt::operator+=(long long b) {
	std::vector<int>::iterator it = value.begin();
	if (skip > value.size())
		value.insert(value.end(), skip - value.size(), 0);

	it += skip;
	bool initial_flag = true;
	while (b || initial_flag) {
		initial_flag = false;
		if (it != value.end()) {
			*it += b % base;
			b /= base;
			b += *it / base;
			*it %= base;
			it++;
		}
		else {
			value.push_back(0);
			it = value.end() - 1;
		}
	}
	return *this;
}

// Subtraction
BigInt BigInt::operator-(const BigInt &b) const {
	BigInt c = *this;
	c -= b;
	return c;
}

BigInt &BigInt::operator-=(const BigInt &b) {
	std::vector<int>::iterator it1 = value.begin();
	std::vector<int>::const_iterator it2 = b.value.begin();
	int dif = 0;
	while (it1 != value.end() || it2 != b.value.end()) {
		if (it1 != value.end()) {
			dif += *it1;
			it1++;
		}
		if (it2 != b.value.end()) {
			dif -= *it2;
			it2++;
		}
		if (dif < 0) {
			*(it1 - 1) = dif + base;
			dif = -1;
		}
		else {
			*(it1 - 1) = dif % base;
			dif /= base;
		}
	}

	if (dif < 0)
		positive = false;

	if (value.size() > 1) {
		do {
			it1 = value.end() - 1;
			if (*it1 == 0)
				value.pop_back();
			else
				break;
		} while (value.size() > 1);
	}

	return *this;
}

// Multiplication
BigInt BigInt::operator*(const BigInt &b) {
	if (b.value.size() == 1)
		return *this *= b.value[0];
	
	BigInt c;
	std::vector<int>::iterator it1;
	std::vector<int>::const_iterator it2;
	for (it1 = value.begin(); it1 != value.end(); ++it1) {
		for (it2 = b.value.begin(); it2 != b.value.end(); ++it2) {
			c.skip = (unsigned int)(it1 - value.begin()) + (it2 - b.value.begin()); 
			c += (long long)(*it1)*(*it2);
		}
	}
	c.skip = 0;

	return c;
}

BigInt &BigInt::operator*=(const BigInt &b) {
	*this = *this * b;
	return *this;
}

BigInt BigInt::operator*(const long long &b) {
	BigInt c = *this;
	c *= b;
	return c;
}

BigInt &BigInt::operator*=(const int &b) {
	std::vector<int>::iterator it = value.begin();
	long long sum = 0;
	while (it != value.end()) {
		sum += (long long)(*it) * b; 
		*it = (int)(sum % base);
		sum /= base;
		it++;
	}
	if (sum) value.push_back((int)sum); 

	return *this;
}

// Comparison
int BigInt::compare(BigInt const &b) const { //0 a == b, -1 a < b, 1 a > b
	if (positive && !b.positive) return 1;
	if (!positive && b.positive) return -1;

	int check = 1;
	if (!positive && !b.positive) check = -1;

	if (value.size() < b.value.size()) return -1 * check;
	if (value.size() > b.value.size()) return check;
	for (size_t i = value.size(); i > 0; --i) {
		if (value[i - 1] < b.value[i - 1]) return -1 * check;
		if (value[i - 1] > b.value[i - 1]) return check;
	}
	return 0;
}

bool BigInt::operator==(const BigInt &b) const {
	return compare(b) == 0;
}

bool BigInt::operator<(const BigInt &b) const {
	return compare(b) == -1;
}

bool BigInt::operator>(const BigInt &b) const{
	return compare(b) == 1;
}

// I/O
std::ostream &operator<<(std::ostream &out, const BigInt &b) {
	if (!b.value.size())
		return out << 0;
	int i = b.value.size() - 1;
	for (; i >= 0 && b.value[i] == 0; --i);

	if (i == -1)
		return out << 0;
	if (!b.positive)
		out << '-';

	std::vector<int>::const_reverse_iterator it = b.value.rbegin() + (b.value.size() - i - 1);
	out << *it++;
	for (; it != b.value.rend(); ++it) {
		for (int i = 0, length = b.segment_length(*it); i < 9 - length; ++i)
			out << '0';
		if (*it)
			out << *it;
	}
	return out;
}

BigInt BigInt::pow(int const &power, std::map<int, BigInt> &lookup)
{
	if (power == 1) return *this;
	if (lookup.count(power)) return lookup[power];

	int closestPower = 1;
	while (closestPower < power) closestPower <<= 1;
	closestPower >>= 1;

	if (power == closestPower) lookup[power] = pow(power / 2, lookup) * pow(power / 2, lookup);
	else lookup[power] = pow(closestPower, lookup) * pow(power - closestPower, lookup);

	return lookup[power];
}

BigInt &BigInt::pow(int const &power)
{
	std::map<int, BigInt> lookup;
	if (power % 2 == 0 && !positive) {
		positive = true;
	}
	*this = pow(power, lookup);

	return *this;
}

std::string BigInt::toString() {
	std::ostringstream stream;
	stream << *this;
	return stream.str();
}

int BigInt::digits() {
	int segments = value.size();
	if (segments == 0)
		return 0;
	int digits = 9 * (segments - 1);
	digits += segment_length(value.back());
	return digits;
}

BigInt factorial(int n) {
	BigInt fac = 1;
	if (n % 2) {
		fac = n;
		n--;
	}
	int last = 0;
	for (; n >= 2; n -= 2) {
		fac *= n + last;
		last += n;
	}
	return fac;
}

#endif
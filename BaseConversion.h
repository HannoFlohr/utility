#ifndef BASECONVERSION_H_
#define BASECONVERSION_H_

#include <iostream>
#include <string>

//returns the ascii value of char 'c'
int value(const char &c) {
	if (c >= '0' && c <= '9')
		return (int)c - '0';
	return (int)c - 'A' + 10;
}

//converts the input number from given base 'b' to a decimal number
int toDecimal(std::string number, const int &base) {
	int result = 0, power = 1;
	for (int i = number.length() - 1; i >= 0; i--) {
		if (value(number[i]) >= base) {
			std::cout << "Invalid number for base " << base << ": " << value(number[i]) << std::endl;
			return -1;
		}
		result += value(number[i]) * power;
		power *= base;
	}
	return result;
}

//returns the char for a value 'v'
char reValue(const int &v) {
	if (v >= 0 && v <= 9)
		return (char)(v + '0');
	return (char)(v - 10 + 'A');
}

//converts the decimal 'number' to its representation in base 'b' 
std::string fromDecimal(int number, const int &base) {
	string result = "";
	int index = 0;
	while (number > 0) {
		result += reValue(number % base); 
		number /= base;
	}
	std::reverse(result.begin(), result.end());
	return result;
}

#endif 
#ifndef ROMANINTEGERCONVERSION_H_
#define ROMANINTEGERCONVERSION_H_

#include<unordered_map>
#include<string>
#include<vector>

//Roman Number to Integer
std::unordered_map<char,unsigned> romanToValues { {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000} };

unsigned romanToInt(std::string s) {
    unsigned number = 0;
    for(unsigned i=0; i<s.size(); i++) {
        if(i<s.size()-1 && romanToValues[ s[i+1] ] > romanToValues[ s[i] ] ) {
            number += romanToValues[ s[i+1] ] - romanToValues[ s[i] ];
            i++;
        }
        else
            number += romanToValues[ s[i] ];
    }
    
    return number;
}

//Integer to Roman Number
const std::vector<unsigned> values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
const std::vector<std::string> symbols =  {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

std::string intToRoman(unsigned num) {
    std::string roman = "";
    unsigned i=0;
        
    while(num>0 && i<values.size()) {
        while(values[i] <= num) {
            roman += symbols[i];
            num -= values[i];
        }
        i++;
    }
        
    return roman;
}

#endif
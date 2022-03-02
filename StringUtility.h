#ifndef STRINGUTILITY.H
#define STRINGUTILITY.H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>



//-- find longest palindrome in a string
std::string addSeparator(const std::string& s, std::string sep="|") {
    if(!s.size()) return "";
    
    std::stringstream ss;
    for(unsigned i=0; i<s.size(); i++)
        ss << sep << s[i];
    ss << sep;
    return ss.str();
}
//https://en.wikipedia.org/wiki/Longest_palindromic_substring - Manacher's algorithm
unsigned longest_palindrome(const std::string& input) {
    const int size_input = input.size();
    const int size_s = 2*size_input+1;
    std::string s = addSeparator(input);
    std::vector<int> palindrome_radii (size_s, 0);
    
    int center=0, radius=0, old_center, old_radius, mirrored_center, max_mirrored_radius;
    while(center < size_s) {
        while(center-(radius+1) >= 0 && center+(radius+1) < size_s && s[center-(radius+1)] == s[center+(radius+1)])
            radius++;
        
        palindrome_radii[center] = radius;
        
        old_center = center;
        old_radius = radius;
        center++;
        radius = 0; 
        
        while(center <= old_center + old_radius) {
            mirrored_center = old_center - (center - old_center);
            max_mirrored_radius = old_center + old_radius - center;
            if(palindrome_radii[mirrored_center] < max_mirrored_radius) {
                palindrome_radii[center] = palindrome_radii[mirrored_center];
                center++;
            }
            else if(palindrome_radii[mirrored_center] > max_mirrored_radius) {
                palindrome_radii[center] = max_mirrored_radius;
                center++;
            }
            else {
                radius = max_mirrored_radius;
                break;
            }
        }
    }
    
    unsigned longest_palindrome_s = 2 * (*max_element(palindrome_radii.begin(),palindrome_radii.end())) + 1;
    return (longest_palindrome_s - 1) / 2;  
}
//-- find longest palindrome in a string -- end

//check if a given string s can be an anadrome
bool canBeAnadrome(const std::string& s) {
	std::map<char, unsigned> occurrences;
	for(unsigned i=0; i<s.size(); i++) 
		occurrences[s[i]]+=1;
				
	unsigned odd = 0;
	for(auto iter = occurrences.begin(); iter!=occurrences.end(); iter++) 
		if(iter->second %2 == 1) 
			odd++;
	
	return odd<=1 ? true : false;
}

#endif
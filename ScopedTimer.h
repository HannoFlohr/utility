#pragma once
#include<chrono>
#include<iostream>

class ScopedTimer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
public: 
	ScopedTimer() {
		start = std::chrono::high_resolution_clock::now(); 
		std::cout << "timer started.." << std::endl;
	}
	~ScopedTimer() {
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "timer ended after " << std::chrono::duration<double>(end - start).count() << std::endl; 
	}
};
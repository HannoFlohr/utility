#pragma once
#include<iostream>
#include<vector> 
#include<map>
#include<unordered_map> 
#include<stack> 
#include<array>
#include<queue> 

//adds a pair<T1,T2> to the stream as (T1,T2)
template<typename T1, typename T2> 
std::ostream& operator<<(std::ostream& stream, const std::pair<T1,T2>& p) {
	stream << "(" << p.first << "," << p.second << ")";
	return stream;
}

//adds the contents of a vector<T> to the stream
template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& v) {
	for (const auto& i : v)
		stream << i << " ";
	return stream; 
}

//adds the contents of a vector<vector<T>> to the stream
template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<std::vector<T>>& v) { 
	for (const auto& row : v) {
		for(const auto& column : row) 
			stream << column << " ";
		stream << std::endl;
	}
	return stream;
}

//adds the contents of a array<T> to the stream
template<typename T, std::size_t N> 
std::ostream& operator<<(std::ostream& stream, const std::array<T,N>& a) {  
	for (const auto& i : a) 
		stream << i << " ";
	return stream;
}

//adds the contents of a list<T> to the stream
template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::list<T>& l) { 
	for (const auto& i : l)
		stream << i << " ";
	return stream;
}

//adds the contents of an map<T1,T2> to the stream as [key] = value
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& stream, const std::map<T1, T2>& m) {
	for (const auto& [key, value] : m)
		stream << "[" << key << "] = " << value << std::endl;
	return stream;
}

//adds the contents of an unordered_map<T1,T2> to the stream as [key] = value
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& stream, const std::unordered_map<T1, T2>& m) {
	for (const auto& [key, value] : m)
		stream << "[" << key << "] = " << value << std::endl; 
	return stream;
}

//adds the contents of a stack<T> to the stream
template<typename T>
std::ostream& operator<<(std::ostream& stream, std::stack<T> s) {
	while (!s.empty()) {
		stream << s.top() << " ";
		s.pop(); 
	}
	return stream;
}

//adds the contents of a queue<T> to the stream
template<typename T>
std::ostream& operator<<(std::ostream& stream, std::queue<T> q) {
	while (!q.empty()) {
		stream << q.front() << " ";
		q.pop();
	}
	return stream;
}

//adds the contents of a deque<T> to the stream
template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::deque<T>& q) {
	for(const auto& i : q)  
		stream << i << " ";
	return stream;
}

//adds the contents of a priority_queue<T> to the stream
template<typename T>
std::ostream& operator<<(std::ostream& stream, std::priority_queue<T> q) {
	while (!q.empty()) {
		stream << q.front() << " ";
		q.pop();
	}
	return stream;
}
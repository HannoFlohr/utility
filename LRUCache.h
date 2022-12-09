#pragma once
#include<list>
#include<unordered_map>
#include<assert.h>

template <class KEY_T, class VALUE_T> 
class LRUCache {
private:
	std::list< std::pair<KEY_T, VALUE_T> > items;
	std::unordered_map<KEY_T, decltype(items.begin())> key_to_list;
	std::size_t cache_size;

	void cleanup() {
		while(items.size() > cache_size) {
			auto last = items.end();
			last--;
			key_to_list.erase(last->first);
			items.pop_back();
		}
	}

public:
	LRUCache(std::size_t cache_size) : cache_size(cache_size) {}
	
	void put(const KEY_T& key, const VALUE_T& value) {
			auto it = key_to_list.find(key);
			if(it != key_to_list.end()) {
				items.erase(it->second);
				key_to_list.erase(it);
			}
			
			items.push_front( std::make_pair(key,value) );
			key_to_list.insert( std::make_pair(key, items.begin()) );
		
			cleanup();
	}
	
	int get(const KEY_T& key) {
		assert(key_to_list.count(key) > 0);
		
		auto it = key_to_list.find(key);
		items.splice(items.begin(), items, it->second);
		return it->second->second;
	}
};
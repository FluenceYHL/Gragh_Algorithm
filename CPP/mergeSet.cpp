/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:     resouce_allocate_gragh.cpp
  *Author:       刘畅
  *Version:      1.0
  *Date:         2018.12.6
  *Description:  资源分配图算法模拟
  *Compile:      g++ -std=c++14 resouce_allocate_gragh.cpp -o gragh -lpthread
  *Function List:  
  *History:  
**********************************************************************************/
#include "gnuplot.hpp"
#include <unordered_map>

namespace {
	template<typename T>
	void print(const std::vector<T>& arr) {
		for(const auto& it : arr)
			std::cout << it << "  ";
		std::cout << "\n";
	}
	void logCall(const char* message) {
		std::cout << message << "\n";
	}
}


class mergeSet {
private:
	int len;
	std::vector<int> father;
	std::vector<int> rank;
	mergeSet(const mergeSet&) = delete;
	mergeSet(mergeSet&&) = delete;

	int find(const int u) {
		return u == this->father[u] ? u : father[u] = this->find(father[u]);
	}
public:
	mergeSet(const int _len) 
		: len(_len), father(len, 0), rank(len, 1) {
		for(int i = 0;i < len; ++i)
			this->father[i] = i;
	}
	void merge(const int l, const int r) {
		auto x = this->find(l);
		auto y = this->find(r);
		if(x == y)
			return;
		if(this->rank[x] < this->rank[y])
			std::swap(x, y);
		this->rank[x] += this->rank[y];
		this->father[y] = x;
	}
	std::unordered_map<int,  std::vector<int> > getCluster() {
		std::unordered_map<int, std::vector<int> > res;
		for(int i = 0;i < this->len; ++i) {
			auto root = this->find(i);
			this->father[i] = root;
			res[root].emplace_back(i);
		}
		return res;
	}
};

int main() {
	mergeSet one(10);
	one.merge(0, 1);
	one.merge(2, 3);
	one.merge(4, 4);
	one.merge(0, 7);
	auto res = one.getCluster();
	for(const auto& it : res) {
		print(it.second);
	}
	return 0;
}

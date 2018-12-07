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
	bool merge(const int l, const int r) {
		auto x = this->find(l);
		auto y = this->find(r);
		if(x == y)
			return true;
		if(this->rank[x] < this->rank[y])
			std::swap(x, y);
		this->rank[x] += this->rank[y];
		this->father[y] = x;
		return false;
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
	freopen("./gragh(2).txt", "r", stdin);
	mergeSet one(10);
	int len, l , r, i;
	std::cin >> len;
	for(i = 0;i < len; ++i) {
		std::cin >> l >> r;
		if(l == r)
			continue;
		if(one.merge(l, r))
			break;
	}
	printf(i == len ? "不存在环\n" : "检测到环\n");
	return 0;
}

/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:     topo_sort.cpp
  *Author:       刘畅
  *Version:      1.0
  *Date:         2018.12.6
  *Description:  资源分配图算法模拟
  *Compile:      g++ -std=c++14 topo_sort.cpp -o gragh -lpthread
  *Function List:  
  *History:  
**********************************************************************************/
#include "gnuplot.hpp"
#include <unordered_map>
#include <queue>
#include <assert.h>

namespace {
	template<typename T>
	void print(const T& arr) {
		for(const auto& it : arr)
			std::cout << it << "  ";
		std::cout << "\n";
	}
	void logCall(const char* message) {
		std::cout << message << "\n";
	}
}

class mapGragh {
private:
	int len;
	std::vector< std::vector<int> > maps;
	std::vector<int> indegree;
	std::vector<bool> exist;
	std::vector<int> color;
	std::vector<int> sequence;
	mapGragh(const mapGragh&) = delete;
	mapGragh(mapGragh&&) = delete;

	void dfs(const int u) {
		this->color[u] = 1;
		for(int i = 0;i < this->len; ++i) {
			if(this->maps[u][i] and this->color[i] == 0) 
				dfs(i);
			else if(this->maps[u][i] and this->color[i] == 1)
				logCall("检测到环");
		}
		this->color[u] = 2;
		this->sequence.emplace(this->sequence.begin(), u);
	}

public:
	mapGragh(const int _len) 
		: len(_len) {
		this->indegree.assign(this->len, 0);
		this->color.assign(this->len, 0);
		this->exist.assign(this->len, false);
		this->maps.assign(this->len, std::vector<int>(this->len, 0));
	}

	void addEdge(const int l, const int r, const int value = 1) {
		assert(0 <= l and l < len and 0 <= r and r < len);
		this->maps[l][r] = value;
		++this->indegree[r];
		this->exist[l] = this->exist[r] = true;
	}

	void search() {
		this->sequence.clear();
		for(int i = 0;i < this->len; ++i) 
			if(this->exist[i] and color[i] == 0)
				this->dfs(i);
		print(this->sequence);
	}

	void topo_sort() {
		std::queue<int> Q;
		int cnt = 0;
		for(int i = 0;i < this->len; ++i)
			if(indegree[i] == 0)
				Q.push(i), ++cnt;
		while(!Q.empty()) {
			auto u = Q.front();
			Q.pop();
			for(int i = 0;i < this->len; ++i) 
				if(this->maps[u][i] and --this->indegree[i] == 0)
					Q.push(i), ++cnt;
		}
		printf(cnt == this->len ? "不存在环\n" : "检测到环\n");
	}
};

int main() {
	mapGragh one(10);
	freopen("./gragh(2).txt", "r", stdin);
	int len, l , r;
	std::cin >> len;
	for(int i = 0;i < len; ++i) {
		std::cin >> l >> r;
		one.addEdge(l, r);
	}
	one.search();
	return 0;
}
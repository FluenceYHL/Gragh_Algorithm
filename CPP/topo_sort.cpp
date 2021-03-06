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

class topoSort {
private:
	int len;
	std::vector< std::vector<int> > maps;
	std::vector<int> indegree;
	topoSort(const topoSort&) = delete;
	topoSort(topoSort&&) = delete;

public:
	topoSort(const int _len) 
		: len(_len) {
		this->indegree.assign(this->len, 0);
		this->maps.assign(this->len, std::vector<int>());
	}

	void addEdge(const int l, const int r) {
		assert(0 <= l and l < len and 0 <= r and r < len);
		this->maps[l].emplace_back(r);
		++this->indegree[r];
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
			for(const auto v : this->maps[u]) 
				if(--this->indegree[v] == 0)
					Q.push(v), ++cnt;
		}
		printf(cnt == this->len ? "不存在环\n" : "检测到环\n");
	}
};

class dfs_circle {
private:
	int len;
	std::vector< std::vector<int> > maps;
	std::vector<bool> exist;
	std::vector<int> color;
	std::vector<int> sequence;
	dfs_circle(const dfs_circle&) = delete;
	dfs_circle(dfs_circle&&) = delete;

	/*
		1. 如果一个点 color = 2, 说明这个点的后续点都搜索完了, 后面的点没机会在这个点产生回路
		2. 如果后面的节点，发现一个节点 color = 1, 不是 2, 说明这个点搜索过
		3. 重要的是，这个点（以及后续节点）还没搜索完....... 回路
	*/
	void dfs(const int u) {
		this->color[u] = 1;
		for(const auto v : this->maps[u]) {
			if(this->color[v] == 0)
				dfs(v);
			else if(this->color[v] == 1)
				logCall("检测到环");
		}
		this->color[u] = 2;
		this->sequence.emplace(this->sequence.begin(), u);
	}

public:
	dfs_circle(const int _len) 
		: len(_len) {
		this->color.assign(this->len, 0);
		this->exist.assign(this->len, false);
		this->maps.assign(this->len, std::vector<int>());
	}

	void addEdge(const int l, const int r) {
		assert(0 <= l and l < len and 0 <= r and r < len);
		this->maps[l].emplace_back(r);
		this->exist[l] = this->exist[r] = true;
	}

	void search() {
		this->sequence.clear();
		for(int i = 0;i < this->len; ++i) 
			if(this->exist[i] and color[i] == 0)
				this->dfs(i);
		print(this->sequence);
	}
};

int main() {
	// topoSort one(10);
	// freopen("./gragh(2).txt", "r", stdin);
	// int len, l , r;
	// std::cin >> len;
	// for(int i = 0;i < len; ++i) {
	// 	std::cin >> l >> r;
	// 	one.addEdge(l, r);
	// }
	// one.topo_sort();

	topoSort one(10);
	freopen("./gragh(2).txt", "r", stdin);
	int len, l , r;
	std::cin >> len;
	for(int i = 0;i < len; ++i) {
		std::cin >> l >> r;
		one.addEdge(l, r);
	}
	one.topo_sort();
	return 0;
}
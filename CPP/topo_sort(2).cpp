/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:     search.cpp
  *Author:       刘畅
  *Version:      1.0
  *Date:         2018.12.6
  *Description:  资源分配图算法模拟
  *Compile:      g++ -std=c++14 search.cpp -o gragh -lpthread
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

struct yhl_graph {
	struct Edge {
		int to, next, value;
		Edge(const int _to, const int _next, const int _value = 1) 
			: to(_to), next(_next), value(_value)
		{}
	};
	int edge_cnt = -1;
	std::vector< Edge> edges;
	std::vector<int> head;
	yhl_graph(const int len) : head(len, -1) {}

	void addEdge(const int l, const int r) {
		this->edges.emplace_back(r, this->head[l]);
		this->head[l] = ++this->edge_cnt;
	}
};

class topoSort {
private:
	int len;
	yhl_graph graph;
	std::vector<int> indegree;
	topoSort(const topoSort&) = delete;
	topoSort(topoSort&&) = delete;

public:
	topoSort(const int _len) 
		: len(_len), graph(_len) {
		this->indegree.assign(this->len, 0);
	}

	void addEdge(const int l, const int r, const int value = 1) {
		assert(0 <= l and l < len and 0 <= r and r < len);
		++this->indegree[r];
		this->graph.addEdge(l, r);
	}

	void search() {
		std::queue<int> Q;
		int cnt = 0;
		for(int i = 0;i < this->len; ++i)
			if(indegree[i] == 0)
				Q.push(i), ++cnt;
		while(!Q.empty()) {
			auto u = Q.front();
			Q.pop();
			for(int k = this->graph.head[u];k not_eq -1;k = this->graph.edges[k].next) {
				auto v = this->graph.edges[k].to;
				if(--this->indegree[v] == 0)
					Q.push(v), ++cnt;
			}
		}
		printf(cnt == this->len ? "不存在环\n" : "检测到环\n");
	}
};

class dfs_circle {
private:
	int len;
	yhl_graph graph;
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
		for(int k = this->graph.head[u];k not_eq -1;k = this->graph.edges[k].next) {
			auto v = this->graph.edges[k].to;
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
		: len(_len), graph(_len) {
		this->color.assign(this->len, 0);
		this->exist.assign(this->len, false);
	}

	void addEdge(const int l, const int r, const int value = 1) {
		assert(0 <= l and l < len and 0 <= r and r < len);
		this->exist[l] = this->exist[r] = true;
		this->graph.addEdge(l, r);
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
	dfs_circle one(10);
	freopen("./gragh(1).txt", "r", stdin);
	int len, l , r;
	std::cin >> len;
	for(int i = 0;i < len; ++i) {
		std::cin >> l >> r;
		one.addEdge(l, r);
	}
	one.search();
	return 0;
}
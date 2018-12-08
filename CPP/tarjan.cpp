/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:     tarjan.cpp
  *Author:       刘畅
  *Version:      1.0
  *Date:         2018.12.6
  *Description:  tarjan 求强联通分量
  *Compile:      g++ -std=c++14 tarjan.cpp -o gragh -lpthread
  *Function List:  
  *History:  
  *Preference:   
**********************************************************************************/

#include "gnuplot.hpp"
#include <queue>
#include <assert.h>

class Tarjan {
private:
	int len;
	int cnt;
	int time = 0;
	std::vector< std::vector<int> > maps;
	std::vector<int> dfn;
	std::vector<int> low;
	std::vector<int> color;
	std::vector<int> sequence;
	std::vector<int> exist;

	std::unordered_map<int, std::vector<int> > clusters;

	void clear() {
		time = cnt = 0;
		for(int i = 0;i < len; ++i) 
			this->dfn[i] = this->low[i] = this->color[i] = 0;
		this->sequence.clear();
		this->clusters.clear();
	}

	void tarjan(const int u) {
		dfn[u] = low[u] = ++time;
		sequence.emplace_back(u);
		for(const auto v : maps[u]) {
			if(dfn[v] == 0) {
				tarjan(v);
				low[u] = std::min(low[u], low[v]);
			}
			else if(color[v] == 0)
				low[u] = std::min(low[u], dfn[v]);
		}
		if(dfn[u] == low[u]) {
			++cnt;
			std::cout << "NO." << cnt << " { ";
			while(1) {
				auto top = sequence.back();
				sequence.pop_back();
				color[top] = cnt;
				this->clusters[u].emplace_back(top);
				std::cout << top << "  ";
				if(top == u)
					break;
			}
			std::cout << " }\n";
		}
	}
public:
	Tarjan(const int _len) 
		: len(_len), dfn(_len, 0), low(_len, 0), color(_len, 0), exist(_len, 0),
		  maps(_len, std::vector<int>()) // 千万不可以用 len
	{}

	std::unordered_map<int, std::vector<int> > search() {
		this->clear();
		for(int i = 0;i < len; ++i) 
			if(exist[i] and dfn[i] == 0)
				tarjan(i);
		return this->clusters;
	}

	void addEdge(const int l, const int r) {
		assert(0 <= l and l < len and 0 <= r and r < len);
		maps[l].emplace_back(r);
		exist[l] = exist[r] = 1;
	}
};

int main() {
	Tarjan one(10);
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
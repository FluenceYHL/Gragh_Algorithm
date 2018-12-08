/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:     kosaraju.cpp
  *Author:       刘畅
  *Version:      1.0
  *Date:         2018.12.6
  *Description:  Kosaraju 求强联通分量
  *Compile:      g++ -std=c++14 kosaraju.cpp -o gragh -lpthread
  *Function List:  
  *History:  
  *Preference:   https://www.cnblogs.com/nullzx/p/6437926.html
**********************************************************************************/
#include "gnuplot.hpp"
#include <queue>
#include <assert.h>

// 算法很巧妙, 见博客 https://www.cnblogs.com/nullzx/p/6437926.html
class Kosaraju {
private:
	int len;
	int cnt;
	std::vector<int> visited;
	std::vector<int> color;
	std::vector<int> exist;
	std::vector< std::vector<int> > maps;
	std::vector< std::vector<int> > re_maps;
	std::list<int> sequence;

	void re_dfs(const int u) {
		visited[u] = 1;
		for(const auto& v : this->re_maps[u]) 
			if(visited[v] == 0)
				this->re_dfs(v);
		this->sequence.push_front(u);
	}

	void dfs(const int u) {
		color[u] = cnt;
		for(const auto v : this->maps[u])
			if(color[v] == 0)
				this->dfs(v);
		std::cout << u << "  ";
	}
public:
	Kosaraju(const int _len) 
		: len(_len), visited(_len, 0), color(_len, 0), exist(_len, 0),
		  maps(_len, std::vector<int>()), re_maps(_len, std::vector<int>())
	{}

	void search() {
		for(int i = 0;i < len; ++i)
			if(exist[i] and visited[i] == 0)
				this->re_dfs(i);
		for(const auto u : this->sequence) {
			if(color[u] == 0) {
				++cnt;
				std::cout << "NO." << cnt << " { ";
				this->dfs(u);
				std::cout << " }\n";
			}
		}
	}

	void addEdge(const int l, const int r) {
		this->maps[l].emplace_back(r);
		this->re_maps[r].emplace_back(l);
		this->exist[l] = this->exist[r] = 1;
	}
};

int main() {
	Kosaraju one(10);
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
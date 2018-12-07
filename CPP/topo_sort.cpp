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

std::vector< std::vector<int> > maps;
std::vector<int> indegree;
std::vector<int> exist;
int len;

void topoSort() {
	std::queue<int> Q;
	for(int i = 0;i < 10; ++i) 
		if(indegree[i] == 0) 
			Q.push(i);
	int cnt = 0;
	while(!Q.empty()) {
		auto u = Q.front();
		Q.pop();
		++cnt;
		for(int i = 0;i < 10; ++i) 
			if((maps[u][i] not_eq 0) and --indegree[i] == 0)
				Q.push(i);
	}
	std::cout << "cnt :  " << cnt << "\n";
	printf(cnt == len ? "不存在环\n" : "检测到环\n");
}

int main() {
	freopen("./gragh(1).txt", "r", stdin);
	maps.assign(10, std::vector<int>(10, 0));
	indegree.assign(10, 0);
	int i, l, r;
	std::cin >> len;
	for(i = 0;i < len; ++i) {
		std::cin >> l >> r;
		++indegree[r];
		maps[l][r] = 1;
	}
	for(int i = 0;i < 10; ++i) {
		std::cout << i << "\t入度  :  " << indegree[i] << "\n";
	}
	topoSort();
	logCall("结束\n");
	return 0;
}
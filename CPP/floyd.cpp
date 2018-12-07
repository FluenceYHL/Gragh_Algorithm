/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:     floyd.cpp
  *Author:       刘畅
  *Version:      1.0
  *Date:         2018.12.init
  *Description:  floyd 传递闭包  证明是否存在环
  *Compile:      g++ -std=c++14 floyd.cpp -o gragh -lpthread
  *Function List:  
  *History:  
  *Preference:  
**********************************************************************************/
#include "gnuplot.hpp"
#include <queue>
#include <assert.h>
static constexpr int init = 6;
int dp[init][init];

void floyd() {
    for(int k = 0;k < init; ++k)
        for(int i = 0;i < init; ++i)
            for(int j = 0;j < init; ++j)
                dp[i][j] |= (dp[i][k] and dp[k][j]);
    for(int i = 0;i < init; ++i) 
        for(int j = 0;j < init; ++j) 
            if(dp[i][j] and dp[j][i]) {
                std::cout << "检测到环\n";
                return;
            }
}

int main() {
    freopen("./gragh(1).txt", "r", stdin);
    int len, l, r;
    std::cin >> len;
    for(int i = 0;i < len; ++i) {
        std::cin >> l >> r;
        dp[l][r] = 1;
    }
    floyd();
    return 0;
}

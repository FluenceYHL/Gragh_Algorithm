/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:     tarjan.cpp
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


using namespace std ;
const int Max = 100 ;
int n , m , start , end , index , ans ;
int low[Max] , dfn[Max] , Color[Max] ;
vector<int> Gragh[max] ;
stack<int> One ;

void dfs( int cur ){
	low[cur] = dfn[cur] = ++index ;
	One.push( cur ) ;                       //压栈
	for(int i = 0 ; i < (int)Gragh[cur].size() ; ++i ){
		int v = Gragh[cur][i] ;
		if( dfn[v] == 0 ){
			dfs( v ) ;
			low[cur] = min( low[cur] , low[v] ) ;
		}
		else if( Color[v] == 0 )                  //如果访问过了，而且还没有被弹出栈，还不属于任何连通分量
			low[cur] = min( low[cur] , dfn[cur] ) ;  //出现了环，递归更新环的 low 值
	}
	if( dfn[cur] == low[cur] ){    //只有连通分量的根节点 low == dfn 
		ans ++ ;
		cout << "NO." << ans << "  {  " ;   //注意这个是  搜索了所有邻接点之后 ， 再判断的
		while( 1 ){                         //因为出现环 ， 还可能被更大的环包围 
			int top = One.top() ;
			cout << top << " " ;
			One.pop() ;
			Color[top] = ans ;   //染色 ， 属于这个连通分量的颜色是 ans
			if( top == cur )
				break ;
		}
		cout << " }" << endl ;
	}
}
int main(){
	cin >> n >> m ;
	for(int i = 1 ; i <= m ; ++i ){
		cin >> start >> end ;
		Gragh[start].push_back( end ) ;
	}
	for(int i = 1 ; i <= n ; ++i )  //因为是有向图 ， 一次 dfs 可能走不完
		if( dfn[i] == 0 )
			dfs( i ) ;
	return 0 ;
}

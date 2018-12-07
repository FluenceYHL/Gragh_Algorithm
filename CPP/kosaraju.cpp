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

using namespace std ;
const int Max = 100 ;
int n , m , start , end , k1 , k2 , ans , NO , index[Max] ;
struct Node{
	int end , next ;
} Edge[Max] , Re_Edge[Max] ;
int head[Max] ;
int Re_head[Max] ;
int book[Max] , color[Max] ;
void Add_Edge( int start , int end ){
	Edge[k1].end = end ;
	Edge[k1].next = head[start] ;
	head[start] = k1++ ;
}
void Re_Add_Edge( int start , int end ){
	Re_Edge[k2].end = end ;
	Re_Edge[k2].next = Re_head[start] ;
	Re_head[start] = k2++ ;
}
void dfs( int cur ){
	book[cur] = 1 ;
	for( int i = head[cur] ; i != -1 ; i = Edge[i].next ){
		int v = Edge[i].end ;
		if( book[v] == 0 )
			dfs( v ) ;
	}
	index[ ++NO ] = cur ;
}
void Re_dfs( int cur ){
	color[cur] = ans ;
	cout << cur << " " ;
	for(int i = Re_head[cur] ; i != -1 ; i = Re_Edge[i].next ){
		int v = Re_Edge[i].end ;
		if( color[v] == 0 )
			Re_dfs( v ) ;
	}
}
void Kosaraju(){
	for(int i = 1 ; i <= n ; ++i )
		if( book[i] == 0 )
			dfs( i ) ;
	for(int i = NO ; i >= 1 ; --i ){
		int v = index[i] ;
		if( color[v] == 0 ){
			ans ++ ;
			cout << "NO." << ans << "  {  " ;
			Re_dfs( v ) ;
			cout << " }" << endl ;
		}
	}
}
int main(){
	cin >> n >> m ;
	k1 = k2 = 1 ;
	memset( head , -1 , sizeof( head ) ) ;
	memset( Re_head , -1 , sizeof( Re_head ) ) ;
	for(int i = 1 ; i <= m ; ++i ){
		cin >> start >> end ;
		Add_Edge( start , end ) ;
		Re_Add_Edge( end , start ) ;
	}
	Kosaraju() ;
	return 0 ;
}
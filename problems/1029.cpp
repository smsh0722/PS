#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

const int MAX_N = 15;
const int CASE_NUM = (1<<15)-1; // 0(000 0000 0000 0000)
vector<vector<int>> srcToDstCostMat(MAX_N);
vector<vector<vector<int>>> memo( MAX_N, vector<vector<int>>(10, vector<int>(CASE_NUM, -1)) ); //NOTE: 최종 구매자, 가격, 루트 세 가지 생각해야하므로 3D

int visited = 0;
int N; // num of artist

int FindMaxNumBuyerRecursive( int src, int price, int depth );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;

    for ( int r = 0; r < N; r++ ){
        string s;
        cin >> s;
        for ( int c = 0; c < N; c++ )
            srcToDstCostMat[r].push_back(s.at(c)-'0');
    }

    visited = 1;
    cout << FindMaxNumBuyerRecursive(0, 0, 1);

    return 0;
}

int FindMaxNumBuyerRecursive( int src, int price, int depth )
{
    // base Case
    if ( depth == N )
        return 1;

    // use memo
    if ( memo[src][price][visited] != -1 )
        return memo[src][price][visited];
    
    // Search
    int count = 0;
    const int savedVisited = visited;
    for ( int i = 0; i < N; i++ ){
        // Skip visited
        if ( (savedVisited & (1<<i)) != 0 )
            continue;

        // Search Rec
        if( srcToDstCostMat[src][i] >= price ){
            visited = (savedVisited | (1<<i));
            int rst = FindMaxNumBuyerRecursive( i, srcToDstCostMat[src][i], depth+1);
            if ( count < rst )
                count = rst;
        }
    }

    visited = savedVisited;
    memo[src][price][visited] = count+1;
    return memo[src][price][visited];
}
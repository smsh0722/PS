/*
disjoint set
연결 되어 있나? -> 방문 가능 테스트. (DFS)
              -> 집합 유지 (disjoint set)
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_CITY = 200;

int N; // num of city
int M; // num of city to travel

vector<int> parents(MAX_CITY, -1);
vector<int> ranks(MAX_CITY, 0);

int FindRecursive( int n )
{
    return parents[n] == n ? n : (parents[n] = FindRecursive(parents[n]));
}
void Union ( int a, int b )
{
    int pa = FindRecursive(a);
    int pb = FindRecursive(b);
    
    if ( pa == pb )
        return;

    if ( ranks[pa] == ranks[pb] ){
        parents[pb] = pa;
        ranks[pa]++;
    }
    else if (ranks[pa] > ranks[pb] ) 
        parents[pb] = pa;
    else // ranks[pa] < ranks[pb]
        parents[pa] = pb;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    cin >> M;
    for ( int c = 0; c < N; c++ ){
        parents[c] = c;
    }
    for ( int r = 0;  r < N; r++ ){
        for ( int c = 0; c < N; c++ ){
            int in;
            cin >> in;
            if ( in == 1 ){
                Union(r, c);
            }
        }
    }

    int city;
    cin >> city;
    int pa = FindRecursive(city-1);
    for ( int i = 1; i < M; i++ ){
        cin >> city;
        int pb = FindRecursive(city-1);
        if (pa != pb ){
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";

    return 0;
}
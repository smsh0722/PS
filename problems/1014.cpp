#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Num of Tests
int C;
// Size of class NxM
int N, M;

unordered_map<string, int> dpMemo;

inline void PrintDebug( string& s )
{
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            cout << s[r*M+c];
        }cout << "\n";
    }
}
inline int GetPos( int r, int c )
{
    return (r*M + c);
}
int DFS( int r, int c, string& s )
{
    // cout << "Cur DFS " << r << ", " << c << "\n"; // Debug
    // PrintDebug(s); // Debug
    if ( r >= N )
        return 0;
    if ( dpMemo.find(s) != dpMemo.end() )
        return dpMemo[s];
    
    int nextR = r+((c+1)/M);
    int nextC = (c+1)%M;
    int rst1 = 0;
    int rst2 = 0;
    // Case1: Include this seat
    if ( s[GetPos(r,c)] != 'x' ){
        string s1 = s;
        s1[GetPos(r,c)] = 'x';
        if ( c - 1 >= 0 ){
            s1[GetPos(r, c-1)] = 'x';
            if ( r+1 < N )
                s1[GetPos(r+1,c-1)] = 'x';
        }
        if ( c + 1 < M ){
            s1[GetPos(r,c+1)] = 'x';
            if ( r+1 < N)
                s1[GetPos(r+1,c+1)] = 'x';
        }
        rst1 = DFS( nextR, nextC, s1 ) + 1;
    }
    // Case2: Exclude this seat
    string s2 = s;
    s2[GetPos(r,c)] = 'x';
    rst2 = DFS( nextR, nextC, s2 );

    // Save Max
    return (dpMemo[s] = max(rst1, rst2));
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> C;
    for ( int test = 0; test < C; test++ ){
        // Get input
        cin >> N >> M;
        string s;
        string tmp;
        for ( int i = 0; i < N; i++ ){
            cin >> tmp;
            s += tmp;
        }

        // Solve (Memoization)
        cout << DFS(0,0, s) << endl;
    }

    return 0;
}
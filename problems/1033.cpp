/* NOTE:
1)
LCM 알고리즘
2)
곱해지는 수 범위 고려해서 자료형 잘 세팅하기
*/
#include <iostream>
#include <vector>
using namespace std;

struct Ratio {
    int64_t p;
    int64_t q;
    bool operator!=(const Ratio& other) const 
    {
        return !(p == other.p && q == other.q);
    }
};

struct Edge{
    int dst;
    Ratio ratio;
};

const Ratio NULL_RATIO = {0,0};

int N;
// {[src][idx] : Edge}
vector<vector<Edge>> adjList;
// Ratios from N-1 to idx
vector<Ratio> ratios;

inline int GCD( int64_t a, int64_t b )
{
    if ( a < b)
        swap(a, b);
    
    int64_t r = a % b;
    while ( r != 0 ){
        a = b;
        b = r;
        r = a % b;
    }

    return b;
}
inline int64_t LCM( int64_t a, int64_t b )
{
    int64_t gcd = GCD( a, b);
    return (a * b / gcd);
}
inline void Minimize( Ratio& r )
{
    int64_t gcd = GCD( r.p, r.q);
    r.p /= gcd;
    r.q /= gcd;
}
void DFS( int node, Ratio r )
{
    // cout << "Node: " << node << endl; // Debug

    for ( size_t i = 0; i < adjList[node].size(); i++ ){
        Edge e = adjList[node][i];
        if ( ratios[e.dst] != NULL_RATIO ) { // visited
            continue;
        }
        
        // Get New Ratio
        // p1 : q1, p2: q1
        int64_t lcm = LCM( r.q, e.ratio.p );       
        Ratio newRatio = { r.p * (lcm / r.q), e.ratio.q * (lcm / e.ratio.p) };
        Minimize(newRatio);

        ratios[e.dst] = newRatio;
        DFS( e.dst, newRatio );
    }
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    adjList.resize(N);
    ratios.resize(N, NULL_RATIO);
    for ( int i = 0; i < N-1; i++ ){
        int a, b;
        Ratio r;
        cin >> a >> b >> r.p >> r.q;

        Minimize(r);
        adjList[a].push_back({b, Ratio{r.p, r.q}}); // (a,b) = p : q
        adjList[b].push_back({a, Ratio{r.q, r.p}});// (b, a) = q : p
    }

    // DFS
    ratios[N-1] = {1, 1};
    DFS(N-1, {1, 1});

    // for ( int i = 0 ; i < N; i++ ){
    //     printf("%d:%d = %d:%d\n", N-1, i, ratios[i].p, ratios[i].q); // Debug
    // }

    int64_t lcm = 1;
    for ( int i = 0; i < N; i++ ){
        lcm = LCM( lcm, ratios[i].p );
    }
    for ( int i = 0; i < N; i++ ){
        cout << ratios[i].q * ( lcm/ ratios[i].p ) << " ";
    }

    return 0;
}
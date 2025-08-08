/* NOTE:
array erase는 뒤에 있는 모든 원소를 이동시키 때문에 비효율적
custom erase 필요.

1) 다른 방안: Segment Tree
But, 범위가 크고 깊이가 있어서 재귀로 인한 시간 소요가 크다.
-> iterative Segment tree 구현

2) disjoint set
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAX_INT = ~(1<<31);
const int MAX_NUM = 4000000;

struct SegTree{
    int n;
    vector<int> arr;
};

int N; // num of Cards
int M; // num of picks
int K; // num of Games

SegTree st;

inline void UpdateST( int trg, int val )
{
    int i = st.n+trg;
    st.arr[i] = val;
    while ( i > 1 ){
        int p = i >> 1;
        st.arr[p] = min(st.arr[p*2], st.arr[p*2+1]);
        i = p;
    }
}

inline int GetMinST( int tl, int tr )
{
    int li = st.n + tl;
    int ri = st.n + tr;
    int m = MAX_INT;
    while ( li < ri ){
        if ( li & 1 ){
            m = min(m, st.arr[li]);
            li++;
        }
        if ( ri & 1 ){
            ri--;
            m = min( m, st.arr[ri]);
        }
        li >>= 1;
        ri >>= 1;
    }
    return m;
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;

    st.n = MAX_NUM+1;
    st.arr.resize(st.n*2, MAX_INT);
    
    for ( int i = 0; i < M; i++ ){
        int c;
        cin >> c;
        UpdateST(c, c);
    }

    for ( int k = 0; k < K; k++ ){
        int c;
        cin >> c;

        int ans = MAX_INT;
        if ( c < MAX_NUM ){
            ans = GetMinST(c+1, MAX_NUM+1);
        }
        if ( ans == MAX_INT ){
            ans = GetMinST(1, c+1);
        }
        cout << ans << "\n";
        UpdateST(ans, MAX_INT );
    }

    return 0;
}
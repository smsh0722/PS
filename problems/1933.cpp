/*  NOTE:
    범위에서 최대 구하기 = segment tree를 떠올렸다.
    그러나 range가 너무 넓어 공간 복잡도가 불가능했다.
    고심 끝에, 축을 range가 아닌 건물 번호로 사용하기로 생각했다.
    건물 번호는 0에 가까운 건물부터 나오도록 정렬후 사용했다.
    (+ 건물 시작번호가 같은 경우, 끝 번호가 같은 경우를 고려하지 못해 헤맸다. 
        다른 문제에서도 자주 실수한 부분이다. 어떻게 처리해야할 지 미리 고민하자)
    SOL2:
    다른 방법으로도 풀 수 있는 것으로 보인다. 고민해보자.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

struct Building{
    int lx;
    int h;
    int rx;
};

struct SegmentTree{
    int h;
    int size;
    vector<int> arr;
};

int N;
vector<Building> buildings;
SegmentTree st;

struct EndCompare{
    bool operator()( const int a, const int b )
    {
        if ( buildings[a].rx == buildings[b].rx )
            return buildings[a].h > buildings[b].h;
        return  buildings[a].rx > buildings[b].rx;// rx 오름차순 정렬
    }
};
priority_queue<int, vector<int>, EndCompare> endPQ;

bool BuildingCompare( const Building& a, const Building& b )
{
    if ( a.lx == b.lx )
        return a.h > b.h;
    return a.lx < b.lx; // 오름차순 정렬, l작은 것부터 나오게
}

int BuildST( int node, int l, int r )
{
    if ( l == r ){
        st.arr[node] = buildings[l].h;
        return st.arr[node];
    }

    int mid = (r-l)/2 +l;
    int lRst = BuildST(node*2+1, l, mid );
    int rRst = BuildST(node*2+2, mid+1, r );
    
    st.arr[node] = max(lRst, rRst);

    return st.arr[node];
}
int FindST( int node, int l, int r, int tl, int tr )
{
    if ( r < tl || tr < l )
        return 0;
    if ( tl <= l && r <= tr )
        return st.arr[node];
    
    int mid = (r-l)/2 +l;
    int lRst = FindST(node*2+1, l, mid, tl, tr );
    int rRst = FindST( node*2+2, mid+1, r, tl, tr );

    return max(lRst, rRst);
}
int UpdateST( int node, int l, int r, int ti, int val )
{
    if ( r < ti || ti < l )
        return st.arr[node];
    if ( l== r && l == ti ){
        st.arr[node] = val;
        return st.arr[node];
    }

    int mid = (r-l)/2+l;
    int lRst = UpdateST( node*2+1, l, mid, ti, val );
    int rRst = UpdateST( node*2+2, mid+1, r, ti, val );

    st.arr[node] = max(lRst, rRst);
    return st.arr[node];
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int i = 0; i < N; i++ ){
        int lx, h, rx;
        cin >> lx >> h >> rx;
        buildings.push_back( Building{lx, h, rx} );
    }

    sort( buildings.begin(), buildings.end(), BuildingCompare );

    st.h = ceil(log2(N));
    st.size = (1<<(st.h+1)) -1;
    st.arr.resize(st.size, 0 );
    BuildST(0, 0, N-1);

    cout << buildings[0].lx << " " << buildings[0].h << " ";
    endPQ.push(0);
    for ( int bi = 1; bi < N; bi++ ){
        while ( endPQ.empty() == false ){
            int ebi = endPQ.top();
            if ( buildings[ebi].rx < buildings[bi].lx ){
                endPQ.pop();

                int prevH = FindST(0,0,N-1,0, bi-1);
                UpdateST(0, 0, N-1, ebi, 0 );
                int curH = FindST(0, 0, N-1, 0, bi-1);
                if ( prevH != curH )
                    cout << buildings[ebi].rx << " " << curH << " ";
            }
            else 
                break;
        }
        int maxH = FindST(0, 0, N-1, 0, bi-1);
        if ( maxH < buildings[bi].h )
            cout << buildings[bi].lx << " " << buildings[bi].h << " ";
        endPQ.push(bi);
    }
    while ( endPQ.empty() == false ){
        int ebi = endPQ.top();
        endPQ.pop();

        int prevH = FindST(0,0,N-1, 0, N-1);
        UpdateST(0, 0, N-1, ebi, 0 );
        int curH = FindST(0, 0, N-1, 0, N-1);
        if ( prevH != curH )
            cout << buildings[ebi].rx << " " << curH << " ";
    }

    return 0;
}
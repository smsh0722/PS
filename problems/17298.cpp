/* sol) Segment Tree
1. stack(monotone stack)이 더 빠르다.
2. ST 구현 상의 주의점 아래에서 확인.
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_INT = ~(1<<31);
const int MAX_N = 1000000;

// Segtree for [0,r]
// Data for left most occurence idx for each num
struct SegmentTree{
    int l = 0;
    int r;
    int h;
    vector<int> arr;
    int UpdateRecursive( int node, int l, int r, int trg, int val )
    {
        // NOTE: bound 벗어남 -> leaf 순으로 체크! 거꾸로 했다가 틀림.
        if ( trg < l || r < trg ) 
            return MAX_INT;
        if ( l == r )
            return arr[node] = val;

        
        int mid = (r-l)/2+l;
        int lRst = UpdateRecursive(node*2+1, l, mid, trg, val );
        int rRst = UpdateRecursive(node*2+2, mid+1, r, trg, val);

        return arr[node] = min(lRst, rRst);
    }
    int GetMinRecursive( int node, int l, int r, int tl, int tr )
    {
        if ( r < tl || tr < l )
            return MAX_INT;
        if ( tl <= l && r <= tr )
            return arr[node];
        
        int mid = (r-l)/2+l;
        int lRst = GetMinRecursive(node*2+1, l, mid, tl, tr );
        int rRst = GetMinRecursive(node*2+2, mid+1, r, tl, tr );

        return min(lRst, rRst);
    }

};

// Size of sequence
int N;

vector<int> sequence;
vector<int> answers;

SegmentTree st;


int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    sequence.resize(N,0);
    answers.resize(N,-1);
    for ( int i = 0; i < N; i++ ){
        cin >> sequence[i];
    }

    // build st
    st.r = MAX_N;
    st.h = ceil(log2(st.r + 1 ));
    st.arr.resize((1<<(st.h+1))-1, MAX_INT);

    // Get answer backward and store
    for ( int i = N-1; i >= 0; i-- ){
        // Get ans
        int idx = MAX_INT;
        if ( sequence[i] < MAX_N ) 
            idx = st.GetMinRecursive(0, st.l, st.r, sequence[i]+1, st.r );
        answers[i] = idx == MAX_INT ? -1 : sequence[idx];

        // Update Seg
        st.UpdateRecursive(0, st.l, st.r, sequence[i], i);
    }

    // Ans 
    for ( int i = 0; i < N; i++ )
        cout << answers[i] << " ";

    return 0;
}
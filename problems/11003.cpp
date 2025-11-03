/* NOTE:
전형적인 Segtree 처럼 보인다.
전체 시간 복잡도는 O(nlogn)으로 억대이다.
그러나, 단순한 segtree는 재귀함수라는 특성으로 TLE가 발생할 수 있다.

SOL)
iterative segtree

Learn)
Deque로도 풀 수 있다고한다.
*/
#include <iostream>
#include <vector>
using namespace std;

struct SegTree{
    int n;
    int h;
    int size;
    vector<int> arr;
};

// # of elements
int N;
// Length of search range
int L;

SegTree st;

vector<int> seq;

void ConstructST()
{
    for ( int i = 0; i < st.n; i++ )
        st.arr[st.n + i] = seq[i];

    for ( int i = st.n-1; i > 0; i-- ){
        st.arr[i] = min( st.arr[i*2], st.arr[i*2+1] );
    }
}

int GetMin( int l, int r )
{
    int ans = INT32_MAX;

    l += st.n;
    r += st.n;

    while ( l <= r ){
        if ( !(r & 1) ){ 
            ans = min(ans, st.arr[r]);
            r--;
        }

        if ( l & 1 ){
            ans = min(ans, st.arr[l] );
            l++;
        }

        l /= 2;
        r /= 2;
    }

    return ans;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> L;
    seq.resize(N);
    for ( int ni = 0; ni < N; ni++ )
        cin >> seq[ni];

    st.n = N;
    st.size = 2*st.n;
    st.arr.resize(st.size);
    ConstructST();

    for ( int r = 0; r < N; r++ ){
        int l = max(0, r - L + 1);
        cout << GetMin(l, r) << " ";
    }

    return 0;
}
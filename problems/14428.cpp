#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 100000;
const int MAX_INT = ~(1<<31);

struct Node {
    int from;
    int value;
    bool operator<(const Node& other ) const
    {
        if ( value == other.value )
            return from < other.from;
        return value < other.value;
    }
};

int N; // size of sequence a(0)~a(N-1)
int M; // num of query
vector<Node> segTree;

void UpdateST( int trg, int val )
{
    int i = N+trg;
    segTree[i].value = val;
    while ( i > 0 ){
        i = i >> 1;
        segTree[i] = segTree[i*2] < segTree[i*2+1] ? segTree[i*2] : segTree[i*2+1];
    }
}
Node GetMin( int l, int r )
{
    l = N + l;
    r = N + r;
    
    Node rst = {0, MAX_INT};
    while ( l < r ){
        if ( l & 1 ){
            rst = rst < segTree[l] ? rst : segTree[l];
            l++;
        }
        
        if ( r & 1 ){
            r--;
            rst = rst < segTree[r] ? rst : segTree[r];
        }

        l >>= 1;
        r >>= 1;
    }

    return rst; 
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
 
    cin >> N;
    segTree.resize(2*N, {0, MAX_INT});
    for ( int i = 0; i < N; i++ ){
        int a;
        cin >> a;
        segTree[N+i] = {i, a};
    }

    // Build SegTree
    for ( int i = N-1; i > 0; i-- ){
        segTree[i] = segTree[i*2] < segTree[i*2+1] ? segTree[i*2] : segTree[i*2+1];
    }

    cin >> M;
    for ( int m = 0; m < M; m++ ){
        int q, a, b;
        cin >> q >> a >> b;
        if ( q == 1 ){ // Update
            UpdateST( a-1, b);
        }
        else { // q == 2, GetMin
            Node rst = GetMin( a-1, b );
            cout << rst.from + 1 << "\n";
        }
    }

    return 0;
}
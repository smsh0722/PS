/* NOTE: RMQ-based LCA 
Level + SegTree
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int INT_INF = ~(1<<31);

struct SegTree{
    size_t N;
    struct Node{
        int level;
        int nodeNum;
    };
    vector<Node> arr;
};

// num of nodes
int N;
// num of queries
int M;

vector<vector<int>> adjList;
vector<bool> visited;
vector<int> firstAppear;
vector<int> seqMemo;
vector<int> levelMemo;
SegTree st;

int level = 0;
int seqIdx = 0;

void DoMemo( int node )
{
    if ( firstAppear[node] == -1 )
        firstAppear[node] = seqIdx;
    seqMemo.push_back( node );
    levelMemo.push_back( level );
    seqIdx++;
}

void DFS( int node )
{
    visited[node] = true;
    level++;
    
    DoMemo(node);    

    for ( size_t i = 0; i < adjList[node].size(); i++ ){
        int dst = adjList[node][i];
        if ( visited[dst] == false ){
            DFS(dst);

            DoMemo(node);
        }
    }

    level--;
}

SegTree::Node BuildST( int node, int l, int r )
{
    if ( l == r ){
        return (st.arr[node] = {levelMemo[l], seqMemo[l]} );
    }

    int mid = (r-l)/2 + l;
    SegTree::Node lRst = BuildST( node*2+1, l, mid );
    SegTree::Node rRst = BuildST(node*2+2, mid+1,r);
    if ( lRst.level < rRst.level ){
        st.arr[node] = lRst;
    }
    else 
        st.arr[node] = rRst;
    return st.arr[node];
}

SegTree::Node MinST( int node, int l, int r, int tl, int tr )
{
    if ( tl <= l && r <= tr )
        return st.arr[node];
    if ( r < tl || tr < l )
        return {INT_INF, -1};
    
    int mid = (r-l)/2+l;
    SegTree::Node lRst = MinST(node*2+1, l, mid, tl, tr);
    SegTree::Node rRst = MinST(node*2+2, mid+1, r, tl, tr );
    if ( lRst.level < rRst.level )
        return lRst;
    else
        return rRst;
}

void PrintDebug( const vector<int>& arr )
{
    for ( size_t i = 0; i < arr.size(); i++ ){
        cout << arr[i] << " ";
    } cout << endl;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    adjList.resize(N+1);
    visited.resize(N+1, false);
    firstAppear.resize(N+1,-1);
    for ( int i = 0; i < N-1; i++ ){
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    // Memo DFS
    DFS(1);

    st.N = seqIdx;
    int h = ceil(log2(st.N));
    int size = (1<<(h+1))-1;
    st.arr.resize( size );
    BuildST(0, 0, st.N-1);

    // cout << "firstApear: ";
    // PrintDebug( firstAppear );
    // cout << "seqMemo: ";
    // PrintDebug( seqMemo );
    // cout << "levelMemo: ";
    // PrintDebug( levelMemo );

    cin >> M;
    for ( int m = 0; m < M; m++ ){
        int a, b;
        cin >> a >> b;
        int aFA = firstAppear[a];
        int bFA = firstAppear[b];
        if ( aFA > bFA )
            swap(aFA,bFA);
        
        // cout << "AF, BF: " << aFA<< " " << bFA << endl; // Debug

        SegTree::Node rst = MinST( 0, 0, st.N-1, aFA, bFA );
        cout << rst.nodeNum << "\n";
    }

    return 0;
}
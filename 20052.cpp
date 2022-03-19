/* smsh0722
 * 20052
 * 괄호 문자열 ?
 * */
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

struct st_node{
    int o; // remaining opening parenthesis
    int c; // reamining closing parenthesis
};

st_node* constructST( char* S );
st_node constructSTUtil( st_node* ST, int idx, int l, int r, char* S );
st_node ansQuery( st_node* ST, int idx, int l, int r, int trgL, int trgR );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    char* S = new char[100001]; // 100,001
    memset( S, '\0', 100001 );
    cin >> S;

    // Build ST;
    st_node* ST = constructST( S );
    int seqLen = strlen(S);

    // Query
    int count = 0;
    int M;
    cin >> M;
    for ( int i = 0; i < M; i++ ){
        int l, r;
        cin >> l >> r;
        st_node ans = ansQuery( ST, 0, 0, seqLen-1, l-1, r-1 );
        
        count += (int)( ans.o == 0 && ans.c == 0 );
    }

    cout << count << "\n";
    
    return 0;
}


st_node* constructST( char* S )
{
    int seqLen = strlen(S);
    int h = ceil( log2( seqLen ) );
    int size = ( 1 << (h+1) ) - 1;

    st_node* ST = new st_node[size];

    constructSTUtil( ST, 0, 0, seqLen - 1, S );

    return ST;
}
st_node constructSTUtil( st_node* ST, int idx, int l, int r, char* S ){
    // Base Case
    if ( l == r ){
        ST[idx].o = ( S[l] == '(' );
        ST[idx].c = ( S[r] == ')' );
        return ST[idx];
    }

    int mid = ( r - l ) / 2 + l;
    st_node lval = constructSTUtil( ST, idx*2+1, l, mid, S );
    st_node rval = constructSTUtil( ST, idx*2+2, mid+1, r, S );

    int gap = lval.o < rval.c ? lval.o : rval.c; // min 
    
    ST[idx].c = lval.c + rval.c - gap;
    ST[idx].o = lval.o + rval.o - gap;

    // cout << l+1 << "," << r+1 << " = " << ST[idx].c << ", " << ST[idx].o << "\n"; // Debug

    return ST[idx];
}
st_node ansQuery( st_node* ST, int idx, int l, int r, int trgL, int trgR )
{
    // OutOfRange
    if ( trgR < l || r < trgL )
        return st_node{0,0};
    // InRange
    if ( trgL <= l && r <= trgR )
        return ST[idx];

    // Partly In
    int mid = ( r - l ) / 2 + l;
    st_node lval = ansQuery( ST, idx*2+1, l, mid, trgL, trgR );
    st_node rval = ansQuery( ST, idx*2+2, mid+1, r, trgL, trgR );

    int gap = lval.o < rval.c ? lval.o : rval.c; // min 
    
    int c = lval.c + rval.c - gap;
    int o = lval.o + rval.o - gap;

    return st_node{ o, c };
}
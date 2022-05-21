/* smsh0722 
 * 5419
 * 북서풍
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

struct point {
    int x;
    int y;
    int x_rank;
};

bool xAsc_Comp( point p, point q );
bool yAsc_xDes_comp( point p, point q );
int* constructST( int x_range );
int sumST( int* ST, int idx, int l, int r, int trgL, int trgR );
int updateST( int* ST, int idx, int l, int r, int trg, int gap );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int T;
    cin >> T;
    
    while ( T > 0 ){
        int N;
        cin >> N;
        
        vector<point> points;
        // Input points
        {
            int x, y;
            for ( int i = 0; i < N; i++ ){
                cin >> x >> y;
                points.push_back( point{ x, y, -1 } );
            }
        }
        int x_range = 0;
        // Preprocess points
        {
            sort( points.begin(), points.end(), xAsc_Comp );
            
            int prev = points[0].x;
            for ( int i = 0; i < N; i++ ){
                x_range += (prev < points[i].x ? 1 : 0);

                points[i].x_rank = x_range;
                prev = points[i].x;
            }
            
            sort( points.begin(), points.end(), yAsc_xDes_comp );
        }
        
        int64_t sum = 0;
        // Solve
        {
            int* ST;
            ST = constructST( x_range );

            for ( int i = 0; i < N; i++ ){
                sum += (int64_t)sumST( ST, 0, 0, x_range, points[i].x_rank, x_range );

                updateST( ST, 0, 0, x_range, points[i].x_rank, 1 );
            }

            delete[] ST;
        }
        // Print result
        cout << sum << "\n";

        T--;
    }
    
    return 0;
}

bool xAsc_Comp( point p, point q )
{
    return p.x < q.x;
}
bool yAsc_xDes_comp( point p, point q )
{
    if ( p.y == q.y )
        return p.x > q.x;
    return p.y < q.y;
}
int* constructST( int x_range )
{
    int* ST;

    int x_size = x_range + 1;
    int h = ceil( log2(x_size) );
    int size = (1<<(h+1))-1;

    ST = new int[size];
    memset( ST, 0, sizeof(int)*size );
    
    return ST;
}
int sumST( int* ST, int idx, int l, int r, int trgL, int trgR )
{
    if ( trgL <= l && r <= trgR )
        return ST[idx];
    if ( trgR < l || r < trgL )
        return 0;
    
    int mid = ( r - l ) / 2 + l;
    int lval = sumST( ST, idx*2+1, l, mid, trgL, trgR );
    int rval = sumST( ST, idx*2+2, mid+1, r, trgL, trgR );
    
    return (lval + rval);
}
int updateST( int* ST, int idx, int l, int r, int trg, int gap )
{
    if ( l == r && l == trg ){
        ST[idx] += gap;
        return ST[idx];
    }
    if ( trg < l || r < trg )
        return ST[idx];

    int mid = (r - l )/ 2 + l;
    int lval = updateST( ST, idx*2+1, l, mid, trg, gap );
    int rval = updateST( ST, idx*2+2, mid+1, r, trg, gap );

    ST[idx] = lval + rval;

    return ST[idx];
}
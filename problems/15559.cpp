#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Vec2{
    int r, c;
    bool operator==( const Vec2& other ) const
    {
        return (r==other.r)&&(c==other.c);
    }
};

int N, M;
vector<vector<char>> worldMap;
vector<vector<Vec2>> parents;
vector<vector<bool>> visited;

Vec2 GetParentRecursive( int r, int c)
{
    return parents[r][c] == Vec2{r,c} ? Vec2{r, c} :
        (parents[r][c] = GetParentRecursive( parents[r][c].r, parents[r][c].c) );
}
Vec2 GetParentRecursive( const Vec2& cell )
{
    return parents[cell.r][cell.c] == cell ? cell : 
        (parents[cell.r][cell.c] = GetParentRecursive( parents[cell.r][cell.c]) );
}
Vec2 UnionTo( const Vec2& a, const Vec2& b )
{
    Vec2 pb = GetParentRecursive(b);

    parents[a.r][a.c] = pb;
    return pb;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;    
    worldMap.resize( N, vector<char>(M) );
    for ( int r = 0; r < N; r++ ){
        string s;
        cin >> s;
        for ( int c = 0; c < M; c++ ){
            worldMap[r][c] = s[c];
        }
    }

    int ans = 0;
    // Loop all cell and count set
        // Init disjoint set
    parents.resize(N, vector<Vec2>(M) );
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            parents[r][c] = {r, c};
        }
    }
    visited.resize(N, vector<bool>(M, false ) );
        // Loop
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            if ( visited[r][c] == true )
                continue;

            Vec2 cur = Vec2{r, c};
            Vec2 curP = cur;
            Vec2 next = cur;
            
            while ( true ){
                if ( visited[cur.r][cur.c] == true )
                    break;
                visited[cur.r][cur.c] = true;

                char opt = worldMap[cur.r][cur.c];
                if ( opt == 'N' ){
                    next.r--;
                }
                else if ( opt == 'S' ){
                    next.r++;
                }
                else if ( opt == 'W' ){
                    next.c--;
                }
                else { //opt == 'E'
                    next.c++;
                }

                Vec2 nextP = GetParentRecursive(next);
                if ( nextP == curP ){ // self cycle
                    // printf("add in sr,sc(%d, %d), cur(%d,%d), next(%d,%d)\n", r, c, cur.r, cur.c, next.r, next.c);// DEBUG
                    ans++;
                }
                else if ( nextP == next ){ 
                    UnionTo( next, cur );
                }
                else { // cycle to another set
                    UnionTo( cur, next );
                }
                cur = next;
            }
        }
    }
    // answer
    cout << ans;

    return 0;
}
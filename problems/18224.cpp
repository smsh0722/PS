/* 18224 미로에 갇힌 건우
 * Dijkstra
 * smsh0722
 * */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INFINITE = 500 * 500 + 1;

struct edge {
    int r, c;
    int w;
    edge(int r, int c, int w)
    {
        this->r = r;
        this->c = c;
        this->w = w;
    }

};

struct compare{
    bool operator() (const edge& a, const edge& b ){
        return a.w > b.w;
    }
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m;
    int maze[500][500];
    cin >> n >> m;
    for ( int r = 0; r < n; r++ ){
        for ( int c = 0; c < n; c++ )
            cin >> maze[r][c];
    }

    vector<vector<int>> dist( n, vector<int>(n, INFINITE ) );
    bool visited[500][500][20];
    {
        priority_queue< edge, vector<edge>, compare > q;
        q.push( edge(0, 0, 0) );
        dist[0][0] = 0;
        visited[0][0][0] = true;
        while ( q.empty() == false ){
            edge e = q.top(); q.pop();

            int ra[] = { -1, 1, 0, 0 };
            int ca[] = { 0, 0, -1, 1 };
            for ( int i = 0; i < 4; i++ ){
                int r = e.r;
                int c = e.c;
                if ( r + ra[i] == n || c + ca[i] == n )
                    continue;
                if ( r + ra[i] < 0 || c + ca[i] < 0 )
                    continue;

                if ( maze[r+ra[i]][c+ca[i]] == 0 ){
                    r += ra[i];
                    c += ca[i];
                }
                else if ( ( e.w / m ) % 2 == 1 ){ // moon
                    while ( true ){
                        r += ra[i];
                        c += ca[i];
                        if ( r >= n || c >= n )
                            break;
                        if ( maze[r][c] == 0 )
                            break;
                    }
                }
                if ( r < 0 || c < 0 )
                    continue;
                if ( r >= n || c >= n )
                    continue;
                if ( r == e.r && c == e.c )
                    continue;

                if ( maze[r][c] == 0 ){
                    int newDist = e.w + 1;
                    if ( dist[r][c] > newDist ){
                        dist[r][c] = newDist;
                        q.push(edge(r,c,newDist) );
                    }
                    else if ( visited[r][c][newDist%(2*m)] == false ){
                        visited[r][c][newDist%(2*m)] = true;
                        q.push(edge(r,c,newDist) );
                    }
                }
            }
        }
    }

    int S2E = dist[n-1][n-1];
    if ( S2E != INFINITE ){
        cout << S2E /(m*2) + 1<< " ";
        if ( (S2E / m) % 2 == 0 )
            cout << "sun";
        else 
            cout << "moon";
    }
    else {
        cout << "-1\n";
    }
}

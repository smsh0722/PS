#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

struct BFS{
    int x;
    int y;
    int dist;
};

using Point = pair<int, int>; // NOTE: typedef보단 using

// # of points
int N;
// Target y
int T;

map<Point, int> points; // NOTE: map에 key로 struct하면 귀찮아지지만 pair 사용하면 key로 사용 가능

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> T;
    for ( int ni = 0; ni < N; ni++ ){
        Point p;
        cin >> p.first >> p.second;

        points[p] = 0;
    }
    
    queue<BFS> bfs;
    bfs.push({0,0,0});
    while ( bfs.empty() == false ){
        BFS cur = bfs.front();
        bfs.pop();

        for ( int dx = -2; dx <= 2; dx++ ){
            for ( int dy = -2; dy <= 2; dy++ ){
                int nx = cur.x + dx;
                int ny = cur.y + dy;
                Point np{nx,ny}; // NOTE: Uniform Initialization
                if ( points.find(np) == points.end() )
                    continue;
                
                int nDist = cur.dist + 1;
                if ( ny >= T ){
                    cout << nDist;
                    return 0;
                }

                if ( points[np] == 0 ){
                    points[np] = nDist;
                    bfs.push({nx,ny,nDist});
                }
            }
        }
    }

    cout << -1;

    return 0;
}
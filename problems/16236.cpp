#include <iostream>
#include <queue>
using namespace std;

struct point{
    int r, c;
    int dist;
};

void printMap( int** map, const int SIZE, int level, int exp, int time );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;

    int level = 2;
    int exp = 0;
    int time = 0;
    queue<point> Q;
    int** map;

    map = new int*[N];
    for ( int i = 0; i < N; i++ ){
        map[i] = new int[N];
        for ( int j = 0; j < N; j++ ){
            cin >> map[i][j];
            if ( map[i][j] == 9 )
                Q.push( {i, j, 0} );
        }
    }

    int color[N][N];
    for ( int i = 0; i < N; i++ ){
        for ( int j = 0; j < N; j++ )
            color[i][j] = -1;
    }

    point* curPoint = new point{ Q.front().r, Q.front().c, Q.front().dist };
    point* nextPoint = nullptr;
    int dist = 0;
    while ( Q.empty() == false ){
        point trgP = Q.front(); Q.pop();

        dist += trgP.dist - dist;

        // Check Eat
        if ( nextPoint != nullptr && nextPoint->dist < trgP.dist ){
            while (Q.empty() == false )
                Q.pop();
            
            // Eat
            map[curPoint->r][curPoint->c] = 0;
            time += nextPoint->dist;
            dist = 0;
            nextPoint->dist = 0;
            exp++;
            if( level == exp ){
                level++;
                exp = 0;
            }
            delete curPoint;
            curPoint = nextPoint;
            nextPoint = nullptr;

            Q.push( *curPoint );

            map[curPoint->r][curPoint->c] = 9;

            // printMap( map, N, level, exp, time ); // Debug
            continue;
        }

        // Check Feed
        if ( map[trgP.r][trgP.c] > 0 && map[trgP.r][trgP.c] < level && map[trgP.r][trgP.c] <= 6 ){
            point* tmp = new point;
            tmp->r = trgP.r; tmp->c = trgP.c; tmp->dist = trgP.dist;
            if ( nextPoint == nullptr )
                nextPoint = tmp;
            else if ( nextPoint->r > trgP.r )
                nextPoint = tmp;
            else if ( nextPoint->r == trgP.r && nextPoint->c > trgP.c )
                nextPoint = tmp;
        }

        // Push Queue
        int candidateP[4][2]; // 4x(r, c)
        candidateP[0][0] = trgP.r + 1; candidateP[0][1] = trgP.c;
        candidateP[1][0] = trgP.r - 1; candidateP[1][1] = trgP.c;
        candidateP[2][0] = trgP.r;     candidateP[2][1] = trgP.c + 1;
        candidateP[3][0] = trgP.r;     candidateP[3][1] = trgP.c - 1;
        for ( int i = 0; i < 4; i++ ){
            if ( candidateP[i][0] < 0 || candidateP[i][0] >= N )
                continue;
            if ( candidateP[i][1] < 0 || candidateP[i][1] >= N )
                continue;
            int r = candidateP[i][0]; int c = candidateP[i][1];
            if ( map[r][c] <= 6 && map[r][c] <= level && color[r][c] < time){
                Q.push( {r, c, dist+1} );
                color[r][c] = time;
            }
        }

        if ( Q.empty() == true && nextPoint != nullptr ){
            while ( Q.empty() == false )
                Q.pop();

            // Eat
            map[curPoint->r][curPoint->c] = 0;
            time += nextPoint->dist;
            dist = 0;
            nextPoint->dist = 0;
            exp++;
            if( level == exp ){
                level++;
                exp = 0;
            }
            delete curPoint;
            curPoint = nextPoint;
            nextPoint = nullptr;

            Q.push( *curPoint );

            map[curPoint->r][curPoint->c] = 9;
            
            // printMap( map, N, level, exp, time ); // Debug
            continue;
        }
    }

    cout << time;

    return 0;
}

void printMap( int** map, const int SIZE, int level, int exp, int time )
{
    cout << "\nlevel: " << level 
            << ", exp: " << exp
            << ", time: " << time << "\n";
    for ( int i = 0; i < SIZE; i++ ){
        for ( int j = 0; j < SIZE; j++ )
            cout << map[i][j] << " ";
        cout << "\n";
    }
}
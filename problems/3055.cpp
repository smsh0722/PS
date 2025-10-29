#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// RxC Map
int R, C;

struct Vec2{
    int r, c;
    Vec2 operator+(const Vec2& other ) const 
    {
        return {r+other.r, c+other.c};
    }
};
// UpDownLeftRight
const Vec2 UDLR[4] = {
    {-1,0},
    {1,0},
    {0,-1},
    {0,1}
};
struct QData{
    int time;
    Vec2 pos;
};

vector<vector<char>> world;

queue<QData> waterQ;
queue<QData> candQ;

bool IsOutOfRange( const Vec2& pos )
{
    if ( pos.r < 0 || pos.r >= R || pos.c < 0 || pos.c >= C )
        return true;
    return false;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> R >> C;
    world.resize(R, vector<char>(C, '.'));
    for ( int r = 0; r < R; r++ ){
        for ( int c = 0; c < C; c++ ){
            cin >> world[r][c];
            if ( world[r][c] == 'S' ){
                candQ.push( {0,{r,c}});
            }
            else if ( world[r][c] == '*' )
                waterQ.push( {0, {r,c}} );
        }
    }

    int time = 0;
    while ( candQ.empty() == false ){
        time++;
        
        while ( candQ.empty() == false ){
            QData cur = candQ.front();
            if ( cur.time >= time )
                break;
            candQ.pop();

            if ( world[cur.pos.r][cur.pos.c] != 'S' )
                continue;

            for ( int mi = 0; mi < 4; mi++ ){
                Vec2 adj = cur.pos + UDLR[mi];
                if( IsOutOfRange(adj) )
                    continue;
                if( world[adj.r][adj.c] == 'D' ){
                    cout << time;
                    return 0;
                }   
                else if ( world[adj.r][adj.c] == '.' ){
                    world[adj.r][adj.c] = 'S';
                    candQ.push({cur.time+1, adj});
                }         
            }
        }
        while ( waterQ.empty() == false ){
            QData cur = waterQ.front();
            if ( cur.time >= time )
                break;
            waterQ.pop();

            for ( int mi = 0; mi < 4; mi++ ){
                Vec2 adj = cur.pos + UDLR[mi];
                if ( IsOutOfRange(adj) )
                    continue;

                char w = world[adj.r][adj.c];
                if ( w == '.' || w == 'S' ){
                    world[adj.r][adj.c] = '*';
                    waterQ.push({cur.time+1, adj});
                }
            }
        }


    }

    cout << "KAKTUS";

    return 0;
}
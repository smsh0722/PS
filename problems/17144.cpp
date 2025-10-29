#include <iostream>
#include <vector>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2& other ) const 
    {
        return {r+other.r, c+other.c};
    }
    bool operator==( const Vec2& other ) const 
    {
        return (r==other.r&&c==other.c);
    }
};
const Vec2 MOVES[4] = {
    {-1,0},
    {1,0},
    {0,-1},
    {0,1}
};

// RxC room
int R, C;
// Time
int T;

vector<vector<int>> room;
vector<vector<Vec2>> flows;
Vec2 top = {-1,-1};
Vec2 bottom = {-1, -1};

void PrintRoom()
{
    cout << "----Room------\n";
    for ( int r = 0; r < R; r++ ){
        for ( int c = 0; c < C; c++ ){
            cout << room[r][c] << " ";
        } cout << endl;
    }
}
void UpdateRoom()
{
    // 확산
    {
        vector<vector<int>> nextRoom(R, vector<int>(C, 0) );
        nextRoom[top.r][top.c] = -1;
        nextRoom[bottom.r][bottom.c] = -1;
        for ( int r = 0; r < R; r++ ){
            for ( int c = 0; c < C; c++ ){
                if ( room[r][c] == -1 )
                    continue;
                int amount = room[r][c] / 5;
                
                    // 인접 위치 먼지 추가
                int count = 0;
                for ( int mi = 0; mi < 4; mi++ ){
                    Vec2 adj = Vec2{r,c} + MOVES[mi];
                    if ( adj.r < 0 || adj.r >= R || adj.c < 0 || adj.c >= C )   
                        continue;
                    if ( adj == top || adj == bottom )
                        continue;
                    nextRoom[adj.r][adj.c] += amount;
                    count++;
                }
                    // 현재 위치 먼지 감소
                nextRoom[r][c] += (room[r][c] - amount*count);
            }
        }
        room = nextRoom;
    }
    // PrintRoom(); // DEBUG

    vector<vector<int>> nextRoom(R, vector<int>(C, 0) );
    nextRoom[top.r][top.c] = -1;
    nextRoom[bottom.r][bottom.c] = -1;
    for ( int r = 0; r < R; r++ ){
        for ( int c = 0; c < C; c++ ){
            if ( room[r][c] == -1)
                continue;
            Vec2 dst = Vec2{r,c} + flows[r][c];
            if ( dst == top || dst == bottom )
                continue;
            nextRoom[dst.r][dst.c] += room[r][c];
        }
    }
    room = nextRoom;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> R >> C >> T;
    room.resize(R, vector<int>(C) );
    for ( int r = 0; r < R; r++ ){
        for ( int c = 0; c < C; c++ ){
            cin >> room[r][c];
            if ( room[r][c] != -1 )
                continue;

            if ( top.r == -1 && top.c == -1 )
                top = {r,c};
            else 
                bottom = {r,c};
        }
    }

    flows.resize(R, vector<Vec2>(C, {0,0} ));
    for ( int r = 0; r < R; r++ ){
        for ( int c = 0; c < C; c++ ){
            Vec2 flow = {0,0};
            if ( r <= top.r ){
                if ( r == 0 && c > 0){
                    flow = {0,-1};
                }
                else if ( c == 0 && r < top.r ){
                    flow = {1, 0};
                }
                else if ( r == top.r && c < C-1 ){
                    flow = {0, 1};
                }
                else if ( r > 0 && c == C-1 ){
                    flow = {-1, 0};
                }
            }
            else {
                if ( r == bottom.r && c < C-1){
                    flow = {0,1};
                }
                else if ( c == C-1 && r < R-1 ){
                    flow = {1, 0};
                }
                else if ( r == R-1 && c > 0 ){
                    flow = {0, -1};
                }
                else if ( r > bottom.r && c == 0 ){
                    flow = {-1,0};
                }
            }
            flows[r][c] = flow;
        }
    }

    // for ( int r = 0; r < R; r++ ){ // DEBUG
    //     for ( int c = 0; c < C; c++ ){
    //         cout << flows[r][c].r << "," << flows[r][c].c << " ";
    //     }
    //     cout << endl;
    // }

    while ( T > 0 ){
        UpdateRoom();
        T--;
    }

    int ans = 2;
    for ( int r = 0; r < R; r++ ){
        for ( int c = 0; c < C; c++ ){
            ans += room[r][c];
        }
    }

    cout << ans;

    return 0;
}
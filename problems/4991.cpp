/* smsh0722
 * 4991
 * 로봇 청소기
 * */
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int INF = (-1)^(1<<31);
const int MAX_ROOM_SIZE = 20;
const int MAX_OBJECT_SIZE = 11;
int w, h;

struct position{
    int r, c;
    int dist;
};
struct object_data{
    position pos;
    int* dist2obj;
};
struct room_data{
    char roomCondition;
    int objNum;
};

void BFS( room_data** room, object_data* objects, int objects_count, int curObjNum );
int DFS( room_data** room, object_data* objects, int objects_count, int curObjNum, int flags );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    room_data** room;
    {
        room = new room_data*[MAX_ROOM_SIZE];
        for ( int i = 0; i < MAX_ROOM_SIZE; i++ )
            room[i] = new room_data[MAX_ROOM_SIZE];
    }

    object_data* objects;
    {
        objects = new object_data[MAX_OBJECT_SIZE];
        for ( int i = 0; i < MAX_OBJECT_SIZE; i++ )
            objects[i].dist2obj = new int[MAX_OBJECT_SIZE];
    }

    // Start position
    position sPos;
    // # of objects
    int objects_count = 0;

    cin >> w >> h;
    while ( w != 0 && h != 0){
        sPos = position{ -1, -1, 0 };  
        objects_count = 0;

        // Input
        for ( int r = 0; r < h; r++ ){
            for ( int c = 0; c < w; c++ ){
                cin >> room[r][c].roomCondition;
                
                room[r][c].objNum = -1;
                if ( room[r][c].roomCondition == 'o' || room[r][c].roomCondition == '*' ){
                    room[r][c].objNum = objects_count;
                    
                    objects[objects_count].pos = position{ r, c, 0 };
                    
                    objects_count++;

                    if ( room[r][c].roomCondition == 'o' ){
                        sPos.r = r;
                        sPos.c = c;
                    }
                }
            }
        }

        // construct objects->dist2obj
        for ( int i = 0; i < objects_count; i++ ){
            for ( int j = 0; j < objects_count; j++ )
                objects[i].dist2obj[j] = -1;
            
            BFS( room, objects, objects_count, i );
        }

        // Solve 
        {
            bool isSolvable = true;
            for ( int i = 0; i < objects_count; i++ ){
                if (isSolvable == false )
                    break;
                for ( int j = 0; j < objects_count; j++ ){
                    if ( objects[i].dist2obj[j] == -1 ){
                        cout << -1 << "\n";
                        isSolvable = false;
                        break;
                    }
                }
            }
            if ( isSolvable == true ){
                int minDist = INF;
                int flags = 1 << (room[sPos.r][sPos.c].objNum);
                minDist = DFS( room, objects, objects_count, room[sPos.r][sPos.c].objNum, flags );
                
                cout << minDist << "\n";
            }
        }
        
        // next Test Case
        cin >> w >> h;
    }

    return 0;
}

void BFS( room_data** room, object_data* objects, int objects_count, int curObjNum )
{
    bool** visited;
    {
        visited = new bool*[MAX_ROOM_SIZE];
        for ( int i = 0; i < MAX_ROOM_SIZE; i++ ){
            visited[i] = new bool[MAX_ROOM_SIZE];
            memset( visited[i], false, sizeof(bool)*MAX_ROOM_SIZE );
        }
    }

    objects[curObjNum].dist2obj[curObjNum] = 0;
    visited[objects[curObjNum].pos.r][objects[curObjNum].pos.c] = true;

    // BFS
    queue<position> Q;
    Q.push( objects[curObjNum].pos );
    while ( Q.empty() == false ){
        position curPos = Q.front();
        Q.pop();

        position adjCell[4];
        {
            adjCell[0].r = curPos.r - 1; adjCell[0].c = curPos.c;       adjCell[0].dist = curPos.dist + 1;
            adjCell[1].r = curPos.r + 1; adjCell[1].c = curPos.c;       adjCell[1].dist = curPos.dist + 1;
            adjCell[2].r = curPos.r;     adjCell[2].c = curPos.c - 1;   adjCell[2].dist = curPos.dist + 1;
            adjCell[3].r = curPos.r;     adjCell[3].c = curPos.c + 1;   adjCell[3].dist = curPos.dist + 1;
        }

        for ( int i = 0; i < 4; i++ ){
            if ( adjCell[i].r < 0 || adjCell[i].r >= h )
                continue;
            if ( adjCell[i].c < 0 || adjCell[i].c >= w )
                continue;
            if ( visited[adjCell[i].r][adjCell[i].c] == true )
                continue;

            char roomCondition = room[adjCell[i].r][adjCell[i].c].roomCondition;
            if (roomCondition == 'x' )
                continue;
            if ( roomCondition == 'o' || roomCondition == '*' ){
                int trgObjNum = room[adjCell[i].r][adjCell[i].c].objNum;
                objects[curObjNum].dist2obj[trgObjNum] = adjCell[i].dist;
            }
            Q.push( adjCell[i] );
            visited[adjCell[i].r][adjCell[i].c] = true;

        }
    }

    // Delete
    for ( int i = 0; i < MAX_ROOM_SIZE; i++ )
        delete[] visited[i];
    delete[] visited;
}
int DFS( room_data** room, object_data* objects, int objects_count, int curObjNum, int flags )
{
    if ( ((1<<objects_count) - 1) == flags )
        return 0;
    
    int min = INF;
    for ( int i = 0; i < objects_count; i++) {
        if ( ( flags&(1<<i) )!= 0 )
            continue;
        
        int rst = DFS( room, objects, objects_count, i, flags|(1<<i) );
        rst += objects[curObjNum].dist2obj[i];

        
        min = min < rst ? min : rst;
    }

    return min;
}
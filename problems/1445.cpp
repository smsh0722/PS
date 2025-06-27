#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct vec2{
    union{
        struct{int x,y;};
        struct{int r,c;};
    };
};

struct dist{
    int trashCount;
    int nextTrashcount;

    dist operator+(const dist& other) const {
        return dist{
            trashCount + other.trashCount,
            nextTrashcount + other.nextTrashcount
        };
    }
    dist operator-(const dist& other ) const {
        return dist{
            trashCount - other.trashCount,
            nextTrashcount - other.nextTrashcount
        };
    }
    bool operator>(const dist& other ) const {
        if( trashCount < other.trashCount )
            return false;
        else if ( trashCount > other.trashCount )
            return true;
        else if ( nextTrashcount > other.nextTrashcount )
            return true;
        else 
            return false;
    };
};

struct distCompare{
    bool operator() (pair<vec2, dist>& a, pair<vec2, dist>& b ) const {
        return a.second > b.second;
    }
};

const int MAX_NM = 50;
const int MAX_DIST = ~(1<<31);

int N, M; // word: NxM
vector<vector<char>> world(MAX_NM, vector<char>(MAX_NM, '.'));
vector<vector<dist>> distMat( MAX_NM, vector<dist>(MAX_NM, {MAX_DIST, MAX_DIST} ) );
vector<vector<dist>> statusMat( MAX_NM, vector<dist>(MAX_NM, {0,0}));

inline void GetAdjNodes( vector<vec2>& adjNodes, const int r, const int c)
{
    if ( r-1 >= 0)
        adjNodes.push_back({r-1, c});
    if ( r+1 < N )
        adjNodes.push_back({r+1, c});
    if ( c- 1 >= 0 )
        adjNodes.push_back({r, c-1});
    if ( c + 1 < M )
        adjNodes.push_back({r, c+1});
}

int main (void){

    cin >> N >> M;
    
    vec2 sPos, fPos;
    {
        string s;
        for ( int r = 0; r < N; r++ ){
            cin >> s;
            for ( int c = 0; c < M; c++ ){
                world[r][c] = s.at(c);
                if ( world[r][c] == 'S' )
                    sPos = {r, c};
                else if ( world[r][c] == 'F' )
                    fPos = {r, c};
            }
        }
    }   

    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            if ( world[r][c] != 'g' )
                continue;
            statusMat[r][c].trashCount = 1;
            vector<vec2> adjNodes;
            GetAdjNodes(adjNodes, r, c);
            for ( size_t i = 0; i < adjNodes.size(); i++ ){
                vec2 adjNode = adjNodes[i];

                if( world[adjNode.r][adjNode.c] == '.')
                    statusMat[adjNode.r][adjNode.c].nextTrashcount = 1;
            }
        }
    }

    priority_queue<pair<vec2, dist>
        , vector<pair<vec2,dist>>
        , distCompare> pq;
    pq.push(pair<vec2,dist>(sPos, {0,0} ) );
    distMat[sPos.r][sPos.c] = {0,0};
    while ( pq.empty() == false ){
        vec2 curNode = pq.top().first;
        pq.pop();


        vector<vec2> adjNodes;
        GetAdjNodes(adjNodes, curNode.r, curNode.c);

        for ( size_t i = 0; i < adjNodes.size(); i++ ){
            vec2 adjNode = adjNodes[i];
            
            dist curDist = distMat[adjNode.r][adjNode.c];
            dist newDist = distMat[curNode.r][curNode.c] + 
                            statusMat[adjNode.r][adjNode.c];
            if( curDist > newDist ){
                distMat[adjNode.r][adjNode.c] = newDist;
                pq.push(pair<vec2,dist>(adjNode, newDist));                
            }
        }
    }

    cout << distMat[fPos.r][fPos.c].trashCount << " "
        << distMat[fPos.r][fPos.c].nextTrashcount << endl;
}   
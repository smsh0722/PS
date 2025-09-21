#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Num of people
int N;
// Num of laptops adj
int M;


class Hopcroft{
public:
    Hopcroft( int nu, int nv )
    {
        this->nu = nu;
        this->nv = nv;
        mAdjList.resize(nu+1);
        mPairU.resize(nu+1, NIL);
        mPairV.resize(nv+1, NIL);
        mDist.resize(nu+1, INF);
    }
    void AddEdge( int u, int v )
    {
        mAdjList[u].push_back(v);
    }
    int GetMaximumBipartiteMatching()
    {
        int rst = 0;    
        while ( BFS() ){
            for ( int u = 1; u <= nu; u++ ){
                if ( mPairU[u] == NIL && DFS(u) ){
                    rst++;
                }
            }
        }
        return rst;
    }
private:
    const int NIL = 0;
    const int INF = INT32_MAX;

    int nu, nv;
    vector<vector<int>> mAdjList;
    vector<int> mPairU, mPairV, mDist;

    bool BFS()
    {
        queue<int> q;

        for ( int i = 1; i <= nu; i++ ){
            if ( mPairU[i] == NIL ){
                mDist[i] = 0;
                q.push(i);
            }
            else {
                mDist[i] = INF;
            }
        }
        mDist[NIL] = INF;

        while ( q.empty() == false ){
            int u = q.front();
            q.pop();

            if ( mDist[u] < mDist[NIL] ){
                for ( size_t i = 0; i < mAdjList[u].size(); i++ ){
                    int v = mAdjList[u][i];

                    if ( mDist[mPairV[v]] == INF ){
                        mDist[mPairV[v]] = mDist[u] + 1;
                        q.push( mPairV[v] );
                    }
                }
            }
        }

        return (mDist[NIL] != INF);
    }
    bool DFS( int u )
    {
        if ( u == NIL )
            return true;
        
        for ( size_t i = 0; i < mAdjList[u].size(); i++ ){
            int v = mAdjList[u][i];

            if ( mDist[mPairV[v]] == mDist[u] + 1 ){
                if ( DFS( mPairV[v] ) )
                {
                    mPairU[u] = v;
                    mPairV[v] = u;
                    
                    return true;
                }
            }
        }

        mDist[u] = INF;
        return false;
    }
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M;

    Hopcroft h(N, N);
    for ( int i = 0; i < M; i++ ){
        int u, v;
        cin >> u >> v;
        h.AddEdge(u,v);
    }

    cout << h.GetMaximumBipartiteMatching();

    return 0;
}
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct Edge{
    int aPos;
    int bPos;
    int bucketIdx;
};

const int MAX_EDGE = 100000;
vector<Edge> edges;
vector<int> bucket;
stack<int> ans;

int N;

bool EdgeCompare( const Edge& e1, const Edge& e2 )
{
    return e1.aPos < e2.aPos;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int n = 0; n < N; n++ ){
        int a, b;
        cin >> a >> b;
        edges.push_back({a,b,-1});
    }

    sort(edges.begin(), edges.end(), EdgeCompare);

    bucket.push_back(edges[0].bPos);
    edges[0].bucketIdx = 0;
    for ( size_t i = 1; i < edges.size(); i++ ){
        if ( bucket.back() < edges[i].bPos ){
            edges[i].bucketIdx = bucket.size();
            bucket.push_back(edges[i].bPos);
        }
        else {
            int idx = lower_bound(bucket.begin(), bucket.end(), edges[i].bPos) - bucket.begin();
            edges[i].bucketIdx = idx;
            bucket[idx] = edges[i].bPos;
        }
    }
  
    int idx = bucket.size() - 1;
    for ( int i = edges.size()-1; i >= 0; i-- ){
        printf("idx %d, i: %d, edge: %d %d %d\n", idx, i, edges[i].aPos, edges[i].bPos, edges[i].bucketIdx); // Debug
        if ( edges[i].bucketIdx == idx ){
            idx--;
        }
        else {
            ans.push(edges[i].aPos);
        }
    }

    cout << ans.size() << "\n";
    while ( ans.empty() == false ){
        cout << ans.top() << "\n";
        ans.pop();
    }

    return 0;
}
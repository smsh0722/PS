#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Query{
    int qi;
    int l, r;
};

const int MAX_PEOPLE = 300000;  
const int MAX_COLOR = 10000;

// num of peoples
int N;
// num of colors
int C;
// num of queries
int M;
int blockDivisor;

vector<int> seq(MAX_PEOPLE+1, 0);
vector<int> colorCounts(MAX_COLOR+1, 0);
vector<Query> queries;
vector<int> answers;

bool CompareQuery( const Query& a, const Query& b )
{
    int aBlock = a.l / blockDivisor;
    int bBlock = b.l / blockDivisor;
    if ( aBlock == bBlock ){
        if ( aBlock&1 ){ // odd
            return a.r > b.r;
        }
        else {
            return a.r < b.r;
        }
    }

    return aBlock < bBlock;
}

void SetAns( const Query& q )
{
    int color = 0;
    int length = q.r - q.l + 1;
    for ( int i = 1; i <= C; i++ ){
        if ( colorCounts[i] > (length / 2) ){
            color = i;
            break;
        }
    }

    if ( color != 0 )
        answers[q.qi] = color;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> C;
    for ( int i = 1; i <= N; i++ ){
        cin >> seq[i];
    }

    cin >> M;
    queries.resize(M);
    answers.resize(M, 0);
    blockDivisor = ceil(sqrt(M));
    for ( int m = 0; m < M; m++ ){
        cin >> queries[m].l >> queries[m].r;
        queries[m].qi = m;
    }
    sort( queries.begin(), queries.end(), CompareQuery );

    int curL = queries[0].l;
    int curR = queries[0].r;
    for ( int l = queries[0].l; l <= queries[0].r; l++ ){
        colorCounts[seq[l]]++;
    }
    SetAns(queries[0]);
    for ( int i = 1; i < M; i++ ){
        Query q = queries[i];

        while ( curL < q.l ){
            int trg = seq[curL++];
            colorCounts[trg]--;
        }
        while ( curL > q.l ){
            int trg = seq[--curL];
            colorCounts[trg]++;
        }
        while ( curR < q.r ){
            int trg = seq[++curR];
            colorCounts[trg]++;
        }
        while ( curR > q.r ){
            int trg = seq[curR--];
            colorCounts[trg]--;
        }

        SetAns(q);
    }

    for ( int i = 0; i < M; i++ ){
        if ( answers[i] != 0 ){
            cout << "yes " << answers[i] << "\n";
        }
        else {
            cout << "no\n";
        }
    }
    return 0;
}
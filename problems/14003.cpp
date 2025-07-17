/* NOTE: 
grammer:
lower_bound & upper_bound 깊게 이해하자

algorithm
bucket[i]에 올 수 있는-> seq를 가리키는 게 아닌
seq[i]가 bucket에 어느 위치에 있는지 생각할 수 있다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 1000000;
int N;

vector<int> seq;
vector<int> bucket;
vector<vector<int>> sourceIdxOfBucket(MAX_N);

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    seq.resize(N);
    for ( int i = 0; i < N; i++ ){
        int a;
        cin >> a;
        seq[i] = a;
    }

    bucket.push_back(seq[0]);
    sourceIdxOfBucket[0].push_back(0);
    for ( int i = 0; i < N; i++ ){
        if ( bucket[bucket.size()-1] < seq[i] ){
            bucket.push_back(seq[i]);
            sourceIdxOfBucket[bucket.size()-1].push_back(i);
        }
        else {
            int idx = lower_bound( bucket.begin(), bucket.end(), seq[i] ) - bucket.begin();
            bucket[idx] = seq[i];
            sourceIdxOfBucket[idx].push_back(i);
        }
    }

    cout << bucket.size() << endl;
    int min = sourceIdxOfBucket[bucket.size()-1].back();
    for ( int i = bucket.size()-2; i >= 0; i-- ){
        printf( "i : %d, min: %d\n", i, min );
        if ( sourceIdxOfBucket[i].back() > min ){
            vector<int>& sources = sourceIdxOfBucket[i];
            int idx = lower_bound(sources.begin(), sources.end(), min ) - sources.begin()-1;
            printf( "idx %d\n", sources[idx]);
            bucket[i] = seq[sources[idx]];
            min = sources[idx];
        }
        else {
            min = sourceIdxOfBucket[i].back();
        }
    }

    for( size_t i = 0; i < bucket.size(); i++ ){
        cout << bucket[i] << " ";
    }

    return 0;
}
/* NOTE:
2) disjoint set
array로 풀면 사용한 걸 erase 하는 게 오래걸렸다.
기본 erase() 함수는 N이 걸리고, custom으로 pop_back()을 사용하면 정렬이 깨진다.
대안으로 erase 대신 다음을 가리키도록 하면 되는데, disjoint_set 방식을 쓸 수 있다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N; // range of cards
int M; // num of picks
int K; // num of games

vector<int> cards;
vector<int> parents;

int FindParents( int x )
{
    return ( parents[x] == x ? x : parents[x] = FindParents(parents[x]));
}
inline void Union( int x, int y )
{
    int px = FindParents(x);
    int py = FindParents(y);

    parents[px] = py;
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;

    cards.resize(M, 0);
    parents.resize(M);
    for ( int i = 0; i < M; i++ ){
        parents[i] = i;
    }

    for ( int i = 0; i < M; i++ ){
        int card;
        cin >> card;
        cards[i] = card;
    }
    
    sort(cards.begin(), cards.end() );

    for ( int k = 0; k < K; k++ ){
        int card;
        cin >> card;

        int upBoundIdx = upper_bound( cards.begin(), cards.end(), card ) - cards.begin();
        int pi;
        if ( upBoundIdx >= cards.size() )
            pi = FindParents(0);
        else 
            pi = FindParents(upBoundIdx);

        Union( pi, (pi+1)%M);

        cout << cards[pi] << endl; 
    }

    return 0;
}
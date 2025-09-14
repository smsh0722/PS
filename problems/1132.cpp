/* NOTE:
1) BRUTE FORCE
10! x (숫자 개수=50) x (숫자 길이=12) ~= 20억

2) greedy
가중치

+a)
역방향 Loop 에서는 size_t를 쓰면 안 된다. 0에서 감소되면 최대가 되버린다.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int c;
    int64_t w;
};

const int MAX_NUMBER = 9;

// Num of string
int N;
vector<string> numbers;
vector<int64_t> charWeights(MAX_NUMBER+1, 0);

vector<bool> cantBeZeroChar(MAX_NUMBER+1, false);

bool CompareNode( const Node& a, const Node& b )
{
    if ( a.w == b.w )
        return a.c > b.c;
    return a.w > b.w;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    numbers.resize(N);
    for ( int ni = 0; ni < N; ni++ ){
        cin >> numbers[ni];

        int64_t w = 1;
        for ( int i = numbers[ni].length() - 1; i >= 0; i-- ){ // 역방향은 size_t 가 아닌 int 로
            int c = numbers[ni].at(i);
            charWeights[c-'A'] += w;
            w *= 10;

            if ( i == 0 )
                cantBeZeroChar[c-'A'] = true;
        }
    }

    vector<Node> sortedWeight( MAX_NUMBER+1);
    for ( int i = 0; i <= MAX_NUMBER; i++ ){
        sortedWeight[i] = {i, charWeights[i]};
    }

    sort ( sortedWeight.begin(), sortedWeight.end(), CompareNode );

    {
        Node n = sortedWeight[9];
        if ( cantBeZeroChar[n.c] == true ){
            int trgIdx = 8;
            Node trg;
            while ( trgIdx >= 0 ){
                trg = sortedWeight[trgIdx];
                if ( cantBeZeroChar[trg.c] == false ){
                    break;
                }
                trgIdx--;
            }

            
            for ( int i = trgIdx; i < 9; i++ ){
                sortedWeight[i] = sortedWeight[i+1];
            }
            sortedWeight[9] = trg;
        }
    }

    vector<int> numberOfChar( MAX_NUMBER+1, 0 );
    {
        int num = 9;
        for ( int i = 0; i <= MAX_NUMBER; i++ ){
            Node node = sortedWeight[i];
            numberOfChar[node.c] = num;
            num--;
        }
    }


    int64_t ans = 0;
    for ( int ni = 0; ni < N; ni++ ){
        string numberString = numbers[ni];

        int64_t number = 0;
        for ( size_t i = 0; i < numberString.size(); i++ ){
            number *= 10;
            number += numberOfChar[numberString[i]-'A'];
        }
        ans += number;
    }
    

    cout << ans;

    return 0;
}
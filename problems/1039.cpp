/* NOTE:
greedy하게 풀려고 하였으나 조건이 너무 많이 붙어 쉽지 않았다.

다시 생각해보니, 숫자 조합이 다시 나타날 수 있기에 (숫자, 변경 횟수)축으로 dp를 만들 수 있다.
이때 숫자를 섞는 경우는 (자릿수)! 만큼 존재하는데, 숫자가 커지면 N보다 오히려 작다.
즉, 7!*K 가 N*K 보다 작기 때문에 맵을 쓰기로 하였다.

또한, 속도를 조금이라도 빠르게 하기 위해서 unordered_map을 사용하려고 계획했다.
그러나 여기서 커스텀 구조체를 사용하려면 매우 복잡해진다.
그나마 간단하게 하려면 map을 쓸 수 있다. 이 부분을 기억하자.
*/
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct NumData{
    string number;
    int countOfChange;
    // NOTE: unorderd_map보다 map에서 커스텀 구조체 쓰기 쉽다.
    // 아래와 같이 비교 연산자만 정의하면 된다.
    bool operator<( const NumData& other ) const 
    {
        if ( countOfChange == other.countOfChange )
            return stoi(number) < stoi(other.number);
        return countOfChange < other.countOfChange;
    }
};

map<NumData, string> dpMemo;

string trg;
int K;

string DFS( const NumData& numData )
{
    if ( dpMemo.find( numData ) != dpMemo.end() )
        return dpMemo[numData];
    if ( numData.countOfChange == K )
        return (dpMemo[numData] = numData.number );

    string rst = "-1";
    for ( size_t i = 0; i < numData.number.size(); i++ ){
        for ( size_t j = i+1; j < numData.number.size(); j++ ){
            if ( i == 0 && numData.number[j] == '0' )
                continue;

            NumData nextData = numData;
            char tmp = numData.number[i];
            nextData.number[i] = numData.number[j];
            nextData.number[j] = tmp;
            nextData.countOfChange++;
            string dfsRst = DFS(nextData);
            rst = stoi(rst) < stoi(dfsRst) ? dfsRst : rst;
        }
    }

    return (dpMemo[numData] = rst );
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> trg >> K;

    NumData startNumData = { trg, 0 };
    cout << DFS( startNumData );

    return 0;
}
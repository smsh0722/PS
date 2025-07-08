/*
NOTE:
DP를 떠올리긴 했으나 다른 방식의 dp였고, 시공간 복잡도상 불가능했다.
막혔을 때는 결국 유치원생처럼 가장 Naive한 방법으로 문제를 해결하고, 
그 사이에 패턴과 규칙을 발견하는게 좋은 것 같다.
*/
#include <iostream>
#include <vector>
using namespace std;

const int64_t MAX_STUDENT = 1000000;

vector<int64_t> table(MAX_STUDENT+1, 0);

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    table[2] = 1;
    table[3] = 2;
    for ( int64_t stu = 4; stu <= MAX_STUDENT; stu++){
        table[stu] = ((table[stu-1] + table[stu-2])*(stu-1)) % 1000000000;
    }

    int trg = 0;
    cin >> trg;
    cout << table[trg];

    return 0;
}
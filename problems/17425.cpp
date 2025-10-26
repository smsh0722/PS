#include <iostream>
#include <vector>
using namespace std;

/*
N=10
1:  1,2,3,4,5,6,7,8,9,10
1:  1
2:  1,2
3:  1,  3
4:  1,2,  4
5:  1,      5
6:  1,2,3,    6
7:  1,          7
8:  1,2,  4,      8
9:  1,  3,          9
10: 1,2,    5,        10
10,10,9,8,10,6,7,8,9,10

NOTE:
처음 든 생각은,
1~N를 각각 약수를 새로 구하는 것이다.
이렇게 풀면 O(N^2)이 걸린다.

어떻게 하면 더 빠르게 풀 수 있을까?

아이디어)
1~N을 약수로 가지는 수들을 찾아가면 더 빠르게 풀 수 있다.
N/1 + N/2 + N/3 + N/4 + ... + N/N 이므로
O(NlogN)이 걸린다. 

이 문제는 아이디어 떠올리기, 시간복잡도 분석을 못했다.
조화급수의 시간복잡도를 알아두자.
*/

const int MAX_N = 1000000;
int T;

int N;

vector<int64_t> fnTable(MAX_N+1, 1);
vector<int64_t> gnTalbe(MAX_N+1, 0);

int main(void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    for ( int i = 2; i <= MAX_N; i++ ){
        int num = i;
        while ( num <= MAX_N ){
            fnTable[num] += i;
            num += i;
        }
    }

    for ( int i = 1; i <= MAX_N; i++ ){
        gnTalbe[i] = fnTable[i] + gnTalbe[i-1];
    }

    cin >> T;
    for ( int ti = 0; ti < T; ti++ ){
        cin >> N;
        cout << gnTalbe[N] << "\n";
    }

    return 0;
}
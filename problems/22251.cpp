/* NOTE:
처음에 subproblem이 반복되어 dp를 생각했다. 그러나, dp로 하려면 3축이 필요하다. 
또한 무엇보다도, bruteforce 시에 case가 10^6밖에 안 되므로 사실 dp를 할 이유도 없다.
항상 시작은 Brute force로 가능한지 파악. 불가능 -> Naive 손풀이-> 패턴, 특징 찾기 순서로 문제 풀자.

이진수를 char에 넣고 싶으면, 0b~형식으로 넣자. (16진수: 0x~)

*/
#include <iostream>
#include <vector>
using namespace std;

const int MAX_K = 6;
const int MAX_P = 42;

const char digits[10] = { 0b01110111, 0b00000011, 0b00111110, 0b00011111, 0b01001011,
                    0b01011101, 0b01111101, 0b00010011, 0b01111111, 0b01011111 };
int N, K, P, X;

vector<int> limitNum;
vector<int> inputNum;
vector<int> caseNum;

int GetP( int a, int b )
{
    char aBit = digits[a];
    char bBit = digits[b];
    int sum = 0;
    char bit = aBit ^ bBit;
    while ( bit > 0 ){
        sum += bit & 1;
        bit >>= 1;
    }
    return sum;
}

int CalculateCaseRecursive( int i, bool bTight, int remainP )
{
    if ( i == K ){
        bool bZero = true;
        for ( size_t i = 0; i < caseNum.size(); i++ ){
            if ( caseNum[i] != 0 ){
                bZero = false;
                break;
            }
        }
        if ( bZero == true )
            return 0;
        return remainP == P ? 0 : 1; 
    }

    int sum = 0;
    for ( int n = 0; n <= 9; n++ ){
        if ( bTight == true && limitNum[i] < n )
            break;

        int p = GetP( n, inputNum[i] );
        
        printf("i: %d, btight: %d, reaminP: %d, n: %d, p: %d\n", i, bTight, remainP, n, p );//Debug

        if ( remainP < p )
            continue;

        caseNum[i] = n;
        if ( bTight == true && limitNum[i] == n ){
            sum += CalculateCaseRecursive( i+1, true, remainP - p );
        }   
        else {
            sum += CalculateCaseRecursive( i+1, false, remainP - p );
        }     
        caseNum[i] = 0;
    }

    return sum;
}

void BuildDigitVec( vector<int>& v, int x )
{
    int i = 1;
    while ( K - i >= 0 ){
        v[K-i] = x % 10;
        x /= 10;
        i++;
    }
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K >> P >> X;
    
    inputNum.resize(K, 0);
    limitNum.resize(K, 0);
    caseNum.resize(K, 0);
    BuildDigitVec( inputNum, X );
    BuildDigitVec( limitNum, N );

    cout << CalculateCaseRecursive(0, true, P);

    return 0;
}
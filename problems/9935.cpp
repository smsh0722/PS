/* NOTE:
아이디어 떠올리질 못했다. stack 사용이 핵심이다.

stack에 너무 잦은 pop push가 반복적으로 일어나는 경우 시간에 영향을 줄 수 있다.
vector와 right idx 사용하는 것이 시간 단축에 도움이 된다.

vec to string 문법 알고 있자.
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_STRING = 1000000;
vector<char> rst(MAX_STRING, '\0');

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s;
    string bomb;
    cin >> s;
    cin >> bomb;

    int ri = -1;
    for ( size_t si = 0; si < s.size(); si++ ){
        ri++;
        rst[ri] = s[si];

        int bi = bomb.size()-1;
        if ( ri >= 0 && bomb[bi] == rst[ri] ){
            size_t l = 1;
            bool bBomb = true;
            while ( l < bomb.size() ){
                if ( ri - l < 0 ){
                    bBomb = false;
                    break;
                }
                
                if ( bomb[bi-l] != rst[ri-l] ){
                    bBomb = false;
                    break;
                }
                l++;
            }
            if (bBomb == true ){
                ri = ri - l;
                rst[ri+1] = '\0';
                continue;
            }
        }
    } 

    if ( ri < 0 )
        cout << "FRULA";
    else {
        string a (rst.begin(), rst.begin() + ri + 1); // NOTE: vector to string
        cout << a;
    }

    return 0;
}
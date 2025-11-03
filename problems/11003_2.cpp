/* NOTE:
monotonic stack 개념을 활용하면서
앞뒤로 접근 가능한 deque로 풀 수 있다.
*/
#include <iostream>
#include <deque>
using namespace std;

struct AscendingStack{
    int val;
    int idx;
};

// # of elements
int N;
// Len of range
int L;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> L;

    deque<AscendingStack> ascStack;
    for ( int ni = 0; ni < N; ni++ ){
        int val;
        cin >> val;

        while ( ascStack.empty() == false ){
            if ( ascStack.back().val < val )
                break;
            ascStack.pop_back();
        }
        ascStack.push_back({val,ni});

        while ( ascStack.empty() == false ){
            if ( ni - ascStack.front().idx < L )
                break;
            ascStack.pop_front();
        }

        cout << ascStack.front().val << " ";
    }

    return 0;
}
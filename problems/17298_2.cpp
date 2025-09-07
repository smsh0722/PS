/* sol) stack(monotonic stack)
refer: https://www.geeksforgeeks.org/dsa/introduction-to-monotonic-stack-2/
각 원소는 stack에서 최대 한번 push, 최대 한번 pop 된다.
따라서 Time Complexity는 O(N)이 된다.
*/
#include <iostream>
#include <vector>
using namespace std;

struct MyStack{
    int size = 0;
    vector<int> stack;
};

int N;
vector<int> sequence;
vector<int> answers;
// min stack
MyStack myStack;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    sequence.resize(N, 0);
    answers.resize(N,-1);
    myStack.stack.resize(N,-1);
    for ( int i = 0; i < N; i++ )
        cin >> sequence[i];
    
    for ( int i = N - 1; i >= 0; i-- ){
        int num = sequence[i];
        int ans = -1;
        for ( ; myStack.size > 0; myStack.size-- ){
            if ( num < myStack.stack[myStack.size-1] ){
                ans = myStack.stack[myStack.size-1];
                break;
            }
        }
        myStack.stack[myStack.size++] = num;
        answers[i] = ans;
    }

    for ( int i = 0; i < N; i++ )
        cout << answers[i] << " ";

    return 0;
}
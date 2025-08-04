#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Value{
    bool bIsNum;
    int val;
};

const int MAX_LENGTH = 30;

vector<Value> valueStack(MAX_LENGTH, {false, 0});
int stackSize = 0;
string s;

int Calculate( char c )
{
    bool bIsDone = false;
    char trg = c == ']' ? '[' : '(';
    int sum = 0;
    for ( int i = stackSize-1; i >= 0; i-- ){
        if ( valueStack[i].bIsNum == true ){
            sum += valueStack[i].val;
        }
        else {
            if ( valueStack[i].val != trg ){
                break;
            }

            sum = sum == 0 ? 1 : sum;
            if ( c == ']' ){
                sum *= 3;
            }
            else {
                sum *= 2;
            }
            stackSize = i;
            bIsDone = true;
            break;
        }
    }
    if ( bIsDone == true )
        return sum;
    else 
        return 0;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> s;

    for ( auto c : s ){
        if ( c == ']' || c == ')'){
            int rst = Calculate(c);
            if ( rst == 0 ){
                cout << 0;
                return 0;
            }
            else {
                valueStack[stackSize++] = {true, rst };
            }
        }
        else {
            valueStack[stackSize++] = {false, c};
        }
    }

    int ans = 0;
    for ( int i = 0; i < stackSize; i++ ){
        if ( valueStack[i].bIsNum == false ){
            cout << 0;
            return 0;
        }
        else {
            ans += valueStack[i].val;
        }
    }
    cout << ans;

    return 0;
}
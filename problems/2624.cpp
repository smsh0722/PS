#include <iostream>
#include <vector>
using namespace std;

/*
T: 지폐 금액
k: 동전 종류의 수
*/
int T, k;

int main(void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> T >> k;

    /*
    * 0 1 2 . . . k
    0
    1
    2
    .
    .
    T
    */
    vector<vector<int>> dpTable(T+1, vector<int>(k, 0));
    vector<vector<int>> moneyTable(k, vector<int>(2)); //[0]: money,[1]: numOfMoney
    for ( int i = 0; i < k; i++ )
        cin >> moneyTable[i][0] >> moneyTable[i][1];
    
    for ( int c = 0; c < k; c++ )
        dpTable[0][c] = 1;
    
    { // c == 0
        int c = 0;
        int money = moneyTable[0][0];
        int numOfMoney = moneyTable[0][1];
        for ( int r = 1; r <= T; r++ ){
            if ( r % money == 0 && (r/money) <= numOfMoney ) {
                dpTable[r][c] = 1;
            }
        }
    }
    for ( int c = 1; c < k; c++ ){
        int money = moneyTable[c][0];
        int numOfMoney = moneyTable[c][1];

        for ( int r = 1; r <= T; r++ ){
            int caseMax = numOfMoney > (r/money) ? r/money : numOfMoney;
            for ( int caseNum = 0; caseNum <= caseMax; caseNum++ ){
                dpTable[r][c] += dpTable[r-caseNum*money][c-1];
            }
        }
    }

    cout << dpTable[T][k-1];
}
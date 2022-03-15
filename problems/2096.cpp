/* smsh0722
 * 2096
 * 내려가기
 * */
#include <iostream>
using namespace std;

int find_Max( int* dp, int cl, int cr );
int find_Min( int* dp, int cl, int cr );

int main( void )
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    
    int N;
    cin >> N;

    int val;

    int dp_Max[2][3];
    int dp_Min[2][3];
    for ( int i = 0; i < 3; i++ ){
        cin >> val;
        dp_Max[0][i] = val;
        dp_Min[0][i] = val;
    }

    int prevR, curR;
    for ( int i = 2; i <= N; i++ ){
        prevR = i & 1;
        curR = prevR ^ 1; // (1, 0 ) or (0, 1)
        
        cin >> val;
        dp_Max[curR][0] = val + find_Max( dp_Max[prevR], 0, 1 );
        dp_Min[curR][0] = val + find_Min( dp_Min[prevR], 0, 1 );

        cin >> val;
        dp_Max[curR][1] = val + find_Max( dp_Max[prevR], 0, 2 ); 
        dp_Min[curR][1] = val + find_Min( dp_Min[prevR], 0, 2 ); 

        cin >> val;
        dp_Max[curR][2] = val + find_Max( dp_Max[prevR], 1, 2 );
        dp_Min[curR][2] = val + find_Min( dp_Min[prevR], 1, 2 );
    }
    
    cout << find_Max( dp_Max[curR], 0, 2 ) << " " << find_Min( dp_Min[curR], 0, 2 );

    return 0;
}

int find_Max( int* dp, int cl, int cr )
{
    int max = -1;
    for ( int i = cl; i <= cr; i++ )
        max = max < dp[i] ? dp[i] : max;
    return max;
}
int find_Min( int* dp, int cl, int cr )
{
    int min = 900001; // 900,001
    for ( int i = cl; i <= cr; i++ )
        min = min > dp[i] ? dp[i] : min;
    return min;
}
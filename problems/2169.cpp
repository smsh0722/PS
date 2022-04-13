/* smsh0722
 * 2169
 * 로봇 조종하기
 * */
#include <iostream>
using namespace std;

const int INF_NEGATIVE = (1<<31);

struct dp_data{
    int from_up;
    int from_left;
    int from_right;
    int max;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N, M;
    cin >> N >> M;
    
    int** mars;
    // Input
    mars = new int*[N+1];
    for ( int i = 1; i <= N; i++ ){
        mars[i] = new int[M+1];

        for ( int j = 1; j <= M; j++ )
            cin >> mars[i][j];
    }

    dp_data** dp;
    // Dynamic allocation
    dp = new dp_data*[N+1];
    for ( int r = 0; r <= N; r++ )
        dp[r] = new dp_data[M+1];

    // Init
    for ( int r = 0; r <= N; r++ ){
        dp[r][0] = dp_data{ INF_NEGATIVE, INF_NEGATIVE, INF_NEGATIVE };
    }
    dp[1][1].max = mars[1][1];
    for ( int c = 2; c <= M; c++ )
        dp[1][c].max = dp[1][c-1].max + mars[1][c];

    // Fill dp
    for ( int r = 2; r <= N; r++ ){
        // Fill .from_up
        for ( int c = 1; c <= M; c++ )
            dp[r][c].from_up = dp[r-1][c].max + mars[r][c];
        // Fill .from_left
        dp[r][1].from_left = INF_NEGATIVE;
        for ( int c = 2; c <= M; c++ ){
            dp[r][c].from_left = dp[r][c-1].from_left > dp[r][c-1].from_up ? 
                                 dp[r][c-1].from_left : dp[r][c-1].from_up;
            dp[r][c].from_left += mars[r][c];
        }
        // Fill .from_right
        dp[r][M].from_right = INF_NEGATIVE;
        for ( int c = M-1; c >= 1; c-- ){
            dp[r][c].from_right = dp[r][c+1].from_right > dp[r][c+1].from_up ?
                                    dp[r][c+1].from_right : dp[r][c+1].from_up;
            dp[r][c].from_right += mars[r][c];
        }
        // Fill .max
        for ( int c = 1; c <= M; c++ ){
            dp[r][c].max = dp[r][c].from_up;
            dp[r][c].max = dp[r][c].max > dp[r][c].from_left ?
                            dp[r][c].max : dp[r][c].from_left;
            dp[r][c].max = dp[r][c].max > dp[r][c].from_right ?
                            dp[r][c].max : dp[r][c].from_right;
        }
    }

    // Debug
    /*
    for ( int r = 2; r <= N; r++ ){
        for ( int c = 1; c <= M; c++ ){
            dp_data curP = dp[r][c];
            cout << "[" << curP.from_up << " "
                << curP.from_left << " "
                << curP.from_right << " "
                << curP.max << "] ";
        } cout << "\n";
    }*/
    // Answer
    cout << dp[N][M].max;

    return 0;
}
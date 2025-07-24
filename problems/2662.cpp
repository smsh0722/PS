#include <iostream>
#include <vector>
using namespace std;

struct InvestData{
    int sumProfit;
    vector<int> companyList;
};

const int MAX_N = 300;
const int MAX_M = 20;

int N; // budget
int M; // num of companies

// [budget][company]
vector<vector<InvestData>> dpTable(MAX_N+1
    , vector<InvestData>(MAX_M+1, {0, vector<int>(MAX_M+1, 0)}) );

// [budget][company] : profit
vector<vector<int>> investList( MAX_N+1, vector<int>(MAX_M+1, 0 ) );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;

    for ( int n = 1; n <= N; n++ ){ // budget
        int idx;
        cin >> idx;
        for ( int m = 1; m <= M; m++ ){ // company
            cin >> investList[n][m];
        }
    }

    for ( int n = 1; n <= N; n++ ){ // budget
        for ( int m = 1; m <= M; m++ ){ // company
            int max = 0;
            for ( int invest = 0; invest <= n; invest++ ){
                int newProfit = dpTable[n-invest][m-1].sumProfit + investList[invest][m];
                printf("b[%d], cp[%d], invest[%d], newprofit: %d\n", n, m, invest, newProfit); // Debug
                if ( max < newProfit ){
                    printf("renew max!\n"); // Debug
                    dpTable[n][m] = dpTable[n-invest][m-1];
                    dpTable[n][m].sumProfit = newProfit;
                    dpTable[n][m].companyList[m] = invest;
                    max = newProfit;
                }
            }
        }
    }

    for ( int r = 0; r <= N; r++ ){ // Debug
        for ( int c = 0; c<=M; c++ ){
            cout << dpTable[r][c].sumProfit << " ";
        }
        cout << "\n";
    }

    cout << dpTable[N][M].sumProfit << "\n";
    for( int i = 1; i <= M; i++ ){
        cout << dpTable[N][M].companyList[i] << " ";
    }

    return 0;
}
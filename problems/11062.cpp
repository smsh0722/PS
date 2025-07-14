#include <iostream>
#include <vector>
using namespace std;

struct Score{
    int a; // 근우
    int b; // 명우
};

int T;
int N;

vector<int> cards;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    for ( int t = 1; t <= T; t++ ){
        cin >> N;

        // Input cards
        cards.resize(N, 0);
        for ( int i = 0; i < N; i++ )
            cin >> cards[i];

        // Tabulation
        bool lastA = N % 2 == 1;
        vector<vector<Score>> table (N, vector<Score>(N, {0,0} ) );
        for ( int l = 0; l < N; l++ ){
            int r = l;
            if ( lastA == true ){
                table[l][r].a = cards[l];
            }
            else {
                table[l][r].b = cards[l];
            }
        }
        for ( int length = 1; length < N; length++ ){
            for ( int l = 0; l < N; l++ ){
                int r = l + length;
                if ( r >= N )
                    continue;
                bool bIsA = (N - (r-l+1) ) % 2 == 0;
                if ( bIsA == true ){
                    int caseR = table[l][r-1].a + cards[r];
                    int caseL = table[l+1][r].a + cards[l];
                    if ( caseR < caseL ){
                        table[l][r].a = caseL;
                        table[l][r].b = table[l+1][r].b;
                    }
                    else {
                        table[l][r].a = caseR;
                        table[l][r].b = table[l][r-1].b;
                    }
                }
                else {
                    int caseR = table[l][r-1].b + cards[r];
                    int caseL = table[l+1][r].b + cards[l];
                    if ( caseR < caseL ){
                        table[l][r].b = caseL;
                        table[l][r].a = table[l+1][r].a;
                    }
                    else {
                        table[l][r].b = caseR;
                        table[l][r].a = table[l][r-1].a;
                    }
                }
            }
        }
        
        cout << table[0][N-1].a << "\n";
    }   


    return 0;
}
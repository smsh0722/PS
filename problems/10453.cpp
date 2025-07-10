#include <iostream>
#include <vector>
#include <string>
using namespace std;

int T;

int main(void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    for ( int t = 0; t < T; t++ ){
        string A, B;
        cin >> A >> B;
        if ( A.length() != B.length() )
            cout << -1 << "\n";
        
        vector<int> apos;
        vector<int> bpos;
        for ( size_t i = 0; i < A.length(); i++ ){
            if ( A[i] == 'b' )
                apos.push_back(i);
            if ( B[i] == 'b' )
                bpos.push_back(i);
        }

        int64_t sum = 0;
        for ( size_t i = 0; i < apos.size(); i++ ){
            sum += int64_t(abs(apos[i] - bpos[i]));
        }
        cout << sum << "\n";
    }
    
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int T;

const vector<vector<int>> options = 
{
    {},
    {},
    {1},
    {7},
    {4},
    {2, 3, 5},
    {0, 6, 9},
    {8},
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    for ( int ti = 0; ti < T; ti++ ){
        int n;
        cin >> n;

        string minStr = "";
        string maxStr = "";

        // Find Min num
        int leftN = n;
        while ( leftN > 0 ){ // NOTE: 까다로움. 연습
            int minL = 100;
            int minNum = 10;
            int minN = leftN;
            for ( int match = 7; match >= 2; match-- ){
                int nextN = leftN - match;
                if ( nextN < 0 || nextN == 1){
                    continue;
                }
                if ( (int)ceil(nextN/double(7)) > minL ){ // NOTE: double 안 해주면 원하는 그림 안 나옴
                    continue;
                }
                for ( size_t i = 0; i < options[match].size(); i++ ){
                    int num = options[match][i];
                    if ( minStr == "" && num == 0 )
                        continue;
                    
                    if ( minNum > num ){
                        minNum = num;
                        minN = nextN;
                        minL = ceil(nextN/double(7));
                        break;
                    }
                }
            }

            minStr += char(minNum+int('0'));
            leftN = minN;
        }

        // Find Max num
        {
            int leftN = n;
            if ( n % 2 != 0 ) {
                maxStr = '7';
                leftN = leftN - 3;
            }

            for ( int i = leftN / 2; i > 0; i-- )
                maxStr += '1';
        }

        cout << minStr << " " << maxStr << "\n";
    }

    return 0;
}
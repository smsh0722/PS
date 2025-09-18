#include <iostream>
#include <vector>
using namespace std;

int T;
int n;
//                           0, 1, 2, 3, 4, 5, 6, 7, 8, 9
const int matchesOfNum[] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };
vector<vector<string>> dpMemo(2, vector<string>(101, "") );

string FindMin( bool bFirst, int leftN )
{
    if ( leftN == 0 )
        return "";
    if ( dpMemo[int(bFirst)][leftN] != "" )
        return dpMemo[int(bFirst)][leftN];
    
    string ans = string(101, '9' );
    for ( int num = 0; num <= 9; num++ ){
        if ( (bFirst==true)&&(num==0) )
            continue;
        
        int nextLeftNum = leftN - matchesOfNum[num];
        if ( nextLeftNum < 0 || nextLeftNum == 1 )
            continue;
        
        string tmp = char(num+'0') + FindMin( false, nextLeftNum );
        // cout << "leftN: " << leftN << " num: " << num << " ans: " << ans << " tmp: " << tmp << endl;
        if ( ans.length() > tmp.length() ){
            ans = tmp;
        }
        else if ( ans.length() == tmp.length() ){
            bool bIsTmpSmall = true;
            for ( size_t i = 0; i < ans.length(); i++ ){
                if ( ans[i] < tmp[i] ){
                    bIsTmpSmall = false;
                    break;
                }
                else if ( ans[i] > tmp[i] ){
                    bIsTmpSmall = true;
                    break;
                }
            }
            if ( bIsTmpSmall ){
                ans = tmp;
            }
        }
    }

    return dpMemo[int(bFirst)][leftN] = ans;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
     
    cin >> T;
    for ( int ti = 0; ti < T; ti++ ){
        cin >> n;
        
        string minStr = "";
        string maxStr = "";

        // Find Min
        minStr = FindMin( true, n);

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
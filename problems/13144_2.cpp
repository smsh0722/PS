/*
two pointer 사용.
l, r 조절 연습!
*/
#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> seq;
vector<bool> bAppear;

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    seq.resize(N, 0);
    bAppear.resize(N+1, false );

    for ( int i = 0; i < N; i++ ){
        cin >> seq[i];
    }

    int64_t rst = 0;
    {
        int l = 0;
        int r = 0;
        while ( l < N ) {
            if ( r < N ){ // r <= N-1
                if ( bAppear[seq[r]] == true ){
                    rst += r - l;
                    bAppear[seq[l]] = false;
                    l++;
                }
                else {
                    bAppear[seq[r]] = true;
                    r++;
                }
            }
            else {
                rst += r - l;
                bAppear[seq[l]] = false;
                l++;
            }
        }
    }
    cout << rst;

    return 0;
}
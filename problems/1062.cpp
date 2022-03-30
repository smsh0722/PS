/* smsh0722
 * 1062
 * 가르침
 * */
#include <iostream>
#include <cstring>
using namespace std;

int N; // # of words, 0 < N <= 50
int K; // # of alphabets, 0 <= K <= 26

int solve( int* words_flag, int baseFlags, int count, int idx, int flags );
int getNumOfavailable( int* words_flags, int flags );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    
    int* words_flags = new int[N];
    {
        memset( words_flags, 0, sizeof(int)*N );

        char* curWord = new char[16];
        for ( int i = 0; i < N; i++ ){            
            cin >> curWord;
            for ( int idx = 0; idx < strlen(curWord); idx++ ){
                int alphaIdx = curWord[idx] - 'a'; // 0 ~ 25 : a ~ z
                words_flags[i] |= (1<<alphaIdx);
            }
        }
        delete[] curWord;
    }

    if ( K < 5 ){
        cout << 0;
        return 0;
    }

    int baseFlags = 0;
    {
        baseFlags |= 1<<('a' - 'a');
        baseFlags |= 1<<('n' - 'a');
        baseFlags |= 1<<('t' - 'a');
        baseFlags |= 1<<('c' - 'a');
        baseFlags |= 1<<('i' - 'a');
    }
    cout << solve( words_flags, baseFlags, 0, 0, 0 );

    return 0;
}

int solve( int* words_flag, int baseFlags, int count, int idx, int flags )
{
    // Case X
    if ( count == K )
        return getNumOfavailable( words_flag, flags );
     
    int rst = 0;
    
    // recursive find
    if ( idx <= 25 ){
        int curOn = solve( words_flag, baseFlags, count + 1, idx + 1, flags|(1<<idx) );

        int curOff = 0;
        if ( (baseFlags&(1<<idx)) == 0 )
            curOff = solve( words_flag, baseFlags, count, idx + 1, flags );

        rst = curOn < curOff ? curOff : curOn;
    }

    return rst;
}
int getNumOfavailable( int* words_flags, int flags )
{
    int count = 0;
    for ( int wIdx = 0; wIdx < N; wIdx++ ){
        int or_rst = words_flags[wIdx] | flags;
        count += int( flags == or_rst );
    }

    return count;
}
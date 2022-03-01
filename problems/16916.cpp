/* smsh0722
 * 16916
 * 부분 문자열
 * */
#include <iostream>
#include <cstring>
using namespace std;

const int BUFSIZE = 1000001;

bool KMP( char* txt , char* pat );
int* computeLPS( char* pat );

int main( void )
{
    char* txt = new char[BUFSIZE]; memset( txt, 0, BUFSIZE );
    char* pat = new char[BUFSIZE]; memset( pat, 0, BUFSIZE );
    cin >> txt >> pat;

    cout << KMP( txt, pat );
}

bool KMP( char* txt , char* pat )
{
    // Build LPS
    int* lps = computeLPS( pat );

    // Caculate
    const int TXTSIZE = strlen(txt);
    const int PATSIZE = strlen(pat);

    int txtIdx = 0;
    int patIdx = 0;
    while ( txtIdx < TXTSIZE ){
        while ( txtIdx < TXTSIZE && patIdx < PATSIZE && txt[txtIdx] == pat[patIdx] ){
            patIdx++;
            txtIdx++;
        }

        if ( patIdx == PATSIZE ){
            patIdx = lps[patIdx-1];
            return true;
        }
        else { // patidx < PATSIZE
            if ( patIdx > 0 )
                patIdx = lps[patIdx-1];
            else 
                txtIdx++;
        }
    }

    return false;
}
int* computeLPS( char* pat )
{
    const int SIZE = strlen(pat);
    int* lps = new int[SIZE];
    int len = 0;

    lps[0] = 0;
    int i = 1;
    while ( i < SIZE ){
        if ( pat[i] == pat[len] ){
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if ( len == 0 ){
                lps[i] = 0;
                i++;
            }
            else
                len = lps[len-1];
        }
    }
    return lps;
}
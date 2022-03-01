/* smsh0722
 * 16916
 * 부분 문자열
 * */
#include <iostream>
#include <string>
using namespace std;

bool KMP( string* txt , string* pat );
int* computeLPS( string* pat );

int main( void )
{
    string txt, pat;
    cin >> txt >> pat;

    cout << KMP( &txt, &pat );
}

bool KMP( string* txt , string* pat )
{
    int* lps = computeLPS( pat );
    const int TXTSIZE = txt->length();
    const int PATSIZE = pat->length();

    int txtIdx = 0;
    int patIdx = 0;
    while ( txtIdx < TXTSIZE ){
        while ( txtIdx < TXTSIZE && patIdx < PATSIZE && txt->at(txtIdx) == pat->at(patIdx) ){
            patIdx++;
            txtIdx++;
        }

        if ( patIdx == PATSIZE ){
            patIdx = lps[patIdx-1];
            return true;
        }
        else {
            if ( patIdx > 0 )
                patIdx = lps[patIdx-1];
            else 
                txtIdx++;
        }
    }

    return false;
}

int* computeLPS( string* pat )
{
    const int SIZE = pat->length();
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
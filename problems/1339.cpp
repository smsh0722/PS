/* smsh0722
 * 1339
 * 단어 수학
 * */
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <cstring>
using namespace std;

int my_pow( int a, int b );

int main( void )
{
    int N;
    cin >> N;

    string* words;
    // Input
    {
        words = new string[N];
        for ( int i = 0; i < N; i++ )
            cin >> words[i];
    }
    
    /* Sort alphabet by size */
    priority_queue<pair<int,char>> size2alphabet;
    {
        int* alphabet2size = new int[26];
        memset( alphabet2size, 0, sizeof(int)*26 );

        for ( int i = 0; i < N; i++ ){
            string s = words[i];
            for ( int idx = 0; idx < s.size(); idx++ ){
                int c_idx = s[idx] - 'A';
                alphabet2size[c_idx] += my_pow( 10, s.size()-idx-1 );
            }
        }

        for ( int i = 0; i < 26; i++ ){
            if ( alphabet2size[i] != 0 ){
                int size = alphabet2size[i];
                char c = i + 'A';

                size2alphabet.push( pair<int,char>{ size, c } );
            }
        }
        
        delete[] alphabet2size;
    }
    
    map<char,int> alphabet2num;
    {
        int num = 9;
        while ( size2alphabet.empty() == false ){
            pair<int,char> p = size2alphabet.top();
            size2alphabet.pop();

            char c = p.second;
            alphabet2num[c] = num--;
        }
    }

    int sum = 0;
    {
        int curNum;
        for ( int i = 0; i < N; i++ ){
            curNum = 0;
            string s = words[i];

            for ( int idx = 0; idx < s.size(); idx++ ){
                char c = s[idx];
                int c_num = alphabet2num[c];
                curNum += c_num * my_pow( 10, s.size()-idx-1 );
            }

            sum += curNum;
        }
    }
    cout << sum;

    return 0;
}

int my_pow( int a, int b )
{
    int rst = 1;
    for ( int i = 0; i < b; i++ )
        rst *= a;
    
    return rst;
}
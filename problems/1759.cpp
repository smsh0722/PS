#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
using namespace std;

char aeiou[5] = { 'a', 'e', 'i', 'o', 'u' };

int main ( void )
{
    int l, c; cin >> l >> c; // cCl
    vector<char> chars(c);
    for ( int i = 0; i < c; i++ ){
        cin >> chars[i];
    }
    sort( chars.begin(), chars.end() );

    set<string> dictionary;
    {
        vector<bool> combination( c - l, false );
        combination.insert( combination.end(), l, true );
        do{
            string tmp = "";
            {
                for ( int i = 0; i < c; i++ ){
                    if ( combination[i] == true ){
                        tmp.push_back( chars[i] );
                    }
                }
            }

            int vowelCount = 0;
            {
                for ( int i = 0; i < 5; i++ ){
                    if ( tmp.find( aeiou[i] ) != string::npos ){
                        vowelCount++;
                    }
                }
            }
            
            if ( vowelCount >= 1 && tmp.length() - vowelCount >= 2 ){
                dictionary.insert( tmp );
            }
        } while ( next_permutation( combination.begin(), combination.end() ) );
    }


    for ( set<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++ ){
        cout << *it << "\n";
    }
}
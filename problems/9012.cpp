#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main( void )
{
    string temp;
    int caseNum;
    stack<char> data;

    cin >> caseNum;
    getline( cin, temp );
    for ( int i = 0; i < caseNum; i++ ){
        temp = "";
        getline( cin, temp );

        for ( int i = 0; i < temp.length(); i++ ){
            if( !data.empty() ){
                if ( data.top() == '(' && temp[i] == ')' ){
                    data.pop();
                    continue;
                }
                else
                    data.push( temp[i] );
            }
            else // data.empty() == true
                data.push(temp[i]);
        }

        if ( data.empty() )
            cout << "YES\n";
        else {
            cout << "NO\n";
            while ( !data.empty() )
                data.pop();
        }
    }
    return 0;
}
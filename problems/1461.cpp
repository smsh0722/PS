#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// # of books
int N;
// Capacity
int M;

vector<int> lBooks;
vector<int> rBooks;

bool CompareBooksAsc( const int a, const int b )
{
    return a < b;
}
bool CompareBooksDesc( const int a, const int b )
{
    return a > b;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;

    lBooks.push_back(0);
    rBooks.push_back(0);
    for ( int ni = 0; ni < N; ni++ ){
        int pos;
        cin >> pos;
        if ( pos < 0 )
            lBooks.push_back(pos);
        else 
            rBooks.push_back(pos);
    }
    sort( lBooks.begin(), lBooks.end(), CompareBooksAsc );
    sort( rBooks.begin(), rBooks.end(), CompareBooksDesc );

    int sum = 0;
    for ( size_t i = 0; i < lBooks.size(); ){
        sum -= lBooks[i]*2;
        
        i += M;
    }
    for ( size_t i = 0; i < rBooks.size(); ){
        sum += rBooks[i]*2;

        i += M;
    }

    sum = min( sum + lBooks[0], sum - rBooks[0] );

    cout << sum;

    return 0;
}
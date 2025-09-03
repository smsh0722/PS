#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Num of books
int N;

vector<int> books;
vector<int> lis;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    books.resize(N, 0);
    for ( int i = 0; i < N; i++ )
        cin >> books[i];
    
    lis.push_back(books[0]);
    size_t lisSize = 1;
    for ( size_t i = 1; i < books.size(); i++ ){
        if ( lis[lisSize-1] < books[i] ){
            lis.push_back(books[i]);
            lisSize++;
        }
        else {
            int idx = lower_bound(lis.begin(), lis.end(), books[i] ) - lis.begin();
            lis[idx] = books[i];
        }
    }

    cout << books.size() - lisSize;

    return 0;
}
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>

using namespace std;

int searchTarget( const int n, int loc[], int& pos, int& size )
{
    int dir[4] = { -n, n, -1, 1 };
    int len = 0;
    vector<int> queue[ n * n ];
    queue[0].push_back(pos);
    bool visited[n*n] = { false };
    visited[pos] = true;
    set<int> dst;

    while ( len < n * n ){
        int tmp;
        for ( int idx = 0; idx < queue[len].size(); idx++ ){
            tmp = queue[len].at(idx);
            
            for ( int i = 0; i < 4; i++ ){
                int trg = tmp + dir[i];
                if ( trg < 0 || trg >= n * n ) continue;
                if ( i == 2 && tmp % n == 0 ) continue;
                if ( i == 3 && trg % n == 0 ) continue;
                
                // cout << trg << "] "; // Debug
                
                if ( loc[trg] == 0 || loc[trg] == size ){
                    if ( visited[trg] == false ) queue[len+1].push_back( trg );
                    // cout << "len: " << len+1 << ", " << trg << "A\n"; // Deubg
                }
                else if ( loc[trg] > size ){
                    //cout << "len: " << len+1 << ", " << trg << "B\n"; // Deubg
                }
                else { //loc[trg] < size
                    // cout << "len: " << len+1 << ", " << trg << "C\n"; // Deubg
                    dst.insert(trg);
                }
                visited[ trg ] = true;
            }
        }
        /*
        for ( int i = 0; i < queue[len+1].size();i++ ){
            cout << "queue" << len+1 << ": " << queue[len+1][i] << "\n";
        }// Debug
        */
        if ( dst.size() == 0 ) len++;
        else break;
    }
    if ( dst.size() != 0 ){
        int tmp = *dst.begin();
        /*
        for ( auto i = dst.begin(); i != dst.end(); i++ ){
            cout << *i << " "; // Debug;
        } cout << "\n";
        */
        loc[tmp] = 9;
        loc[pos] = 0;
        pos = tmp;
        return (len + 1);
    }
    return 0;
}

int main( void )
{
    int sum = 0;
    int n;
    cin >> n;
    {
        int loc[n*n] = {0};

        int tmp;
        int pos;
        for ( int r = 0; r < n; r++ ){
            for ( int c = 0; c < n; c++ ){
                cin >> tmp;
                if ( tmp == 9 ) {
                    pos = r * n + c;
                }
                loc[r*n + c] = tmp;
            }
        }
        
        // search
        int size = 2;
        int count = 0;
        while ( true ){
            int time = searchTarget( n, loc, pos, size );
            if ( time == 0 ) break;
            /*
            cout << "Time: " << time << "\n"; // Debug
            for ( int r = 0; r < n; r++ ){
                for ( int c = 0; c < n; c++ ){
                    cout << loc[r*n+c] << " ";
                }
                cout << "\n";
            } // Debug
            */
            sum += time;
            count++;
            if ( count == size ){
                count = 0;
                size++;
            }
        }
    }

    cout << sum;
    return 0;
}
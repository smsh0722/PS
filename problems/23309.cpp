#include <iostream>
#include <vector>
using namespace std;

const int MAX_STATION = 1000000;

struct Station{
    int next = 0;
    int prev = 0;
};

// # of stations
int N;
// # of constructions
int M;

vector<Station> routes(MAX_STATION+1);

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    {
        vector<int> stations(N);
        for ( int ni = 0; ni < N; ni++ ){
            cin >> stations[ni];
        }

        for ( int i = 0; i < N; i++ ){
            int cur = stations[i];
            int next = stations[(i+1)%N];
            int prev = stations[(i-1+N)%N];
            routes[cur].next = next;
            routes[cur].prev = prev;
        }
    }

    for ( int mi = 0; mi < M; mi++ ){
        string opt;
        cin >> opt;
        if ( opt == "BN" ){ // insert b bet a, c
            int a, b, c;
            cin >> a >> b;
            c = routes[a].next;

            cout << c << "\n";
            routes[b].next = c;
            routes[b].prev = a;
            routes[a].next = b;
            routes[c].prev = b;
        }
        else if ( opt == "BP" ){ // insert b bet c, a
            int a, b, c;
            cin >> a >> b;
            c = routes[a].prev;
            
            cout << c << "\n";
            routes[b].prev = c;
            routes[b].next = a;
            routes[a].prev = b;
            routes[c].next = b;
        }
        else if ( opt == "CN" ){ // re-link a, b, c to a, c
            int a, b, c;
            cin >> a;
            b = routes[a].next;
            c = routes[b].next;

            cout << b << "\n";
            routes[a].next = c;
            routes[c].prev = a;
        }
        else { // opt == "CP" re-link c, b, a to c, a
            int a, b, c;
            cin >> a;
            b = routes[a].prev;
            c = routes[b].prev;

            cout << b << "\n";
            routes[a].prev = c;
            routes[c].next = a;
        }
    }

    return 0;
}
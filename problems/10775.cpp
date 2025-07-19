#include <iostream>
#include <vector>
using namespace std;

const int MAX_P = 100000;
const int MAX_G = 100000;

int G;
int P;

vector<int> planes(MAX_P);
vector<int> options(MAX_G+1, 0);

int findRecursive( int a )
{
    return options[a] == a ? a : (options[a] = findRecursive( options[a] ));
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> G >> P;

    for ( int i = 0; i <= G; i++ ){
        options[i] = i;
    }
    for ( int i = 0; i < P; i++ ){
        cin >> planes[i];
    }

    int i = 0;
    for ( i = 0; i < P; i++ ){
        int g = planes[i];
        int option = findRecursive(g);
        //printf("%di, %dg, %doption\n", i, g, option);
        if ( option == 0 )
            break;
        options[g] = option-1;
        options[option] = option -1;
    }

    cout << i;

    return 0;
}

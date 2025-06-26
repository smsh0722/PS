#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct vec2{
    union{
        struct{ int x, y; };
        struct{ int r, c; };
    };
};

vector<vector<char>> table(9, vector<char>(9));
vector<vector<vec2>> numPos(10);

bool HasDupRow( int r );
bool HasDupColumn( int c );
bool HasDupBox( int r, int c );
bool HasDupTable();
bool InsertNumInBox( vector<bool>& rVisited, vector<bool>& cVisited, vec2 p, int num);
inline void PrintTable( );

int main (void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int unsolvedCount = 0;
    for ( int r = 0; r < 9; r++ ){
        string rString;
        cin >> rString;
        for ( int c = 0; c < 9; c++ ){
            table[r][c] = rString.at(c);
            if (table[r][c] == '.' )
                unsolvedCount++;
            else {
                int num = table[r][c] - '0';
                numPos[num].push_back(vec2{r, c});
            }
        }
    }

    if ( HasDupTable( ) ){
        cout << "ERROR" << endl;
        return 0;
    }
    
    while ( unsolvedCount > 0 ){
        bool bAnyChanged = false;
        for ( int n = 1; n<=9 && bAnyChanged == false; n++ ){
            vector<bool> rVisited(9, false);
            vector<bool> cVisited(9, false);
            for ( size_t idx = 0; idx < numPos[n].size(); idx++ ){
                vec2 pos = numPos[n][idx];
                rVisited[pos.r] = true;
                cVisited[pos.c] = true;
            }

            for ( int r = 0; r < 9 && bAnyChanged == false; r += 3 ){
                for ( int c = 0; c < 9 && bAnyChanged==false; c += 3 ){
                    if (InsertNumInBox( rVisited, cVisited, vec2{r, c}, n) == true ){
                        bAnyChanged = true;
                        unsolvedCount--;
                    }
                }
            }
        }
        
        // There is nothing to change
        if  (unsolvedCount > 0 && bAnyChanged == false )
            break;
    }

    PrintTable();
    return 0;
}

bool HasDupRow( int r )
{
    vector<int> numCount(10, 0);
    for ( int c = 0; c <9; c++ ){
        if( table[r][c] == '.')
            continue;
        int num = table[r][c] -'0';
        numCount[num]++;

        if( numCount[num] > 1 )
            return true;
    }
    return false;
}
bool HasDupColumn( int c )
{
    vector<int> numCount(10, 0);
    for ( int r = 0 ; r < 9; r++ ){
        if( table[r][c] == '.')
            continue;
        int num = table[r][c] - '0';
        numCount[num]++;
        if( numCount[num] > 1 )
            return true;
    }
    return false;
}
bool HasDupBox( int r, int c )
{
    if ( r % 3 != 0 || c % 3 != 0 )
        return false;

    vector<int> numCount(10, 0 );
    for ( int i = 0; i < 3; i++ ){
        for ( int j = 0; j < 3; j++ ){
            if( table[r+i][c+j] == '.')
                continue;
            int num = table[r+i][c+j] - '0';
            numCount[num]++;
            if( numCount[num] > 1 )
                return true;
        }
    }

    return false;
}
bool HasDupTable()
{
    for ( int r = 0; r < 9; r++ ){
        if ( HasDupRow(r) )
            return true;
        for ( int c = 0; c < 9; c++ ){
            if ( (r == 0) && HasDupColumn( c ) )
                return true;
            
            if ( (r % 3 == 0) && (c % 3 == 0) && HasDupBox( r, c ) )
                return true;
        }
    }

    return false;
}
bool InsertNumInBox( vector<bool>& rVisited, vector<bool>& cVisited, vec2 p, int num)
{
    int tr, tc = 0;
    int holeCount = 0;
    // Calculate hole count
    for ( int i = 0; i < 3; i++ ){
        for ( int j = 0; j < 3; j++ ){
            if( table[p.r+i][p.c+j] == (num + '0') )
                return false;
            if ( rVisited[p.r+i] )
                continue;
            if ( cVisited[p.c+j] )
                continue;

            if( table[p.r+i][p.c+j] == '.'){
                holeCount++;
                tr = p.r+i;
                tc = p.c+j;
            }
        }
    }

    if ( holeCount == 0 ){
        cout << "ERROR" <<endl;
        exit(0);
    }    
    if ( holeCount == 1 ){
        if ( table[tr][tc] == '.' ){
            table[tr][tc] = num + '0';
            rVisited[tr] = true;
            cVisited[tc] = true;
            numPos[num].push_back(vec2{tr, tc});
            return true;
        }
    }
    return false;
}
inline void PrintTable( )
{
    for ( int r = 0; r < 9; r++ ){
        for ( int c = 0; c < 9; c++ ){
            cout << table[r][c];
        }
        cout << endl;
    }
}

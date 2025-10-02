#include <iostream>
#include <vector>
using namespace std;

// NxN world
int N;
// L of a slope
int L;

vector<vector<int>> world;

inline bool CanDescSlope( const vector<int>& line, int i, const vector<bool>& bExistSlope )
{
    if( line[i] - line[i+1] != 1 )
        return false;

    i++;
    int level = line[i];
    int count = L;
    for ( ; i < N && count > 0; i++ ){
        if ( line[i] == level && bExistSlope[i] == false )
            count--;
        else 
            break;
    }

    if ( count == 0 )
        return true;
    return false;
}

inline bool CanAscSlope( const vector<int>& line, int i, const vector<bool>& bExistSlope )
{
    if( line[i] - line[i+1] != -1 )
        return false;

    int level = line[i];
    int count = L;
    for ( ; i >= 0 && count > 0; i-- ){
        if ( line[i] == level && bExistSlope[i] == false )
            count--;
        else 
            break;
    }

    if ( count == 0 )
        return true;
    return false;
}

inline void SetSlopeDesc( int i, vector<bool>& bExistSlope )
{   
    int count = L;
    for ( ; i < N && count > 0; i++ ){
        bExistSlope[i] = true;
        count--;
    }
}
inline void SetSlopeAsc( int i, vector<bool>& bExistSlope )
{
    int count = L;
    for ( ; i >= 0 && count > 0; i-- ){
        bExistSlope[i] = true;
        count--;
    }
}

bool IsPossibleline( const vector<int>& line )
{
    bool bPossible = true;
    vector<bool> bExistSlope(N, false);
    for ( int i = 0; i < N-1; i++ ){
        if ( line[i] == line[i+1] ) // Same Level
            continue;
        else if ( line[i] > line[i+1] ){ // Desc
            if( CanDescSlope( line, i, bExistSlope) ){
                SetSlopeDesc(i+1, bExistSlope);
                i = i + L-1;
                continue;
            }
        }   
        else { // world[r][c] < world[r][c+1] // Asc
            if ( CanAscSlope( line, i, bExistSlope) ){
                SetSlopeAsc(i, bExistSlope);
                continue;
            }
        }         
        
        bPossible = false;
        break;
    }

    return bPossible;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> L;
    world.resize(N);
    for ( int r = 0; r < N; r++ ){
        world[r].resize(N);
        for( int c = 0; c < N; c++ ){
            cin >> world[r][c];
        }
    }

    int sum = 0;
    // Count
        // Row test
    for ( int r = 0; r < N; r++ ){
        sum += IsPossibleline(world[r]) ? 1 : 0;
        // if ( IsPossibleline(world[r]) ) // DEBUG
        //     cout << "Possible at r: " << r << endl;
    }
        // Col test
    for ( int c = 0; c < N; c++ ){
        vector<int> line(N,0);
        for ( int r = 0; r < N; r++ ){
            line[r] = world[r][c];
        }
        sum += IsPossibleline(line) ? 1 : 0;
        // if ( IsPossibleline(line) )
        //     cout << "Possible at c: " << c << endl;
    }

    cout << sum;

    return 0;
}
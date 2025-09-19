#include <iostream>
#include <vector>
using namespace std;

const int NO_ANS = 1000;

// num of cols
int N;
// num of sticks
int M;
// num of rows;
int H;

int maxPos = 0;

// lines[line#][row#] = to line#
vector<vector<int>> lines;

inline bool IsSolved()
{
    for ( int line = 1; line <= N; line++ ){
        int curLine = line;
        int curRow = 1;
        while ( curRow <= H ){
            curLine = lines[curLine][curRow];
            curRow++;
        }

        if ( curLine != line )
            return false;
    }

    return true;
}

inline bool CanAddAt( int line, int row )
{
    if ( lines[line][row] != line )
        return false;
    if ( lines[line+1][row] != line +1 )
        return false;

    return true;
}

int Backtracking( int count, int pos )
{
    // cout << "count\tpos\n"
    //     << count << "\t" << pos << endl; // DEBUG
    if ( IsSolved() )
        return count;

    if ( count == 3 )
        return NO_ANS;
    
    int ans = NO_ANS;
    // 모든 경우 시도해보기
    while ( pos < maxPos ){
        int line = pos % (N-1) + 1;
        int row = pos / (N-1) + 1;

        // cout << "Try \tline\trow\n\t"
        //     << line << "\t" << row << endl; // DEBUG
        if ( CanAddAt(line, row ) == true ){
            lines[line][row] = line+1;
            lines[line+1][row] = line;
            ans = min( ans, Backtracking( count + 1, pos+1 ) );

            lines[line][row] = line;
            lines[line+1][row] = line+1;
        }

        pos++;
    }

    return ans;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M >> H;
    lines.resize(N+1, vector<int>(H+1, 0) );
    for ( int line = 1; line <= N; line++ ){
        for ( int r = 1; r <= H; r++ ){
            lines[line][r] = line;
        }
    }

    for ( int m = 0; m < M; m++ ){
        int a, b;
        cin >> a >> b;

        lines[b][a] = b + 1;
        lines[b+1][a] = b;
    }

    maxPos = (N-1)*H;
    int ans = Backtracking( 0, 0 );

    if ( ans == NO_ANS )
        cout << -1;
    else 
        cout << ans;

    return 0;
}
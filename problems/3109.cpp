/* smsh0722
 * 3109
 * 빵집
 * */
#include <iostream>
using namespace std;

int N, M;
bool DFS( char** gasMap, int r, int c, int* count );

int main (void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M;

    char** gasMap;
    {
        gasMap = new char*[N];
        for ( int i = 0; i < N; i++ )
            gasMap[i] = new char[M];
        
        for ( int r = 0; r < N; r++ ){
            for (int c = 0; c < M; c++ )
                cin >> gasMap[r][c];
        }
    }

    int count = 0;
    for ( int r = 0; r < N; r++ ){
        if ( gasMap[r][0] == '.' )
            DFS( gasMap, r, 0, &count );
    }
    
    cout << count;

    return 0;
}

bool DFS( char** gasMap, int r, int c, int* count )
{
    gasMap[r][c] = 'x';
    
    if ( c == M - 1){
        *count += 1;
        return true;
    }

    int rst = false;
    for ( int i = -1; i <= 1; i++ ){
        int dstR = r+i;
        int dstC = c+1;
        if ( dstR >= 0 && dstR < N && gasMap[dstR][dstC] == '.' ){
            rst = DFS( gasMap, dstR, dstC, count );
            if ( rst == true )
                break;
        }
    }

    return rst;
}
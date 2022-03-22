/* smsh0722
 * 9466
 * 텀 프로젝트
 * */
#include <iostream>
#include <cstring>
using namespace std;

enum color{
    WHITE = 0,
    GRAY,
    BLACK
};

int DFS( int curStu, int* students, color* visited, int* NumOfMembers );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /* Students Array
     * stu[src] = dst
     * 1~100,000
     * */
    int* students = new int[100001];

    color* visited = new color[100001];

    /* Test Case Size */
    int T;
    cin >> T;

    /* Loop Test tn */
    for ( int tn = 1; tn <= T; tn++ ){
        int N;
        cin >> N;

        int NumOfMembers = 0;
        for ( int sIdx = 1; sIdx <= N; sIdx++ )
            cin >> students[sIdx];

        memset( visited, WHITE, sizeof(color)*100001 );
        
        for ( int sIdx = 1; sIdx <= N; sIdx++ ){
            if ( visited[sIdx] == WHITE )
                DFS( sIdx, students, visited, &NumOfMembers );
        }
        
        cout << N - NumOfMembers << "\n";
    }
}

/* return team number
 * 0 = Not involved
 * 1 ~ N = Starting point(Stu num) of Cycle
 * */
int DFS( int curStu, int* students, color* visited, int* NumOfMembers )
{
    visited[curStu] = GRAY;
    
    int trgStu = students[curStu];
    int teamNum = 0;
    if ( (visited[trgStu] == WHITE) && ( (teamNum = DFS( trgStu, students, visited, NumOfMembers ) ) != 0) ){
        (*NumOfMembers)++;
        visited[curStu] = BLACK;

        return curStu == teamNum ? 0 : teamNum;
    }
    else if ( visited[trgStu] == GRAY ){
        (*NumOfMembers)++;
        visited[curStu] = BLACK;

        return curStu == trgStu? 0 : trgStu;
    }

    visited[curStu] = BLACK;
    return 0;
}
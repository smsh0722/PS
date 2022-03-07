/* smsh0722
 * 7576
 * 토마토
 * */
#include <iostream>
#include <queue>
using namespace std;

struct tomato{
    int r, c; // Row, Column
    int riped_day;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int M; // Column
    int N; // Row
    cin >> M >> N;

    queue<tomato*> Q; // Queue for BFS
    int day = 0;
    int unripe_count = 0; // If final count == 0, then print day. else -1
    int** box = new int*[N]; // NxM
    for ( int i = 0; i < N; i++ ){
        box[i] = new int[M];
        for ( int j = 0; j < M; j++ ){
            cin >> box[i][j];
            switch ( box[i][j] )
            {
                case 0:
                {
                    unripe_count++;
                    break;
                }
                case 1:
                {
                    tomato* newT = new tomato;
                    newT->r = i; newT->c = j;
                    newT->riped_day = 0;
                    Q.push( newT );
                }
            }
        }
    }
    
    while ( unripe_count > 0 && Q.empty() == false ){
        tomato* curT = Q.front(); Q.pop();
        /*
        {   // Debug
            if ( day < curT->riped_day ){ 
                cout << day << endl;
                for ( int i = 0; i < N; i++ ){
                    for ( int j = 0; j < M; j++ ){
                        cout << box[i][j] << " ";
                    }
                    cout << endl;
                }
            }
        }
        */
        day += curT->riped_day - day;
        if ( box[curT->r][curT->c] == 2 ){
            box[curT->r][curT->c] = 1;
            unripe_count--;
        }

        {
            int trg_points[4][2]; // 4x(r,c)
            trg_points[0][0] = curT->r - 1; trg_points[0][1] = curT->c;
            trg_points[1][0] = curT->r + 1; trg_points[1][1] = curT->c; 
            trg_points[2][0] = curT->r;     trg_points[2][1] = curT->c - 1;
            trg_points[3][0] = curT->r;     trg_points[3][1] = curT->c + 1; 
            for ( int i = 0; i < 4; i++ ){
                int trgR = trg_points[i][0];
                int trgC = trg_points[i][1];
                if ( trgR < 0 || trgR >= N )
                    continue;
                if ( trgC < 0 || trgC >= M )
                    continue;
                if ( box[trgR][trgC] == 0 ){
                    tomato* newT = new tomato;
                    newT->r = trgR; newT->c = trgC;
                    newT->riped_day = day + 1;
                    Q.push( newT );
                    box[trgR][trgC] = 2;
                }
            }
        }
        delete curT;
    }

    if ( unripe_count > 0 )
        cout << -1;
    else
        cout << day;

    return 0;
}
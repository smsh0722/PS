/*
행렬 곱의 시작부터 마무리 방향으로 관찰했더니 아이디어가 잘 안 떠올랐다.
마무리 단계부터 생각하니 아이디어가 떠올랐다.
일단, Naive한 방법으로 상황을 적어보고, 시작부터 보는 것 뿐만 아니라, 뒤에서부터도 살펴보자
*/

#include <iostream>
#include <vector>
using namespace std;

struct Vec2{
    int r,c;
};
struct TableData{
    Vec2 size;
    int minNumOfOp;
};

const int MAX_INT = ~(1<<31);

int N;
vector<vector<TableData>> table;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Input
    cin >> N;
    table.resize( N, vector<TableData>(N, TableData{Vec2{0,0},0}));
    for ( int i = 0; i < N; i++ ){
        int r, c;
        cin >> r >> c;
        table[i][i] = TableData{ Vec2{r, c}, 0 };
    }

    // Build table
    for( int loop = 1; loop < N; loop++ ){
        for ( int l = 0; l < N; l++ ){
            int r = l + loop; 
            if ( r >= N )
                continue;
            TableData min = TableData{ Vec2{0,0}, MAX_INT};
            for ( int mid = l; mid < r; mid++ ){
                TableData left = table[l][mid];
                TableData right = table[mid+1][r];
                TableData newD;
                /*
                cout << "l, mid, r" << l << " " << mid << " " << r << endl;
                cout << "left: " << left.size.r << " " << left.size.c << " " << left.minNumOfOp << "\n";
                cout << "right: " << right.size.r << " " << right.size.c << " " << right.minNumOfOp << "\n";
                */
                newD.size.r = left.size.r;
                newD.size.c = right.size.c;
                newD.minNumOfOp = left.minNumOfOp + right.minNumOfOp +
                    (left.size.r * left.size.c * right.size.c);
                if( min.minNumOfOp > newD.minNumOfOp ){
                    min.minNumOfOp = newD.minNumOfOp;
                    min.size = newD.size;
                }
            }
            table[l][r] = min;
        }
    }
/*
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < N; c++ ){
            cout << table[r][c].minNumOfOp << " ";
        } cout << "\n";
    }*/

    // Ans minimun number of operations
    cout << table[0][N-1].minNumOfOp;

    return 0;
}
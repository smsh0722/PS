#include <iostream>
#include <vector>
using namespace std;

const int MAXPLUS1 = 1000 * 1000 + 1;

void BFS( int level, const vector< int[3] >& rgbList, vector< vector<int> >& levelIdxMin, const int N )
{
    for ( level; level < N - 1; level++ ){
        int nextLevel = level + 1;
        vector< vector<int> > dstCaseAB(3);
        {
            for ( int src = 0; src < 3; src++ ){
                for ( int dst = 0; dst < 3; dst++ ){
                    if( src != dst ){
                        dstCaseAB[dst].push_back( levelIdxMin[level][src] + rgbList[nextLevel][dst] );
                    }
                }
            }
        }  
        for ( int i = 0; i < 3; i++ ){
            levelIdxMin[nextLevel][i] = dstCaseAB[i][0] < dstCaseAB[i][1] ? dstCaseAB[i][0] : dstCaseAB[i][1];
        }
    }
}

int main( void )
{
    int n;
    cin >> n;
    vector< int[3] > rgbList;
    {
        rgbList = vector< int[3] >(n);
        for ( int i = 0; i < n; i++ ){
            for ( int rgb = 0; rgb < 3; rgb++ ){
                cin >> rgbList[i][rgb];
            }
        }
    }

    int min = MAXPLUS1;
    {
        vector< vector<int> > levelIdxMin( n, vector<int>(3, MAXPLUS1) );
        {
            for ( int i = 0; i < 3; i++ ){
                levelIdxMin[0][i] = rgbList[0][i];
            }
        }
        BFS( 0, rgbList, levelIdxMin, n );
        for ( int i = 0; i < 3; i++ ){
            min = min > levelIdxMin[n-1][i] ? levelIdxMin[n-1][i] : min;
        }
    }
    cout << min;

    return 0;
}
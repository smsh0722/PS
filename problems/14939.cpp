/* smsh0722
 * 14939
 * 불 끄기
 * */
#include <iostream>
using namespace std;

const int SIZE = 10;

bool test_all_case( bool** bulbs, int flags, int dfs_level, int& count );
bool solve( bool** bulbs, int flags, int& rst );
void push_switch( bool** bulbs, int r, int c );

int main( void )
{
    bool** bulbs;
    {
        bulbs = new bool*[SIZE];
        for ( int i = 0; i < SIZE; i++ )
            bulbs[i] = new bool[SIZE];
        
        char bulb;
        for ( int r = 0; r < SIZE; r++ ){
            for ( int c = 0; c < SIZE; c++ ){
                cin >> bulb;
                bulbs[r][c] = bulb == '#' ? false : true;
            }
        }
    }

    int count = 101;
    if ( test_all_case( bulbs, 0, 0, count ) == true )
        cout << count;
    else 
        cout << -1;

    return 0;
}

bool test_all_case( bool** bulbs, int flags, int dfs_level, int& count )
{
    int is_solvable = false;

    if ( dfs_level == SIZE ){
        int rst = 101;
        if ( solve( bulbs, flags, rst ) == true ){
            count = count < rst ? count : rst;
            return true;
        }
        else 
            return false;
    }

    is_solvable |= test_all_case( bulbs, flags|(1<<dfs_level), dfs_level+1, count );
    is_solvable |= test_all_case( bulbs, flags, dfs_level+1, count );

    return is_solvable;
}
bool solve( bool** bulbs, int flags, int& rst )
{
    int count = 0;

    bool** bulbs_copy;
    {
        bulbs_copy = new bool*[SIZE];
        for ( int i = 0; i < SIZE; i++){
            bulbs_copy[i] = new bool[SIZE];
            for ( int j = 0; j < SIZE; j++ )
                bulbs_copy[i][j] = bulbs[i][j];
        }
    }

    for ( int c = 0; c < SIZE; c++ ){
        if ( (flags & (1<<c) )!= 0 ){
            count++;
            push_switch( bulbs_copy, 0, c );
        }
    }
    for ( int r = 1; r < SIZE; r++ ){
        for ( int c = 0; c < SIZE; c++ ){
            if ( bulbs_copy[r-1][c] == true ){
                count++;
                push_switch( bulbs_copy, r, c );
            }
        }
    }

    rst = count;

    int is_solvable = true;

    for ( int c = 0; c < SIZE; c++ ){
        if ( bulbs_copy[9][c] == true ){
            is_solvable = false;
            break;
        }
    }
    

    for ( int i = 0; i < SIZE; i++ )
        delete[] bulbs_copy[i];
    delete[] bulbs_copy;
    
    return is_solvable;
}
void push_switch( bool** bulbs, int r, int c )
{
    int delta[5][2] = { {0,0},{1,0},{-1,0},{0,1},{0,-1} };
    for ( int i = 0; i < 5; i++ ){
        int trgR = delta[i][0] + r;
        int trgC = delta[i][1] + c;
        if ( trgR < 0 || trgR >= SIZE )
            continue;
        if ( trgC < 0 || trgC >= SIZE )
            continue;
        
        bulbs[trgR][trgC] ^= true;
    }
}
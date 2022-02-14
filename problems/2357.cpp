/* 2357 최솟값과 최댓값
 * Segment Tree
 * smsh0722
 * */
#include <iostream>
#include <cmath>
using namespace std;

const int MAX_VAL = 1000000000 + 1; // 1,000,000,001
const int MIN_VAL = 0;
/* ST[]: Segment Tree
 * ti: tree idx
 * li: left idx(arr)
 * ri: right idx(arr)
 * */
int constructST_Min( int ST[], const int ti, const int li, const int ri, const int arr[] )
{
    /* Base Case*/
    if ( li == ri ){
        ST[ti] = arr[li];
        return ST[ti];
    }
    
    /* Construct */
    {
        int min;

        int left_val, right_val;
        int mid = (li+ri)/2;
        left_val = constructST_Min( ST, ti*2+1, li, mid, arr );
        right_val = constructST_Min( ST, ti*2+2, mid +1 , ri , arr );

        min = left_val < right_val ? left_val : right_val;
        ST[ti] = min;
    }
    
    return ST[ti];
}
int constructST_Max( int ST[], const int ti, const int li, const int ri, const int arr[] )
{
    /* Base Case*/
    if ( li == ri ){
        ST[ti] = arr[li];
        return ST[ti];
    }
    
    /* Construct */
    {
        int max;

        int left_val, right_val;
        int mid = (li+ri)/2;
        left_val = constructST_Max( ST, ti*2+1, li, mid, arr );
        right_val = constructST_Max( ST, ti*2+2, mid +1 , ri , arr );

        max = left_val > right_val ? left_val : right_val;
        ST[ti] = max;
    }
    
    return ST[ti];
}
int getMin( const int ST[], const int ti, const int li, const int ri, const int ql, const int qr )
{
    /* Base Case */
    if ( ql <= li && ri <= qr )
        return ST[ti];
    else if ( qr < li || ri < ql )
        return MAX_VAL;

    /* Cal Min */    
    int min;
    {
        int mid = (li+ri)/2;
        int left_val = getMin( ST, ti*2+1, li, mid, ql ,qr );
        int right_val = getMin( ST, ti*2+2, mid+1, ri, ql, qr );

        min = left_val < right_val ? left_val : right_val;
    }

    return min;
}
int getMax( const int ST[], const int ti, const int li, const int ri, const int ql, const int qr )
{
    /* Base Case */
    if ( ql <= li && ri <= qr )
        return ST[ti];
    else if ( qr < li || ri < ql )
        return MIN_VAL;

    /* Cal Min */    
    int max;
    {
        int mid = (li+ri)/2;
        int left_val = getMax( ST, ti*2+1, li, mid, ql ,qr );
        int right_val = getMax( ST, ti*2+2, mid+1, ri, ql, qr );

        max = left_val > right_val ? left_val : right_val;
    }

    return max;
}
int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N, M; // N: arr size, M: qeury num
    cin >> N >> M;

    int arr[N];
    for ( int i = 0; i < N; i++ )
        cin >> arr[i];
    
    /* Construct Segment Tree */
    int* ST_Min;
    int* ST_Max;
    {
        int h = (int)ceil(log2(N));
        int size = 2*(int)pow(2,h) - 1; 
        ST_Min = new int[size];
        ST_Max = new int[size];
        constructST_Min( ST_Min, 0, 0, N-1, arr );
        constructST_Max( ST_Max, 0, 0, N-1, arr );
    }

    /* Query */
    int ql, qr;
    for ( int i = 0; i < M; i++ ){
        cin >> ql >> qr;
        cout << getMin( ST_Min, 0, 0, N - 1, ql-1, qr-1 );
        cout << " ";
        cout << getMax( ST_Max, 0, 0, N - 1, ql-1, qr-1 ) << "\n";
    }

    delete[] ST_Min;
    delete[] ST_Max;
    return 0;
}
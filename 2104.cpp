/* smsh0722
 * 2104
 * 부분배열 고르기
 * */
#include <iostream> 
using namespace std;

const int64_t INF = (-1)^(int64_t(1)<<63);
int N;

int64_t getArrayMax( int64_t* arr, int l, int r );
int64_t maxOfTree( int64_t a, int64_t b, int64_t c );
int64_t getCrossedMax( int64_t* arr, int l, int mid, int r );

int main( void )
{
    ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL);

    cin >> N;

    int64_t* arr;
    {
        arr = new int64_t[N];
        for ( int i = 0; i < N; i++ )
            cin >> arr[i];
    }

    cout << getArrayMax( arr, 0, N-1 );

    return 0;
}

int64_t getArrayMax( int64_t* arr, int l, int r )
{
    // cout << l << ", " << r << "\n"; // Debug
    if ( l == r )
        return (arr[l] * arr[l]);
    
    int mid = ( r - l ) / 2 + l;
    return maxOfTree( getArrayMax(arr, l, mid ),
                        getArrayMax( arr, mid+1, r), 
                            getCrossedMax( arr, l, mid, r ) );
}
int64_t maxOfTree( int64_t a, int64_t b, int64_t c )
{
    int64_t max = a;
    max = max > b ? max : b;
    max = max > c ? max : c;

    return max;
}
int64_t getCrossedMax( int64_t* arr, int l, int mid, int r )
{
    int64_t max_rst = arr[mid]*arr[mid];
    {
        int64_t sum = arr[mid];
        int64_t min_val = arr[mid];
        int curL = mid, curR = mid;
        while( l < curL || curR < r ){
            int64_t lval = l < curL ? arr[curL-1] : -1;
            int64_t rval = curR < r ? arr[curR+1] : -1;
        
            if ( lval > rval ){
                curL--;
                min_val = min_val < lval ? min_val : lval;
                sum += lval;
            }
            else {
                curR++;
                min_val = min_val < rval ? min_val : rval;
                sum += rval;
            }

            int64_t cur_rst = sum * min_val;
            max_rst = max_rst > cur_rst ? max_rst : cur_rst;
        }
    }
    return max_rst;
}
/* smsh0722
 * 1700
 * 멀티탭 스케줄링
 * */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

const int INF = (-1)^(1<<31);
/* # of hole */
int N;
/* # of act */
int K;

int get_low_status_idx( int* power_strip, queue<int>* acts );
void plug( int* power_strip, int s_idx, int act_num );
bool unplug( int* power_strip, int s_idx );
void print_cur_situation( int* power_strip, int count );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> K;

    queue<int> act_seq;
    queue<int>* acts;
    {
        acts = new queue<int>[K+1];

        int act_num;
        for ( int i = 0; i < K; i++ ){
            cin >> act_num;

            act_seq.push( act_num );
            acts[act_num].push( i );
        }
    }

    int count = 0;
    // Solve
    {
        int* power_strip = new int[N];
        memset( power_strip, 0, sizeof(int)*N );

        for ( int i = 0; i < K; i++ ){
            int act_num = act_seq.front();
            act_seq.pop();

            bool is_already_pluged = false;
            for ( int idx = 0; idx < N; idx++ ){
                if ( power_strip[idx] == act_num ){
                    is_already_pluged = true;
                    break;
                }
            }
        
            if ( is_already_pluged == false ){
                int low_status_idx = get_low_status_idx( power_strip, acts );
                count += unplug( power_strip, low_status_idx ) ? 1 : 0;
                plug( power_strip, low_status_idx, act_num );
            }

            acts[act_num].pop();

            print_cur_situation( power_strip, count ); // Deubg
        }

        delete[] power_strip;
    }

    cout << count;

    return 0;
}

int get_low_status_idx( int* power_strip, queue<int>* acts )
{
    int trg = -1;
    int max_order_num = -1;
    for ( int s_idx = 0; s_idx < N; s_idx++ ){
        int act_num = power_strip[s_idx];
        if ( act_num == 0 ){
            trg = s_idx;
            return trg;
        }

        int cur_order_num = acts[act_num].empty() == true ? INF : acts[act_num].front();
        if ( max_order_num < cur_order_num ){
            max_order_num = cur_order_num;
            trg = s_idx;
        }
    }

    return trg;
}
void plug( int* power_strip, int s_idx, int act_num )
{
    power_strip[s_idx] = act_num;
}
bool unplug( int* power_strip, int s_idx )
{
    if ( power_strip[s_idx] != 0 ){
        power_strip[s_idx] = 0;
        return true;
    }
    else // power_strip[s_idx] == 0
        return false;
}
void print_cur_situation( int* power_strip, int count )
{
    for ( int idx = 0; idx < N; idx++ ){
        cout << power_strip[idx] << " ";
    } cout << ", " << count << "\n";// Debug
}
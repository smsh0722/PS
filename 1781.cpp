/* smsh0722
 * 1781
 * 컵라면
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct problem{
    int deadline;
    int reward;
};

inline bool DL_Comp( problem& a, problem& b );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;

    vector<problem> problems;
    // Input problems data
    {
        int deadline, reward;
        for ( int i = 0; i < N; i++ ){
            cin >> deadline >> reward;
            problems.push_back( problem{deadline, reward } );
        }

        sort( problems.begin(), problems.end(), DL_Comp );
    }

    int sum = 0;
    // Solve
    {
        priority_queue<int> pq;
        int pIdx = 0;
        int cur_time = problems[pIdx].deadline - 1;
        while ( cur_time >= 0 ){
            // Get problems
            while ( pIdx < N ){
                if ( problems[pIdx].deadline > cur_time ){
                    pq.push( problems[pIdx].reward );
                    pIdx++;
                }
                else
                    break;
            }
            // Select a problem
            if ( pq.empty() == false ){
                sum += pq.top();
                pq.pop();
            }
            // next_Time
            cur_time--;
        }
    }

    cout << sum;
    return 0;
}

inline bool DL_Comp( problem& a, problem& b )
{
    return a.deadline > b.deadline;
}
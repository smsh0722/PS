#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Line{
    int l, r;
};

struct LineCompareLAsc{
    bool operator()( const Line& a, const Line& b)
    {
        if ( a.l == b.l )
            return a.r < b.r; // r 내림차순
        return a.l > b.l; // l 오름차순
    }
};
struct LineCompareRDesc{
    bool operator()( const Line& a, const Line& b)
    {
        if ( a.r == b.r )
            return a.l > b.l; // l 오름차순
        return a.r < b.r; // r 내림차순
    }
};

int M;

priority_queue<Line, vector<Line>, LineCompareLAsc> linesLAsc;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> M;
    int l, r;
    while (true ){
        cin >> l >> r;
        if ( l== 0 && r == 0 )
            break;
        linesLAsc.push(Line{l,r});
    }

    int m = 0;
    int count = 0;
    while ( m < M ){
        priority_queue<Line, vector<Line>, LineCompareRDesc> linesRDesc;
        while ( linesLAsc.empty() == false ){
            Line line = linesLAsc.top();
            if ( m < line.l )
                break;

            linesLAsc.pop();
            linesRDesc.push(line);
        }

        if ( linesRDesc.empty() == true )
            break;

        while ( linesRDesc.empty() == false ){
            Line line = linesRDesc.top();
            linesRDesc.pop();
            if ( line.l <= m && m < line.r ){
                m = line.r;
                count++;
                break;
            }
        }
    }

    if ( m < M )
        cout << 0;
    else // M <= m 
        cout << count;

    return 0;
}
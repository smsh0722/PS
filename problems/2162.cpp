/* smsh0722
 * 2162
 * 선분 그룹
 * */
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

struct Point{
    int x;
    int y;
};
struct Segment{
    Point p;
    Point q;
};

enum orientation{
    COLLINEAR, CLOCK, COUNTERCLOCK
};

void getSets( set<set<int>>& disjoint_sets, queue<set<int>>& sets, Segment* segments, int segIdx );
bool is_crossed( Segment* segments, int segAIdx, int segBIdx );
orientation getOrientation( Point p, Point q, Point r );
bool onSegment(Point p, Point q, Point r);
void union_sets( set<set<int>>& disjoint_sets, queue<set<int>>& sets, int curSeg );
void erase_sets( set<set<int>>& disjoint_sets, set<int>* s_p );

int main( void )
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;

    Segment* segments;
    {
        segments = new Segment[N];
        for ( int i = 0; i < N; i++ ){
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            segments[i] = Segment{ Point{x1,y1}, Point{x2,y2} };
        }
    }

    set<set<int>> disjoint_sets;
    // Solve
    for ( int i = 0; i < N; i++ ){
        queue<set<int>> sets;
        getSets( disjoint_sets, sets, segments, i );
        if ( sets.size() == 0 )
            disjoint_sets.insert( set<int>{i} );
        else 
            union_sets( disjoint_sets, sets, i );
    }

    // Print # of disjoint sets
    cout << disjoint_sets.size() << "\n";
    // Print # of elements in largest set
    int max = 0;
    for ( set<set<int>>::iterator it = disjoint_sets.begin(); it != disjoint_sets.end(); it++ ){
        max = max > (*it).size() ? max : (*it).size();
    }
    cout << max;

    return 0;
}
void getSets( set<set<int>>& disjoint_sets, queue<set<int>>& sets, Segment* segments, int segIdx )
{
    for ( set<set<int>>::iterator s_it = disjoint_sets.begin(); s_it != disjoint_sets.end(); s_it++ ){
        set<int> cur_set = *s_it;

        for ( set<int>::iterator e_it = cur_set.begin(); e_it != cur_set.end(); e_it++ ){
            int cur_elements = *e_it;
            if ( is_crossed( segments, cur_elements, segIdx ) == true ){
                sets.push( cur_set );
                break;
            }
        }
    }
}
bool is_crossed( Segment* segments, int segAIdx, int segBIdx )
{
    Segment s1 = segments[segAIdx];
    Segment s2 = segments[segBIdx];
    orientation o1 = getOrientation( s1.p, s1.q, s2.p );
    orientation o2 = getOrientation( s1.p, s1.q, s2.q );
    orientation o3 = getOrientation( s2.p, s2.q, s1.p );
    orientation o4 = getOrientation( s2.p, s2.q, s1.q );

    if ( o1 != o2 && o3 != o4 )
        return true;
    if ( o1 == 0 && onSegment(s1.p, s2.p, s1.q ) )
        return true;
    if ( o2 == 0 && onSegment(s1.p, s2.q, s1.q ) )
        return true;
    if ( o3 == 0 && onSegment(s2.p, s1.p, s2.q ) )
        return true;
    if ( o4 == 0 && onSegment(s2.p, s1.q, s2.q ) )
        return true;

    return false;
}
orientation getOrientation( Point p, Point q, Point r )
{
    int val = (q.y - p.y)*(r.x - q.x) - (q.x-p.x)*(r.y-q.y);
    if ( val == 0 )
        return COLLINEAR;
    else if ( val > 0 )
        return CLOCK;
    else
        return COUNTERCLOCK;
}
bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;
 
    return false;
}
void union_sets( set<set<int>>& disjoint_sets, queue<set<int>>& sets, int curSeg )
{
    set<int> new_set;
    new_set.insert( curSeg );
    while ( sets.empty() == false ){
        set<int> s_p = sets.front(); 
        sets.pop();

        for ( set<int>::iterator it = s_p.begin(); it != s_p.end(); it++ )
            new_set.insert(*it);
        
        erase_sets( disjoint_sets, &s_p );
    }
    disjoint_sets.insert(new_set);
}
void erase_sets( set<set<int>>& disjoint_sets, set<int>* s_p )
{
    for ( set<set<int>>::iterator s_it = disjoint_sets.begin(); s_it != disjoint_sets.end(); s_it++ ){
        bool flag = true;
        vector<int> sa;
        vector<int> sb;
        for ( set<int>::iterator e_it = s_it->begin(); e_it != s_it->end(); e_it++ )
            sa.push_back(*e_it );
        for ( set<int>::iterator e_it = s_p->begin(); e_it != s_p->end(); e_it++ )
            sb.push_back(*e_it);

        if ( sa.size() == sb.size() ){
            for ( int i = 0; i < sa.size(); i++ )
                flag = sa[i] != sb[i] ? false : flag;
        }
        else 
            flag = false;

        if ( flag == true ){
            disjoint_sets.erase( s_it );
            break;
        }
    }
}
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Building{
    int l, h, r;
};

struct BuildingPQCompare{
    bool operator()( const Building& a, const Building& b )
    {
        if ( a.h == b.h ){
            return a.r < b.r; // r 내림차순
        }
        return a.h < b.h; // 높이 내림차순
    };
};
    
int N;

vector<Building> buildings;
priority_queue<Building, vector<Building>, BuildingPQCompare> pq;

bool BuildingCompare( const Building& a, const Building& b )
{
    if ( a.l == b.l ){
        return a.h > b.h;
    }
    return a.l < b.l;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    buildings.resize(N);
    for ( int i = 0; i < N; i++ ){
        cin >> buildings[i].l >> buildings[i].h >> buildings[i].r;
    }
    sort( buildings.begin(), buildings.end(), BuildingCompare );

    for ( int i = 0; i < N; i++ ){
        // Get New Point
        Building cur = buildings[i];

        // Remove Old Buildings
        Building top;
        while ( pq.empty() == false ){
            top = pq.top();
            if ( cur.l <= top.r )
                break;

            pq.pop();

            Building next = {0, 0, 0};
            while ( pq.empty() == false ){
                if ( top.r < pq.top().r ){
                    next = pq.top();
                    break;
                }
                else 
                    pq.pop();
            }
            cout << top.r << " " << next.h << " ";
        }

        // Process cur Point
        if ( pq.empty() == false ){
            Building top = pq.top();
            if ( top.h < cur.h ){   
                cout << cur.l << " " << cur.h << " ";
            }
        }
        else{
            cout << cur.l << " " << cur.h << " ";
        }

        pq.push(cur);
    }
    // Remove Old Buildings
    Building top;
    while ( pq.empty() == false ){
        top = pq.top();
        pq.pop();

        Building next = {0, 0, 0};
        while ( pq.empty() == false ){
            if ( top.r < pq.top().r ){
                next = pq.top();
                break;
            }
            else 
                pq.pop();
        }
        cout << top.r << " " << next.h << " ";
    }

    return 0;
}
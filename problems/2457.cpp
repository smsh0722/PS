#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Flower{
    int start;
    int end;
    bool operator==( const Flower& other ) const
    {
        return (start == other.start) && (end==other.end);
    }
};

int N;

int days[] = { 0, 31, 28, 31,
                30, 31, 30,
                31, 31, 30,
                31, 30, 31 };

vector<Flower> flowers;

bool FlowerCompare( const Flower& a, const Flower& b )
{
    if ( a.start == b.start )
        return a.end > b.end;
    return a.start < b.start;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    for ( int i = 1; i <= 12; i++ ){
        days[i] += days[i-1];
    };

    cin >> N;
    flowers.resize(N);
    for ( int i = 0; i < N; i++ ){
        int m1, d1, m2, d2;
        cin >> m1 >> d1 >> m2 >> d2;

        flowers[i] = Flower { days[m1-1]+d1, days[m2-1]+d2};
    }
    sort( flowers.begin(), flowers.end(), FlowerCompare );

    int flowerCount = 0;
    Flower pervF = {0,days[2]+1};
    Flower greedyF = pervF;
    for ( int fi = 0; fi < N; fi++ ){
        Flower f = flowers[fi];

        if ( pervF.end >= f.start && greedyF.end < f.end ){
            greedyF = f;
        }   
        else if ( pervF.end < f.start ){
            if ( greedyF.end < f.start ){
                flowerCount = 0;
                break;
            }
            else {
                pervF = greedyF;
                flowerCount++;
                greedyF = f;
            }

        }

        if ( greedyF.end > days[11] ){
            pervF = greedyF;
            flowerCount++;
            break;
        }
    }
    
    if ( pervF.end > days[11] )
        cout << flowerCount;
    else 
        cout << 0;

    return 0;
}
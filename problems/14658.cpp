#include <iostream>
#include <vector>

using namespace std;

/*
world size: NxM
box size: LxL
Num of star : K
*/
int N, M, L, K;

struct vec2{
    int x;
    int y;
};

int CalculateStarsInBox( vector<vec2>& stars, vec2 boxPosLB );

inline int maxAB( int a, int b );
inline int minAB( int a, int b );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> L >> K;

    vector<vec2> stars(K);
    for ( int i = 0; i < K; i++ )
        cin >> stars[i].x >> stars[i].y;

    int max_count = 0;

    for ( int i = 0; i < K; i++ ){
        for ( int j = i; j < K; j++ ){
            int temp_count = 0;
            vec2 boxPos = {0,0};
            vec2 LB = { minAB( stars[i].x, stars[j].x),
                    minAB( stars[i].y, stars[j].y ) };
            vec2 RT = { maxAB(stars[i].x, stars[j].x ),
                maxAB( stars[i].y, stars[j].y ) };

            // Case1
            boxPos.x = LB.x; boxPos.y = LB.y;
            temp_count = CalculateStarsInBox( stars, boxPos );
            max_count = maxAB(max_count, temp_count);
            // Case2
            boxPos.x = LB.x; boxPos.y = RT.y - L;
            temp_count = CalculateStarsInBox( stars, boxPos );
            max_count = maxAB(max_count, temp_count);
            // Case3
            boxPos.x = RT.x - L; boxPos.y = LB.y;
            temp_count = CalculateStarsInBox( stars, boxPos );
            max_count = maxAB(max_count, temp_count);
            // Case4
            boxPos.x = RT.x - L; boxPos.y = RT.y-L;
            temp_count = CalculateStarsInBox( stars, boxPos );
            max_count = maxAB(max_count, temp_count);
        }
    }

    cout << K - max_count << endl;
}

int CalculateStarsInBox( vector<vec2>& stars, vec2 boxPosLB )
{
    if ( boxPosLB.x < 0 )
        boxPosLB.x = 0;
    if ( boxPosLB.x + L > N)
        boxPosLB.x = N - L;
    if  (boxPosLB.y < 0 )
        boxPosLB.y = 0;
    if ( boxPosLB.y + L > M )
        boxPosLB.y = M - L;
    
    vec2 boxPosRT = { boxPosLB.x + L, boxPosLB.y + L };

    int count = 0;
    for ( int i = 0; i < K; i++ ){
        vec2 star = stars[i];

        if ( star.x < boxPosLB.x || boxPosRT.x < star.x )
            continue;
        if ( star.y < boxPosLB.y || boxPosRT.y < star.y )
            continue;
        //cout << "boxLB: " << boxPosLB.x << ", " <<  boxPosLB.y << endl;
        //cout << "star: " << star.x << ", " << star.y << endl;
        count++;
    }

    return count;
}

inline int maxAB( int a, int b )
{
    return a > b ? a: b;
}
inline int minAB( int a, int b )
{
    return a < b ? a : b;
}
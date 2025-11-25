/* NOTE:
아이디어를 떠올리기 어려웠다.

E = (그룹 내의 학생들이 아는 모든 알고리즘의 수 - 그룹 내의 모든 학생들이 아는 알고리즘의 수) * 그룹원의 수
  = (e1 - e2) * e3
여기서 사람이 많아지면
e1은 같거나 커지고
e2는 같거나 작아지고
e3는 커진다
따라서, D 범위 내에서 최대한 사람을 많이 넣어 그룹을 만들며 그 중 최대를 구하면 된다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Student{
    int level;
    int algoBits;
};

// # of students
int N;
// # of algorithms
int K;
// MAX LELEL DIFF
int D;

// students[stu idx]= Student, (stu idx)=[1,N]
vector<Student> students;

// algoCounts[algo idx] = counts, (algo idx)=[1,K]
vector<vector<int>> algoCounts;

// Asc by level
bool CompareStudent( const Student& a, const Student& b )
{
    return a.level < b.level;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K >> D;

    // Input Stu
    students.resize(N+1, {0,0});
    for ( int ni = 1; ni <= N; ni++ ){
        int nAlgo, level;
        cin >> nAlgo >> level;

        int algoBits = 0;
        for ( int i = 0; i < nAlgo; i++ ){
            int algo;
            cin >> algo;
            algoBits |= (1<<algo);
        }

        students[ni] = {level, algoBits};
    }
    sort ( students.begin(), students.end(), CompareStudent );

    // Calculate
    algoCounts.resize( N+1, vector<int>(K+1, 0));
    for ( int ni = 1; ni <= N; ni++ ){
        for ( int ai = 1; ai <= K; ai++ ){
            algoCounts[ni][ai] = algoCounts[ni-1][ai] + int(bool( (1<<ai)&(students[ni].algoBits) ));
        }
    }

    int ans = 0;
    int l = 0;
    int r = 1;
    while ( (l < r)&&(r <= N) ){
        const Student& ls = students[l+1];
        const Student& rs = students[r];

        int levelDiff = rs.level - ls.level;

        if ( levelDiff <= D ){
            // cout << "l: " << l << " r: " << r << endl; // DEBUG
            int e = 0;
            int e1 = 0;
            int e2 = 0;
            int e3 = r - l;
            for ( int ai = 1; ai <= K; ai++ ){
                int count = (algoCounts[r][ai] - algoCounts[l][ai]);
                // cout << "ai: " << ai << " count: " << count << endl; // DEBUG
                if ( count > 0 )
                    e1++;
                if ( count >= e3 )
                    e2++;
            }

            e = (e1-e2)*e3;
            // cout << "e: " << e << "=(" << e1 << "-" << e2 << ")*" <<e3 << endl; // DEBUG
            ans = max(ans, e);
            
            r++;
        }
        else { // levelDiff > D;
            l++;
        }
    }

    cout << ans;
    return 0;
}
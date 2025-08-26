/* NOTE:
사전순 정렬 연습하자. 이 부분에서 틀렸다.
문자열 A, B가 있다고 하자.
1. abc.., abd..와 같이 0..i-1까지 문자가 같다가, i번째에 B 문자가 더 크다면 B는 더 나중에 오는 문자열이다.
2. an, and 는 an이 더 먼저 오는 문자열이다.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_COST = ~(1<<31);

struct Nutrient{
    int p, f, s, v;
    Nutrient operator+(const Nutrient& other ) const 
    {
        return Nutrient{
            p+other.p,
            f+other.f,
            s+other.s,
            v+other.v
        };
    }
};

Nutrient nutrientGoal = { 100, 70, 90, 10 };

// Num of foods
int N;

vector<Nutrient> foods;
vector<int> costs;

vector<int> ansQ;
int ans = MAX_COST;

bool IsPassed( const Nutrient& n )
{
    if ( n.p < nutrientGoal.p )
        return false;
    if ( n.f < nutrientGoal.f )
        return false;
    if ( n.s < nutrientGoal.s )
        return false;
    if ( n.v < nutrientGoal.v )
        return false;
    return true;
}

void GetAnsRecursive( int fi, int cost, vector<int> seq, Nutrient sum )
{
    if ( fi == N){
        if ( IsPassed(sum) == true ){ // Already done
            if ( ans >= cost ){
                ans = cost;
                if ( ansQ.size() == 0 )
                    ansQ = seq;
                else if ( ansQ.size() < seq.size() ){
                    bool bShouldChange = false;
                    for ( size_t i = 0; i < ansQ.size(); i++ ){
                        if ( ansQ[i] < seq[i] ){
                            bShouldChange = false;
                            break;
                        }
                        else if ( ansQ[i] > seq[i] ){
                            bShouldChange = true;
                            break;
                        }
                    }
                    if ( bShouldChange == true ){
                        ansQ = seq;
                    }
                }
                else {
                    bool bShouldChange = true;
                    for ( size_t i = 0; i < seq.size(); i++ ){
                        if ( ansQ[i] < seq[i] ){
                            bShouldChange = false;
                            break;
                        }
                        else if ( ansQ[i] > seq[i] ){
                            bShouldChange = true;
                            break;
                        }
                    }
                    if ( bShouldChange == true ){
                        ansQ = seq;
                    }
                }
            }
        }
        return ;
    }

    // Not include fi
    GetAnsRecursive(fi+1, cost, seq, sum );
    // include fi
    seq.push_back(fi);
    GetAnsRecursive(fi+1, cost+costs[fi], seq, sum+foods[fi] );
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    foods.resize(N);
    costs.resize(N);
    {
        int p, f, s, v, c;
        cin >> p >> f >> s >> v;
        nutrientGoal = {p, f, s, v};
        for ( int i = 0; i < N; i++ ){
            cin >> p >> f >> s >> v >> c;
            foods[i] = Nutrient{p, f, s, v};
            costs[i] = c;
        }
    }

    GetAnsRecursive(0, 0, vector<int>(0), {0,0,0,0} );

    if ( ans == MAX_COST )
        cout << -1;
    else {
        cout << ans << endl;
        for ( size_t i = 0; i < ansQ.size(); i++ )
            cout << ansQ[i] + 1<< " ";
    }
    return 0;
}
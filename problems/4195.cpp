#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int T;
int F;

struct DisjointSet{
    unordered_map<string,string> parents;
    unordered_map<string, int> setSize;
    string FindRecursive( string& s)
    {
        if ( parents.find(s) == parents.end() ){
            parents[s] = s;
            setSize[s] = 1;
            return s;
        }
        else {
            return parents[s] == s ? s : ( parents[s] = FindRecursive(parents[s]));
        }
    };
    string Union( string& a, string& b )
    {
        string pa = FindRecursive(a);
        string pb = FindRecursive(b);
        if ( pa == pb )
            return pa;
        
        if ( setSize[pa] < setSize[pb] ){
            parents[pa] = pb;
            setSize[pb] += setSize[pa];
            return pb;
        }
        else {
            parents[pb] = pa;
            setSize[pa] += setSize[pb];
            return pa;
        }
    };
};


int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    for ( int t = 0; t < T; t++ ){
        // test case(t)
        cin >> F;
        
        DisjointSet ds;
        string a, b;
        for( int f = 0; f < F; f++ ){
            cin >> a >> b;

            string p = ds.Union(a,b);
            cout << ds.setSize[p] << "\n";
        }
    }

    return 0;
}
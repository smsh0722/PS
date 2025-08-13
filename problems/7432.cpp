#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Trie {
    string name;
    map<string, Trie*> childs;
    Trie(){ name = ""; };
    Trie(const string& s ){ name= s;};
};

Trie* root = new Trie();
int N;

void PushTrie( string s )
{
    Trie* trie = root;
    while (true){
        size_t idx = s.find_first_of('\\'); // NOTE: find 실패시 string::npos 반환 아니면 size_t idx 반환

        if ( idx == string::npos){
            if ( trie->childs.find(s) == trie->childs.end() ){
                Trie* newTrie = new Trie(s);
                trie->childs[s] = newTrie;
            }
            break;
        }
        else {
            string p = s.substr(0, idx);
            if ( trie->childs.find(p) == trie->childs.end() ){
                Trie* newTrie = new Trie(p);
                trie->childs[p] = newTrie;
            }
            trie = trie->childs[p];

            s = s.substr(idx+1); // NOTE: .substr(idx) or .substr(idx, len);
        }
    }
}

void PrintTrie( Trie* t, int depth )
{
    if ( t->name != "" ){
        if ( depth > 0 ){
            string indent( depth, ' ' ); // NOTE: sting 반복 
            cout << indent;
        }

        cout << t->name << endl;
    }

    for ( auto ct : t->childs ){
        PrintTrie(ct.second, depth+1);
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    for ( int i = 0; i < N; i++ ){
        string s;
        cin >> s;
        PushTrie(s);
    }

    PrintTrie(root, -1);
    
    return 0;
}
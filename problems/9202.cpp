/* NOTE:
dfs를 하지만 dp는 불가->backtracking
backtracking 시에는 어떻게 시간복잡도 줄일지 고민: 여기서는 trie

trie DS 익숙해지기

new, pointer 익숙해지기
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2& other ) const {
        return {r+other.r, c + other.c};
    };
};

struct Trie{
    Trie* child[26];
    bool bWord;
    Trie(){ memset(child, 0, sizeof(child)), bWord = false; };
};

const vector<Vec2> moves = {
    {-1,-1}, {-1,0}, {-1,1},
    {0,-1}, {0,1},
    {1,-1}, {1,0}, {1,1}
};

const int BOARD_SIZE = 4;

int w; // num of words;
int b; // num of boards;

int score;
string longestWord;
int wordCount;

Trie* rTrie = new Trie();
vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, 'Z'));
vector<vector<bool>> visited(BOARD_SIZE, vector<bool>(BOARD_SIZE,false));

void InsertTrie( string& s )
{
    Trie* trie = rTrie;
    for ( auto c : s ){
        if ( trie->child[c-'A'] == nullptr){
            trie->child[c-'A'] = new Trie;
        }
        trie = trie->child[c-'A'];
    }

    trie->bWord = true;
}

void SolveBoggleRecursive( const Vec2& p, set<string>& wordSet, string& s, Trie* t )
{
    visited[p.r][p.c] = true;
    s += board[p.r][p.c];
    if ( t->bWord == true && wordSet.find(s) == wordSet.end()){
        wordSet.insert(s);
        size_t l = s.length();
        if ( l == 3 || l == 4 )
            score += 1;
        else if ( l == 5 )
            score += 2;
        else if ( l == 6 )
            score += 3;
        else if ( l == 7 )
            score += 5;
        else if ( l == 8 )
            score += 11;

        wordCount++;

        if ( longestWord.length() < l ){
            longestWord = s;
        }
        else if ( longestWord.length() == l && longestWord > s){
            longestWord = s;
        }
    }

    if ( s.length() < 8 ){
        for ( size_t i = 0; i < moves.size(); i++ ){
            Vec2 next = p + moves[i];
            if ( next.r < 0 || next.r >= BOARD_SIZE || next.c < 0 || next.c >= BOARD_SIZE )
                continue;
            if ( visited[next.r][next.c] == true )
                continue;

            Trie* nt = t->child[board[next.r][next.c]-'A'];
            if ( nt != nullptr )
                SolveBoggleRecursive( next, wordSet, s, nt);    
        }
    }

    s.pop_back();
    visited[p.r][p.c] = false;
    return;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> w;
    for ( int i = 0; i < w; i++ ){
        string s;
        cin >> s;
        InsertTrie(s);
    }

    cin >> b;
    for ( int t = 0; t < b; t++ ){
        for ( int r = 0; r < BOARD_SIZE; r++ ){
            for ( int c = 0; c < BOARD_SIZE; c++ ){
                cin >> board[r][c];
            }
        }

        set<string> wordSet;
        score = 0;
        longestWord = "";
        wordCount = 0;
        for ( int r = 0; r < BOARD_SIZE; r++ ){
            for ( int c = 0; c < BOARD_SIZE; c++ ){
                string s = "";
                Trie* t = rTrie->child[board[r][c]-'A'];
                if ( t == nullptr )
                    continue;
                SolveBoggleRecursive( {r,c}, wordSet, s, t);
            }
        }
        cout << score << " " << longestWord << " " << wordCount << "\n";
    }


    return 0;
}
#include <iostream>
#include <string>
#include <set>
using namespace std;

const int CHILD_SIZE = 10; // 0 ~ 9
struct trieNode{
    struct trieNode* children[CHILD_SIZE];
    bool isEnd;
    trieNode()
    {
        isEnd = false;
        for ( int i = 0; i < CHILD_SIZE; i++ ){
            children[i] = nullptr;
        }
    }
};

bool trie( const string& number, trieNode& root );

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t; cin >> t;
    for ( int tIdx = 0; tIdx < t; tIdx++ ){
        int n; cin >> n;
        
        int flag = true;
        {
            set<string> numBook;
            for ( int i = 0; i < n; i++ ){
                string tmp;
                cin >> tmp;
                numBook.insert(tmp);
            }

            trieNode* root = new trieNode;
            for ( set<string>::iterator it = numBook.begin(); it != numBook.end(); it++ ){
                if ( ( flag = trie( *it, *root ) ) == false ){
                    break;
                }
            }
        }

        if ( flag == true ){
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
}

bool trie( const string& number, trieNode& root )
{
    trieNode* nodePtr = &root;
    for ( int i = 0; i < number.length(); i++ ){
        int ithNum = number.at(i) - '0';
        if ( nodePtr->children[ithNum] == nullptr ){
            trieNode* newNode = new trieNode;
            nodePtr->children[ithNum] = newNode;
            nodePtr = newNode;
        }
        else {
            nodePtr = nodePtr->children[ithNum];
            if ( nodePtr->isEnd == true ){
                return false;
            }
        }
        if ( i == number.length() - 1 ){
            nodePtr->isEnd = true;
        }
    }
    return true;
}
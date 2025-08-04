#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Node{
    string s;
    map<string, Node*> child;
    Node() {s = "";};
    Node(string s) { this->s = s; };
};

Node* root = new Node;

int N; // num of data
int K; // num of depth

inline void printDepth( int depth )
{
    for ( int i = 0; i < depth-1; i++ )
        cout << "--";
}
void printAnsRecursive( Node* node, int depth )
{
    if ( depth > 0 ){ // print node excluding root
        printDepth(depth);
        cout << node->s << "\n";
    }

    for( auto child: node->child ){
        printAnsRecursive( child.second, depth+1 );
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int n = 0; n < N; n++ ){
        int k;
        cin >> k;

        Node* node = root;

        while ( k > 0 ){
            k--;
            string s;
            cin >> s;

            if ( node->child.find(s) == node->child.end() ){ // non-exist
                Node* newNode = new Node(s);
                node->child[s] = newNode;
                node = newNode;
            }
            else { // exist
                node = node->child[s];
            }
        }
    }

    printAnsRecursive( root, 0 );    
    return 0;
}
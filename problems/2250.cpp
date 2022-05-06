/* smsh0722 
 * 2250
 * 트리의 높이와 너비
 * */
#include <iostream>
#include <cstring>
using namespace std;

struct t_node{
    int lc;
    int rc;
};
struct w_range{
    int l, r;
};

int countWidthOfEachLevel( t_node* tree, w_range* widthOfEachLevel, int curNode, int curLevel, int leftMost );

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;

    t_node* tree = new t_node[N+1];
    // Input Tree
    for ( int i = 0; i < N; i++ ){
        int val, lc, rc;
        cin >> val >> lc >> rc;
        tree[val].lc = lc;
        tree[val].rc = rc;
    }

    int root = -1;
    // Find root
    {
        bool* isRoot = new bool[N+1];
        memset( isRoot, true, N+1 );

        // get flags
        for ( int i = 1; i <= N; i++ ){
            int lc = tree[i].lc;
            int rc = tree[i].rc;
            if ( lc != -1 )
                isRoot[lc] = false;
            if ( rc != -1 )
                isRoot[rc] = false;
        }
        // Search root
        for ( int i = 1; i <= N; i++ ){
            if ( isRoot[i] == true ){
                root = i;
                break;
            }
        }

        delete[] isRoot;
    }

    w_range* widthOfEachLevel = new w_range[N+1];
    // Count width of each level
    {
        for ( int i = 0 ; i <= N; i++ ){
            widthOfEachLevel[i].l = N;
            widthOfEachLevel[i].r = 1;
        }

        countWidthOfEachLevel( tree, widthOfEachLevel, root, 1, 1 );
    }

    int m_level = -1;
    int m_width = -1;
    // Get Max
    {
        for ( int i = 1; i <= N; i++ ){
            int cur_width = widthOfEachLevel[i].r - widthOfEachLevel[i].l + 1;

            if ( m_width < cur_width ){
                m_width = cur_width;
                m_level = i;
            }
        }
    }

    // Return Answer
    cout << m_level << " " << m_width;

    return 0;
}

int countWidthOfEachLevel( t_node* tree, w_range* widthOfEachLevel, int curNode, int curLevel, int leftMost )
{
    int numOfNode = 0;
    int curNodeIdx = -1;

    // Count Left
    {
        int lc = tree[curNode].lc;
        if ( lc != -1 )
            numOfNode += countWidthOfEachLevel( tree, widthOfEachLevel, lc, curLevel+1, leftMost );
    }

    // Set Idx;
    curNodeIdx = leftMost + numOfNode;
    
    // Count root
    numOfNode++;

    // Count Right
    {
        int rc = tree[curNode].rc;
        if ( rc != -1 )
            numOfNode += countWidthOfEachLevel( tree, widthOfEachLevel, rc, curLevel + 1, leftMost + numOfNode );
    }

    // set widthOfEachLevel
    widthOfEachLevel[curLevel].l = widthOfEachLevel[curLevel].l < curNodeIdx ? 
                                    widthOfEachLevel[curLevel].l : curNodeIdx;
    widthOfEachLevel[curLevel].r = widthOfEachLevel[curLevel].r > curNodeIdx ? 
                                    widthOfEachLevel[curLevel].r : curNodeIdx;

    return numOfNode;
}
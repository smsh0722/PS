#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main( void )
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;
    for ( int ti = 0; ti < T; ti++ ){
        string func_seq;
        int size;
        cin >> func_seq >> size;
        int arr[size];
        {
            char* data_c;
            {
                string data_s;
                cin >> data_s;
                data_s = data_s.substr( 1, data_s.length() - 2 );
                data_c = new char[data_s.length()+1];
                strcpy(data_c, data_s.c_str() );
            }
            int i = 0;
            char* ptok = strtok( data_c, "," );
            while ( ptok != NULL ){
                arr[i++] = atoi(ptok);
                ptok = strtok( NULL, "," );
            }
            delete[] data_c;
        }

        /* exectue sequence */
        bool reverse = false;
        int li = 0;
        int ri = size - 1;
        for ( int seq_i = 0; seq_i < func_seq.length(); seq_i++ ){
            char afunc = func_seq[seq_i];
            if ( afunc == 'R' )
                reverse = !reverse;
            else if ( afunc == 'D' ){
                if ( reverse == false )
                    li++;
                else 
                    ri--;
            }

            if ( li - ri > 1)
                break;
        }

        /* Print result */
        if ( li - ri > 1 ){
            cout << "error\n";
            continue;
        }
        else if ( li - ri == 1 ){
            cout << "[]\n";
        }
        else {
            cout << "[";
            while ( li <= ri ){
                if ( reverse == false )
                    cout << arr[li++];
                else   
                    cout << arr[ri--];

                if ( li <= ri ){
                    cout << ",";
                }
            }
            cout << "]\n";
        }
    }
}

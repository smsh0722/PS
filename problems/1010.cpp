#include <iostream>
using namespace std;

int factorial( const int n, const int r );

int main( void )
{
	int caseNum; cin >> caseNum;
	int siteL, siteR;
	
	for ( int i = 0; i < caseNum; i++ ){
		cin >> siteL >> siteR;
		cout << factorial( siteR, siteL ) << endl;
	}
}

int factorial( const int n, int r )
{
	if ( n == r )
		return 1;
	if ( r == 0 )
		return 0;
		
 	int result = 1;
	int tempN = n;
	int tempR = ( n - r ) < r ? ( n - r ) : r;
	int countN = 0, countR = 0;
	r = tempR;
	int data[tempR + 1] = { 0 };
	
	while( countN <= r && countR <= r ){
		if( ( countN == r )&&( countR == r ) )
			break;
		if( countN < r ){
			result *= tempN--;
			countN++;
		}
		for ( int i = 1; i <= tempR; i++ ){
			if ( data[i] == 0 ){
				if ( ( countR < r )&&( result % i == 0 ) ){
					result /= i;
					data[i] = 1;
					countR++;
				}
			}
		}
	}

	return result;
}

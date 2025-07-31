#include <iostream>
using namespace std;

int num = 1;
int& GetInt()
{
    return num;
}

int* GetIntP()
{
    return &num;
}

int main ( void )
{
    int a = GetInt();
    int& b = GetInt();
    int* c = GetIntP();
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << *c << endl;
    cout << "num: " << num << endl;

    b = 2;
    cout << "b=2" << endl;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << *c << endl;
    cout << "num: " << num << endl;

    *c = 3;
    cout << "c=3" << endl;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << *c << endl;
    cout << "num: " << num << endl;
}
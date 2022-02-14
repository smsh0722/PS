#include <cstdio>

using namespace std;

int dp(int * d, int n) {
    d[1] = 1;
    d[2] = 2;
    for (int i = 3; i <= n; i++) d[i] = (d[i-1] + d[i-2]) % 10007;

    return d[n];
}

int main() {

    int n;
    scanf("%d", &n);

    int d[n+1];
    printf("%d\n", dp(d, n));

    return 0;
}
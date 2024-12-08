#include <stdio.h>

int main() {
    long long a[100], n, k, tong = 0;
    scanf("%lld %lld", &n, &k);


    for (long long i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }


    for (long long i = 0; i < n; i++) {
        for (long long j = i + 1; j < n; j++) {
            if (a[j] < a[i]) {
                long long x = a[i];
                a[i] = a[j];
                a[j] = x;
            }
        }
    }

    
    for (long long i = 0; i < k; i++) {
        tong += a[i];
    }

    printf("%lld\n", tong);
    return 0;
}

#include <stdio.h>

long long int fib_i(int x) {
    long long int f0 = 1, f1 = 1, f2 = 0;
    for(int i = 0 ; i <= x ; i++) {
        f0 = f1;
	f1 = f2;
	f2 = f0 + f1;
    }
    return f2;
}

int
main() {
    printf("%lld\n",fib_i(42));
}

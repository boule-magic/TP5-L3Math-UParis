#include <stdio.h>

long long int fib_r(int x) {
    if(x < 2)
	return 1;
    else
	return fib_r(x-2) + fib_r(x-1);
}

int
main() {
    printf("%lld\n",fib_r(42));
}

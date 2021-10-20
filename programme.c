#include <stdio.h>
#include <math.h>

int max(int x, int y);
int max3(int x, int y, int z);
void swap(int x, int y);
int syracuse(int m);
long long int fib_r(int x);
long long int fib_i(int x);
struct fract {
    long long int num, den;
};
void print(struct fract x);
int pgcd(long long int a, long long int b);
struct fract canonique(struct fract x);
struct fract add(struct fract x, struct fract y);
struct fract div(struct fract x, struct fract y);
void suite(struct fract a);

int
main() {
    int a, b, t, i, fibo, k, n=0, syra, syramax=0;

    //Exercice 1

    printf("Exercice 1 :\n");
    printf("Saisir un entier : ");
    scanf("%d", &a);
    printf("Saisir un entier : ");
    scanf("%d", &b);    
    printf("max(%d,%d) = %d\n",a,b,max(a,b));
    printf("max3(%d,%d,42) = %d\n",a,b,max3(a,b,42));

    //Exercice 2

    printf("\nExercice 2 :\n");
    printf("a = %d, b = %d\n",a,b);
    printf("On swap à la main\n");
    t = a;
    a = b;
    b = t;
    printf("a = %d, b = %d\n",a,b);
    printf("swap(a,b)\n");
    swap(a,b);
    printf("a = %d, b = %d\n",a,b);
    printf("Rien n'a changé !\n");

    //Exercice 3

    printf("\nExercice 3 : Syracuse\n");
    printf("Entrez un entier naturel : ");
    scanf("%d",&k);
    
    for(i = 1 ; i <= k ; i++) {
	syra = syracuse(i);
	if (syramax < syra) {
	    syramax = syra;
	    n = i;
	}
	printf("%d --> temps de vol = %d\n",i,syra);
    }
    printf("n = %d\n", n);

    //Exercice 4

    printf("\nExercice 4 : Fibonacci\n");
    printf("Entrez un entier naturel : ");
    scanf("%d",&fibo);
    printf("\nfib_r => %lld\n", fib_r(fibo));
    printf("fib_i => %lld\n", fib_i(fibo));

    //Exercice 5

    printf("\nExercice 5 :\n");
    struct fract fx, fy = {3,4};
    printf("Saissez une fraction {a/b}:\n");
    printf("a = ");
    scanf("%lld", &fx.num);
    printf("b = ");
    scanf("%lld", &fx.den);
    fx = canonique(fx);
    suite(fx);
    printf("fx = ");
    print(fx);
    printf("\nfy = ");
    print(fy);
    printf("\nfx + fy = ");
    print(add(fx,fy));
    printf("\nfx / fy = ");
    print(div(fx,fy));
    printf("\n");

    //Exercice 6

    printf("\nExercice 6 :\n");
    for(n = 1 ; n <= 100 ; n++) {
	printf("e%d = %lf\n",n, pow(1+1.0/n,n)); //Tend vers e = 2.7182818284
    }    
    
    return 0;
}

int max(int x, int y) {
    if (x > y)
	return x;
    else
	return y;
}

int max3(int x, int y, int z) {
    return max(max(x,y),z);
}

void swap(int x, int y) {
    int t = x;
    x = y;
    y = t;
}

int syracuse(int m) {
    int n, compteur = 0;
    n = m;
    while (n != 1) {
	if (n%2 == 0)
	    n /= 2;
	else
	    n = n*3+1;
	compteur++;
    }
    return compteur;
}

long long int fib_r(int x) {
    printf("%d-", x);
    if(x == 0)
	return 1;
    else if (x == 1)
	return 1;
    else
	return fib_r(x-2) + fib_r(x-1);
}

long long int fib_i(int x) {
    long long int f0 = 1, f1 = 1, f2 = 0;
    for(int i = 0 ; i <= x ; i++) {
        f0 = f1;
	f1 = f2;
	f2 = f0 + f1;
    }
    return f2;
}

void print(struct fract x) {
    printf("{%lld/%lld}", x.num, x.den);
}

int pgcd(long long int a, long long int b) {
    long long int t;
    while(b != 0) {
	t = b;
	b = a%b;
	a = t;
    }
    return a;
}

struct fract canonique(struct fract x) {
    int diviseur = pgcd(x.num, x.den);
    x.num /= diviseur;
    x.den /= diviseur;
    return x;
}

struct fract add(struct fract x, struct fract y) {
    struct fract z = {x.num*y.den+y.num*x.den, x.den*y.den};
    return canonique(z);
}

struct fract div(struct fract x, struct fract y) {
    struct fract z = {x.num*y.den, x.den*y.num};
    return canonique(z);
}

//Permet de calculer et d'afficher une approximation de la racine carrée de a (méthode de Héron ou méthode babylonienne)
//Un long long int a ces limites ! Ici on atteint rapidement plus de 9.2e18. Lorsque l'on dépasse cette limite on retombe alors dans les négatifs vers -9.2e18.
//Pas ouf le cast "long long int" into "long double". Ça mériterait un warning non ? Ils n'ont pas la même valeur max n'est-ce pas ?
void suite(struct fract a) {
    struct fract x0 = canonique(a), x1;
    int i;
    printf("x0 = ");
    print(x0);
    printf("\n");
    for(i = 0 ; i < 20 ; i++) {
	x1 = add(x0, div(a, x0));
	x1.den *= 2;
	x0 = canonique(x1);
	printf("x = ");
	print(x0);
	printf(" ~= %Lg\n", (long double)x0.num/x0.den);
    }
}

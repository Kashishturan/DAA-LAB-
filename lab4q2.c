#include <stdio.h>
#include <complex.h>

// Binary exponentiation for complex numbers
complex double complexPow(complex double base, long long exp) {
    complex double result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}

int main() {
    long long n;
    printf("Enter the exponent (n): ");
    scanf("%lld", &n);

    // Define the complex number i as (-1)^(1/2)
    complex double i = csqrt(-1);

    // Calculate (1 + i)^n using binary exponentiation
    complex double result = complexPow(1 + i, n);

    printf("(1 + i)^%lld = %lf + %lfi\n", n, creal(result), cimag(result));
    return 0;
}
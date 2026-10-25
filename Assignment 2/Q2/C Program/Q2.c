#include <stdio.h>

// Function to calculate the sum of proper divisors of a number
int sum_proper_divisors(int num) {
    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int n;
    int pair_count = 0;

    // 1. Input the upper limit n
    printf("Enter the upper limit n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    printf("\nAmicable pairs up to %d:\n", n);

    // 2. Search for amicable pairs
    for (int a = 1; a <= n; a++) {
        int b = sum_proper_divisors(a);

        // Check conditions: 
        // 1. b <= n (both numbers within limit)
        // 2. b > a (ensures numbers are different and each pair is displayed only once with smaller first)
        if (b > a && b <= n) {
            if (sum_proper_divisors(b) == a) {
                printf("(%d, %d)\n", a, b);
                pair_count++;
            }
        }
    }

    // 3. Display summary report
    if (pair_count == 0) {
        printf("No amicable pairs found up to %d.\n", n);
    } else {
        printf("\nTotal amicable pairs found: %d\n", pair_count);
    }

    return 0;
}
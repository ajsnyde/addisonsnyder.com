//Function isprime (int)
//Returns true(false) if arg is prime(not prime).
//main or driver program is NOT included!


#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

bool isprime(int n) {
    if (n < 2)
        return (false);
    if (n == 2)
        return true;
    int max = int(ceil(sqrt(n)));
    int i = 2;
    while (i <= max) {
        if (n % i == 0)
            return false;
        i += 1;
    }
    return true;
}

/**
        To compile this with your hw1.cpp do:
        g++ 03prime.cpp -c    This creates a '03prime.o' file
        g++ hw1.cpp 03prime.o
*/


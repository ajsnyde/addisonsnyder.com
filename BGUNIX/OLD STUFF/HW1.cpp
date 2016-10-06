#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdbool.h>

using namespace std;

bool isprime(int);

int main ()
{
	int pid = fork();//split into 2 proccesses
	int random;
	int num_prime_child = 0;
	int num_prime_parent = 0;
	int num_non_prime_child = 0;
	int num_non_prime_parent = 0;
	
	const int REPS = 3000000;	// number of numbers to check for primes
	
	clock_t start, end;		// Creates time variables for calculating speed
	double cpu_time_used;		// Will hold time in seconds
	
	

	
	if(pid == 0)//If child
	{
		srand (time(NULL));
		start = clock();
		cout << "CHILD ID: " << getpid() << "\n";
		for(int i = 0; i < REPS; i++)
		{
			random = rand() % 1000 + 1;
			if (random < 2)
				num_non_prime_child++;
			if (random == 2)
				num_prime_child++;
			int max = int(ceil(sqrt(random)));
				int i = 2;
			while (i <= max) 
			{
				if (random % i == 0)
					num_non_prime_child++;
				i++;
			}
		}
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		cout << "Number of primes = " << num_prime_child << "\nNumber of non-primes: " << num_non_prime_child << "\nCPU time: " << cpu_time_used << " seconds\n";
		exit(1);
	}
	else// If parent
	{
		srand (time(NULL));
		start = clock();
		cout << "PARENT ID: " << getpid() << "\n";
		for(int i = 0; i < REPS; i++)
		{
			random = rand() % 1000;
			if (random < 2)
				num_non_prime_parent++;
			if (random == 2)
				num_prime_parent++;
			int max = int(ceil(sqrt(random)));
				int i = 2;
			while (i <= max) 
			{
				if (random % i == 0)
					num_non_prime_parent++;
				i++;
			}

		}
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		cout << "Number of primes = " << num_prime_parent << "\nNumber of non-primes: " << num_non_prime_parent << "\nCPU time: " << cpu_time_used << " seconds\n";
		exit(1);
	}
	
}
	
	
//THIS FUNCTION WAS COPIED DIRECTLY FROM '03prime.cpp' AND IS NOT MY ORIGINAL WORK:
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
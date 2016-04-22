/*
	Advanced OS - Spring 2015 - Dr. Rajaei
	~~~ 2/16/15 ~~~
	Addison Snyder
	Farbod Mirzaei
	Jiazuo Wang
*/

#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_cond_t full;
pthread_cond_t empty;
pthread_cond_t done;
pthread_mutex_t mutex;

const int BUFFER_SIZE = 10;
const int MAX = 1000;		// Max and min number of items to create
const int MIN = 1;
int buffer[BUFFER_SIZE];
int producer_index = 0;
int consumer_index = 0;
int free_slots = BUFFER_SIZE;
int iterations = 10;

using namespace std;

void *producer(void *arg)
{
	int num;
	iterations = ((rand() % 900) + 101);// produces number between 100 and 1000
	cout << "Iterations: " << iterations << "\n";

	for(int i = 0; i < iterations; i++)
	{
		producer_index = (i % BUFFER_SIZE);	//makes sure index is within bounds

		pthread_mutex_lock(&mutex);	//LOCK
		while(free_slots == 0)
			pthread_cond_wait(&full, &mutex);
		
		num = ((rand() % 1000) + 1);	//Add random number
		buffer[producer_index] = num;	//Add random number
		cout << "Producer - Item #" << i << " - #" << producer_index << " Data is now: " << buffer[producer_index] << "!\n";
		pthread_cond_signal(&empty);	//
		producer_index++;
		free_slots--;
		pthread_mutex_unlock(&mutex);
		usleep(1000);	// wait 1 millisecond
	}
	cout << "DONE PRODUCING!\n";
	usleep(1000);
	pthread_cond_signal(&done);
	return NULL;
}

void *consumer(void *arg)
{
	double avg = 0;
	int min = MAX;
	int max = MIN;

	for(int i = 0; i < iterations; i++)
	{
		consumer_index = (i % BUFFER_SIZE);	// Keeps index within bounds
		pthread_mutex_lock(&mutex);

		while(free_slots == BUFFER_SIZE)
			pthread_cond_wait(&empty, &mutex);


		if(buffer[consumer_index] > max)
			max = buffer[consumer_index];
		if(buffer[consumer_index] < min)
			min = buffer[consumer_index];	
		avg += buffer[consumer_index];	
		buffer[consumer_index] = 0;
		cout << "Consumer - #" << consumer_index << " Data has been eaten!\n";
		consumer_index++;
		free_slots++;
		pthread_cond_signal(&full);
		pthread_mutex_unlock(&mutex);
		usleep(1000);			// wait 1 millisecond
	}

	pthread_cond_wait(&done, &mutex);
	cout << "Got a DONE signal!\n";
	cout << "DONE CONSUMING!\n";
	cout << "MIN: " << min << "\nMAX: " << max << "\nAVG: " << (avg/(double)iterations) << "\nNUM ITEMS: " << iterations << "\n";
	pthread_cond_signal(&done);
	return NULL;
}

int main(void)
{
	pthread_t	producer_ID;
	pthread_t	consumer_ID;
	void		*exit_status;
	
	srand(time(NULL));				// seed random numbers

	pthread_cond_init(&full, NULL);			// initialize conditions and mutex
	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&done, NULL);
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&producer_ID, NULL, producer, NULL);	// creates threads
	pthread_create(&consumer_ID, NULL, consumer, NULL);

	pthread_join(producer_ID, &exit_status);	// destroys threads once finished
	pthread_join(consumer_ID, &exit_status);
	
	pthread_mutex_destroy(&mutex);			// destroys conditions
	pthread_cond_destroy(&full);
	pthread_cond_destroy(&empty);
	pthread_cond_destroy(&done);

	return 0;
}

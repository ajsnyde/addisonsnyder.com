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
int total_produced = 0;
int total_consumed = 0;
int produce = 0;
int consume = 0;
int it = 0;
int consumer_ready = 0;

using namespace std;

void *producer(void *arg)
{
	int pro = produce;
	produce++;
	int num;
	if(pro == 0){
		iterations = ((rand() % 9) + 101);// produces number between 100 and 1000
		cout << "Iterations: " << iterations << "\n";}
	else
		usleep(1000);

	for(int i = 0; total_produced < iterations; i++)
	{
		producer_index = (i % BUFFER_SIZE);	//makes sure index is within bounds

		pthread_mutex_lock(&mutex);	//LOCK
		while(free_slots == 0)
			pthread_cond_wait(&full, &mutex);
		
		num = ((rand() % 1000) + 1);	//Add random number
		buffer[producer_index] = num;	//Add random number
		producer_index++;
		total_produced++;
		cout << "Producer #" << pro << "- Item #" << total_produced << " - Index = " << producer_index << "!\n";
		pthread_cond_signal(&empty);	//
		
		free_slots--;
		pthread_mutex_unlock(&mutex);
		usleep(1000);	// wait 1 millisecond
	}
	cout << "PRODUCER #" << pro << " DONE PRODUCING!\n";
	usleep(1000);
	pthread_cond_signal(&done);
	return NULL;
}

void *consumer(void *arg)
{
	int con = consume;
	consume++;
	double avg = 0;
	int min = MAX;
	int max = MIN;

	for(int i = 0; total_consumed < iterations; it++)
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
		consumer_index++;		
		cout << "	Consumer #" << con << " - #" << consumer_index << " Data has been eaten!\n";
		total_consumed++;
		free_slots++;
		pthread_cond_signal(&full);
		pthread_mutex_unlock(&mutex);
		usleep(1000);			// wait 1 millisecond
	}

	//pthread_cond_wait(&done, &mutex);
	cout << "Got a DONE signal!\n";
	cout << "CONSUMER #" << con << " DONE CONSUMING!\n";
	while(con != consumer_ready)
		usleep(100);
	cout << "CONSUMER #" << con  << "\nMIN: " << min << "\nMAX: " << max << "\nAVG: " << (avg/(double)iterations) << "\nNUM ITEMS: " << iterations << "\n";
	pthread_cond_signal(&done);
	consumer_ready++;
	return NULL;
}

int main(void)
{
	pthread_t	producer_ID[5];
	pthread_t	consumer_ID[3];

	void *exit_status;
	long t;
	srand(time(NULL));				// seed random numbers

	pthread_cond_init(&full, NULL);			// initialize conditions and mutex
	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&done, NULL);
	pthread_mutex_init(&mutex, NULL);
	for (t = 0; t<5; t++){
		pthread_create(&producer_ID[t], NULL, producer, NULL);
		if (t < 3)
			pthread_create(&consumer_ID[t], NULL, consumer, NULL);
	}
	for (t = 0; t<5; t++){
		pthread_join(producer_ID[t], &exit_status);
		if (t < 3)
			pthread_join(consumer_ID[t], &exit_status);
	}
	pthread_cancel(consumer_ID[3]);
	pthread_mutex_destroy(&mutex);			// destroys conditions
	pthread_cond_destroy(&full);
	pthread_cond_destroy(&empty);
	pthread_cond_destroy(&done);

	return 0;
}

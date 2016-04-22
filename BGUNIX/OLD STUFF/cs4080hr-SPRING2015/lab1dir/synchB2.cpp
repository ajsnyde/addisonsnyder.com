
	/*Advanced OS - Spring 2015 - Dr. Rajaei
	~~~ 2/23/15 ~~~
	Addison Snyder
	Farbod Mirzaei
	Jiazuo Wang*/
	

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
int num_prod = 5;
int num_cons = 3;


using namespace std;

void *producer(void *arg)
{
	int num;
	int producer = num_prod;
	num_prod--;
	if(producer == 5)
	{
		iterations = ((rand() % 50) + 10);// produces number between 100 and 1000
		cout << "Iterations: " << iterations << "\n";
	}
	for(int i = 0; i < iterations; i++)
	{
		int a = i;
		for (int y = 0; y < 10; y++) //make sure the buffer[consumer_index] is not fill
		{
			producer_index = (i % BUFFER_SIZE); //makes sure index is within bounds
			if (buffer[producer_index] != 0)
				i++;
			else
				break;
		}
		i = a;
		
		pthread_mutex_lock(&mutex);	//LOCK
		while(free_slots == 0)
			pthread_cond_wait(&full, &mutex);
		
		num = ((rand() % 1000) + 1);	//Add random number
		buffer[producer_index] = num;	//Add random number
		cout << "Producer#" << producer << " - Item #" << i << " - #" << producer_index << " Data is now: " << buffer[producer_index] << "!\n";
		pthread_cond_signal(&empty);	//
		producer_index++;
		free_slots--;
		pthread_mutex_unlock(&mutex);
		//usleep(10);	// wait 1 millisecond
	}
	cout << "DONE PRODUCING!\n";
	num_prod--;
	//usleep(1000);
	pthread_cond_signal(&empty);
	return NULL;
}

void *consumer(void *arg)
{
	double avg=0;
	int con=0;
	int min=1000;
	int max=0;
	int consumer = num_cons;
	int y=0;
	num_cons--;

	for (int i = 0; i < i + 1; i++)
	{
		if (num_prod == 0 && free_slots >= 10)
			break;
		for (y = 0; y < 10; y++) //make sure the buffer[consumer_index] is not empty
		{
			consumer_index = ((y + 1) % BUFFER_SIZE);
			usleep(20);
			if (buffer[consumer_index] != 0)
				break;
	}		

		 pthread_mutex_lock(&mutex);

		 while (free_slots == BUFFER_SIZE)
			 pthread_cond_wait(&empty, &mutex);
		 if (buffer[consumer_index] != 0){
			 if (buffer[consumer_index] > max)
				 max = buffer[consumer_index];
			 if (buffer[consumer_index] < min)
				 min = buffer[consumer_index];
			 avg += buffer[consumer_index];
			 cout << "Consumer#" << consumer << " - #" << consumer_index << " Data has been eaten!" << "\n";
		 }
			 buffer[consumer_index] = 0;
			 consumer_index++;
			 free_slots++;
		pthread_cond_signal(&full);
		pthread_mutex_unlock(&mutex);
		con++;
		usleep(10);
	}

	usleep(1000); //pthread_cond_wait(&done, &mutex);
	pthread_cond_signal(&empty);
	free_slots++;
			  cout << "Got a DONE signal!\n";
			  cout << "DONE CONSUMING!\n";
			  cout << "the consumer" << consumer << "\n" << "MIN: " << min << "\nMAX: " << max << "\nAVG: " << (avg / (double)con) << "\nNUM ITEMS: " << con << "\n";
			  pthread_cond_signal(&done);
			  usleep(10000);
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
	pthread_mutex_destroy(&mutex);			// destroys conditions
	pthread_cond_destroy(&full);
	pthread_cond_destroy(&empty);
	pthread_cond_destroy(&done);

	return 0;
}

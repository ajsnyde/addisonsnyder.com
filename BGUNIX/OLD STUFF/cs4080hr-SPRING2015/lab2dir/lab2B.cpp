//Addison Snyder
//Ryan Ricker
//Evan Coane

#include <iostream>

using namespace std;

typedef struct job{		//Standard job item
	int time2Left, neededTime, arrivalTime;	//time2Left - number of TUs needed for completion (changes as it nears completion)
	bool done;				//neededTime - total TUs needed for entire job	(shouldn't change)
	int time2Completed;			//waitTime - time spent in ready queue
	int waitTime;
} job;

void init(job[]);		// init - sets jobs to hard-coded numbers provided
void compute(job[]);		// system time (emulated)
	int time2;
	int lastjob;		// used to determine when job context overhead is added
	bool select2;		// indicates whether a job was selected, and used to end main loop when 'CPU' is idle
int main()
{
	int slice = 1;		// timeslice given to jobs each cycle
	time2 = 1;		
	lastjob = -1;
	int context = 10;	//context switch delay in TU
	job jobs[20];		//main list of jobs
	init(jobs);
	select2 = true;



	//	SHORTEST TIME FIRST:
	int minIndex = -1, min = 999999;
	//cout << "INTO THE LOOP\n";
	while(select2)
	{
		select2 = false;
		//	cout << time2 << " = time2 --- ";
		for(int i = 0; i < 20; i++){			// FIND SHORTEST JOB AVAILBLE BASED ON TIME NEEDED (that is left)
			if(jobs[i].time2Left < min && !jobs[i].done && jobs[i].arrivalTime <= time2){
				select2 = true;
				min = jobs[i].time2Left;
				minIndex = i;
			}
		}
		//	cout << "Job " << minIndex+1 << " selected!\n";
		if(minIndex != lastjob)
			time2 += context;
		lastjob = minIndex;
		jobs[minIndex].time2Left -= slice;
		

		for(int i = 0; i < 20; i++){	// adds wait time to jobs in ready queue
			if(i != minIndex && jobs[i].arrivalTime <= time2 && !jobs[i].done)
				jobs[i].waitTime++;
		}

		if(jobs[minIndex].time2Left <= 0){	// flags job as complete as needed, and then calculates statistics
			jobs[minIndex].done = true;
			jobs[minIndex].time2Completed = time2;
		//	cout <<  minIndex+1 << " is DONE!\n";
		}
		time2 += slice;	// system time is updated
		minIndex = -1;	// reseed min
		min = 500;

	}
	compute(jobs);
	return 0;
}

void init(job jobs[]){
	cout << "INITIALIZING!\n";

	jobs[0].time2Left =		jobs[0].neededTime = 10;	jobs[0].arrivalTime = 1;
	jobs[1].time2Left =		jobs[1].neededTime = 2;		jobs[1].arrivalTime = 1;
	jobs[2].time2Left =		jobs[2].neededTime = 5;		jobs[2].arrivalTime = 2;
	jobs[3].time2Left =		jobs[3].neededTime = 4;		jobs[3].arrivalTime = 3;
	jobs[4].time2Left = 		jobs[4].neededTime = 50;	jobs[4].arrivalTime = 7;
	jobs[5].time2Left = 		jobs[5].neededTime = 16;	jobs[5].arrivalTime = 8;
	jobs[6].time2Left =		jobs[6].neededTime = 7;		jobs[6].arrivalTime = 8;
	jobs[7].time2Left =		jobs[7].neededTime = 8;		jobs[7].arrivalTime = 12;
	jobs[8].time2Left =		jobs[8].neededTime = 9;		jobs[8].arrivalTime = 14;
	jobs[9].time2Left = 		jobs[9].neededTime = 21;	jobs[9].arrivalTime = 14;
	jobs[10].time2Left =		jobs[10].neededTime = 117;	jobs[10].arrivalTime = 22;
	jobs[11].time2Left = 	jobs[11].neededTime = 3;	jobs[11].arrivalTime = 22;
	jobs[12].time2Left = 	jobs[12].neededTime = 25;	jobs[12].arrivalTime = 26;
	jobs[13].time2Left = 	jobs[13].neededTime = 14;	jobs[13].arrivalTime = 26;
	jobs[14].time2Left = 	jobs[14].neededTime = 25;	jobs[14].arrivalTime = 29;
	jobs[15].time2Left = 	jobs[15].neededTime = 86;	jobs[15].arrivalTime = 33;
	jobs[16].time2Left = 	jobs[16].neededTime = 1;	jobs[16].arrivalTime = 45;
	jobs[17].time2Left = 	jobs[17].neededTime = 82;	jobs[17].arrivalTime = 46;
	jobs[18].time2Left = 	jobs[18].neededTime = 2;	jobs[18].arrivalTime = 49;
	jobs[19].time2Left = 	jobs[19].neededTime = 15;	jobs[19].arrivalTime = 51;

	for(int i = 0; i < 20; i++)
	{
		jobs[i].done = false;
		jobs[i].time2Completed = -1;
		jobs[i].waitTime = 0;
	}

}

void compute(job jobs[]){		// give basic stats on job completions


	double avgWait = 0, avgCompleteTime = 0; 
	double turnaround = 0;



	for(int i = 0; i < 20; i++) // find avgs
	{
		avgWait += jobs[i].waitTime;
		avgCompleteTime += jobs[i].time2Completed;
		turnaround += (jobs[i].time2Completed - jobs[i].arrivalTime);
	}
	
	avgWait /= 20;
	avgCompleteTime /= 20;
	cout << "Average Wait = " << avgWait << "\nAverage Complete Time = " << avgCompleteTime << "!\nThroughput = " << 20/(double)time2 << "\nAverage Turnaround = " << turnaround/20 << "\n";
	return;
}

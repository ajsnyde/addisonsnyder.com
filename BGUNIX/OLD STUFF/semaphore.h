//////////////////////////////////////////////////////////////////////////

// File:	semaphore.h

//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

//define KEY	888

union semun {
    int	val;
    struct	semid_ds	*buf;
    ushort	*array;
};

class Semaphore {
	
  private:
    const unsigned int	SemCount;
    int 		SemID;

  public:

    // Create a semaphore group.  Return the semaphore id for the group. 
    Semaphore (key_t key, int howManySemaphoresToCreat);

    // Set the initial value of a semaphore.
    void Init (int SemaphoreNumber, int Value);


    // Return the current value of the semaphore, semaphoreNumber
    int ReadValue (int SemaphoreNumber);


    // Decrease the value of a semaphore, semaphoreNumber, by 1
    void Wait (int SemaphoreNumber);


    // Increase the value of a semaphore, semaphoreNumber, by 1.
    void Signal (int SemaphoreNumber);

    // Remove the semaphore group.
    void Destroy( );


};

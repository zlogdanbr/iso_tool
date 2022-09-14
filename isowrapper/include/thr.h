/*
*	-----------------------------------------------------------------
*	Modulo de threads
*	Daniel V. Gomes 
*   ------------------------------------------------------------------
*/
#ifndef _THREADS_
#define _THREADS_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <unistd.h>


// you actually won't need all these headers above, but they might come at hand...

using namespace std;

#define MAX_THREADS 10
/*--------------------------------------------------------------------------------------------
*		Threads
---------------------------------------------------------------------------------------------*/
class ThreadWrapper
{
public:
    ThreadWrapper();
    void AddRun(void* (*f)(void*) );
    int GetThreadID()const{ return tid ;};
    void Join(int id );
    bool getFullStack()const{ return FullStack ;};
private:
    pthread_t pthreadObj[ MAX_THREADS ];
    bool FullStack;
    int tid;
};
 
#endif
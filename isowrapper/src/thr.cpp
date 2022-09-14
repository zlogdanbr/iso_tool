#include "thr.h"

ThreadWrapper::ThreadWrapper(  )
{
     // contador das threads usadas no pool
     tid = 0;
     FullStack = false;
}

void ThreadWrapper::AddRun( void* (*f)(void*) )
{
    // executa a thread atraves da funcao passada para f
    if ( tid < MAX_THREADS )
    {
	    pthread_create( &pthreadObj[tid], NULL, f, NULL);
	    tid++;
    }
    else
    {
	   FullStack = true;
    }
}

void ThreadWrapper::Join(int id )
{
    // join da thread
    pthread_join(pthreadObj[id],NULL);
}

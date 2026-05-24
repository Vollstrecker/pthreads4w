#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <pthread.h>

enum {
  Size = 10000
};

const int  ShouldSum = (Size-1)*Size/2;

short Verbose = 1;

short ThreadOK[3] = {0,0,0}; // Main, Thread1, Thread2

// Thread
void *_thread(void* Id) {
  int i;
  int x[Size];

#pragma omp parallel for
for ( i = 0; i < Size; i++ ) {
  if (Verbose && i%1000==0) {
    int tid = omp_get_thread_num();
#pragma omp critical
    printf("thread %d : tid %d handles %d\n",(int)(size_t)Id,tid,i);
  }

    x[i] = i;
  }

  int Sum=0;
  for ( i = 0; i < Size; i++ ) {
    Sum += x[i];
  }
  if (Verbose) {
#pragma omp critical
    printf("Id %d : %s : %d(should be %d)\n",(int)(size_t)Id, __FUNCTION__, Sum,ShouldSum);
  }
  if (Sum == ShouldSum) ThreadOK[(int)(size_t)Id] = 1;
  return NULL;
}

// MainThread
void MainThread() {
  int i;

#pragma omp parallel for
  for ( i = 0; i < 4; i++ ) {
    int tid = omp_get_thread_num();
#pragma omp critical
    printf("Main : tid %d\n",tid);
    _thread((void *)(size_t)tid);
  }
  return;
}

// Comment in/out for checking the effect of multiple threads.
#define SPAWN_THREADS

// main
int main(int argc, char *argv[]) {

  if (argc>1) Verbose = 1;

  printf("%s%s%s\n",
         "Nested parallel blocks are ",
         omp_get_max_active_levels() > 1 ? " " : "NOT ",
         "supported.");

  MainThread();

#ifdef SPAWN_THREADS
  {
    pthread_t a_thr;
    pthread_t b_thr;
    int status;

    status = pthread_create(&a_thr, NULL, _thread, (void*) 1 );
    if ( status != 0 ) {
      printf("Failed to create thread 1\n");
      return (-1);
    }

    status = pthread_create(&b_thr, NULL, _thread, (void*) 2 );
    if ( status != 0 ) {
      printf("Failed to create thread 2\n");
      return (-1);
    }

    printf("%s:%d - %s - a_thr:%p - b_thr:%p\n",
           __FILE__,__LINE__,__FUNCTION__,a_thr.p,b_thr.p);

    status = pthread_join(a_thr, NULL);
    if ( status != 0 ) {
      printf("Failed to join thread 1\n");
      return (-1);
    }
    printf("Joined thread1\n");

    status = pthread_join(b_thr, NULL);
    if ( status != 0 ) {
      printf("Failed to join thread 2\n");
      return (-1);
    }
    printf("Joined thread2\n");
  }
#endif // SPAWN_THREADS

  short OK = 0;

  OK = 1;
  {
    short i;
    for (i=0;i<3;i++) OK &= ThreadOK[i];
  }
  if (OK) printf("OMP : All looks good\n");
  else printf("OMP : Error\n");

  return OK?0:1;
}

//g++ -fopenmp omp_test.c -o omp_test -lpthread

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "knn.h"
#include <sys/time.h>


float random_float(){
    return (float) rand() /RAND_MAX;
}

static __inline__ unsigned long long rdtsc(void)
{
  unsigned long long int x;
     __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
     return x;
}

struct Point generate_point(){
    struct Point p;
    p.w = random_float();
    p.x = random_float();
    p.y = random_float();
    p.z = random_float();
    return p;
}

int main()
{
    srand((unsigned int) time(NULL));
    struct Point points[NUM_POINTS];
    struct timeval stop, start;

    for(int i = 0; i < NUM_POINTS; i ++){
        points[i] = generate_point();
    }

    gettimeofday(&start, NULL);
    unsigned long long cycles = rdtsc(); //1
    compute_centroids(points);
    cycles = rdtsc() - cycles;           //2
    gettimeofday(&stop, NULL);
    double secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("time taken %f\n",secs);
    printf("Time is %d\n", (unsigned)cycles);
    return 0;
}

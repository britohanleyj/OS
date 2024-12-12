#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

Zem_t Fork[30];
Zem_t mutex; 
int avail[30];
int philosophers;

int left(int p) { return p; }
int right(int p) { return (p + 1) % philosophers; }

void getForks(int p)
{
    while (1) {
        Zem_wait(&mutex); 

        // check if both forks are available
        if (avail[left(p)] == 1 && avail[right(p)] == 1) { 
            avail[left(p)] = 0;
            avail[right(p)] = 0; //forks no longer available
            Zem_post(&mutex);
            Zem_wait(&Fork[left(p)]); 
            Zem_wait(&Fork[right(p)]); 
            return;
        }
        Zem_post(&mutex); //If both were not picked up
        
    }
}

void putForks(int p)
{
    Zem_wait(&mutex); 
    avail[left(p)] = 1; // mark forks as available 
    avail[right(p)] = 1; 
    Zem_post(&mutex);
    Zem_post(&Fork[left(p)]);
    Zem_post(&Fork[right(p)]);
}

void Phil(int p)
{
    while (1)
    {
        printf("Philosopher %d is in philosophical thought\n", p);
        sleep(1); 
        printf("Philosopher %d is hungry\n", p);
        getForks(p); 
        printf("Philosopher %d is enjoying their food\n", p);
        sleep(1); 
        putForks(p);
        printf("Philosopher %d is done eating\n", p);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("error with arguement");
        return 1;
    }

    philosophers = atoi(argv[1]);
    Zem_init(&mutex, 1);

    // Initialize forks
    for (int i = 0; i < philosophers; ++i)
    {
        Zem_init(&Fork[i], 1);
        avail[i] = 1;
    }

    // create phil threads
    pthread_t c;
    for (int i = 0; i < philosophers; ++i)
    {
        long long int me = i;
        Pthread_create(&c, NULL, (void *(*)(void *))Phil, (void *)me);
    }

    // Wait for threads to finish 
    for (int i = 0; i < philosophers; ++i)
    {
        Pthread_join(c, NULL);
    }

    return 0;
}


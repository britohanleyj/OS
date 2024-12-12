#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

Zem_t Fork[30];
Zem_t table; 
int philosophers;

int left(int p) { return p; }
int right(int p) { return (p + 1) % philosophers; }

void getForks(int p)
{
    Zem_wait(&Fork[right(p)]);
    Zem_wait(&Fork[left(p)]);
    printf("Philosopher %d is getting forks \n", p);
}

void putForks(int p)
{
    Zem_post(&Fork[left(p)]);
    Zem_post(&Fork[right(p)]);
    printf("Philosopher %d is done eating and is wiping off their forks\n", p);
}

void getToTable(int p) 
{
     Zem_wait(&table); 
     printf("Philosopher %d has arrived\n", p); 
}

void leaveTable(int p) 
{
     Zem_post(&table); 
     printf("Philosopher %d has left the table\n", p); 
}

void Phil(int p)
{
    while (1)
    {
        printf("Philosopher %d is in philosophical thought\n", p);
        sleep(1);
        getToTable(p);
        getForks(p); 
        printf("Philosopher %d is enjoying their food\n", p);
        sleep(1);
        putForks(p);
        leaveTable(p);
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
    Zem_init(&table, philosophers - 1); // n-1 philosophers at the table

    // Initialize forks
    for (int i = 0; i < philosophers; ++i)
    {
        Zem_init(&Fork[i], 1);
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

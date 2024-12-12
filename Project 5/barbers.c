#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "common_threads.h"
#include "zemaphore.h"

// Shared resources
Zem_t barberReady;      // barber availability
Zem_t customerReady;    // customer availability
Zem_t mutex;           
Zem_t barberSleeping;   // if barber is sleeping
int waitingCustomers = 0;  // # of waiting customers
int n;                  // chairs

void* barber(void* arg) {
    while (1) {
        printf("Barber is sleeping. Waiting for the customers\n"); 
        Zem_wait(&customerReady); // wait for customer
        
        printf("Barber is awake and cutting hair.\n");

        Zem_wait(&mutex);
        waitingCustomers--;
        printf("Barber is cutting hair. Waiting customers: %d\n", waitingCustomers);
        Zem_post(&barberReady);  
        Zem_post(&mutex);

        sleep(1); //cutting time
    }
}

void* customer(void* arg) {
    int id = (int)(long)arg;  // Customer ID

    Zem_wait(&mutex);

    if (waitingCustomers < n) {
        waitingCustomers++; //increment waiting customers
        printf("Customer %d is waiting. Total waiting: %d\n", id, waitingCustomers);
        Zem_post(&customerReady); 
        Zem_post(&mutex);

        Zem_wait(&barberReady); // check for barber to be ready
        printf("Customer %d is getting a nice cut.\n", id);
    } else {
        printf("Customer %d found no empty chairs and left.\n", id);
        Zem_post(&mutex);
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("error with arguement");
        return 1;
    }

    n = atoi(argv[1]);  // chairs

    Zem_init(&barberReady, 0);
    Zem_init(&customerReady, 0);
    Zem_init(&mutex, 1);
    Zem_init(&barberSleeping, 1);

    pthread_t barberThread;
    Pthread_create(&barberThread, NULL, barber, NULL);

    pthread_t c;
    for (int i = 0; i < 100; i++) {
        long long int me = i;
        Pthread_create(&c, NULL, customer, (void*)me);
        sleep(rand() % 5);  // arrival time 0-5
    }

    for (int i = 0; i < 100; i++) {
        Pthread_join(c, NULL);
    }

    return 0;
}

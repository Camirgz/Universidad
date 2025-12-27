#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Function to generate a random number
void* generateRandomNumber(void* seed) {

    unsigned int* s = (unsigned int*)seed; // Cast the seed to unsigned int
    int* number = malloc(sizeof(int)); //Reserve memory for the random number
    *number = rand_r(s) % 101; // Generate a random number between 0 and 100
    return number; // Return the random number

}

int main(void) {

    pthread_t nietoUno, nietoDos; // Threads for the grandsons
    unsigned int seed1 = (unsigned int)time(NULL);
    unsigned int seed2 = (unsigned int)getpid();

    //Error handling
    int errorUno = pthread_create(&nietoUno, NULL, generateRandomNumber, &seed1);
    int errorDos = pthread_create(&nietoDos, NULL, generateRandomNumber, &seed2);

    // Check if the threads were created successfully
    if (errorUno == EXIT_SUCCESS && errorDos == EXIT_SUCCESS) {
        printf("Threads created successfully\n");
    } else {
        fprintf(stderr, "Error: could not create secondary threads\n");
        return EXIT_FAILURE;
    }

    // Join threads and get the random numbers
    int *number1, *number2;
    pthread_join(nietoUno, (void**)&number1); 
    pthread_join(nietoDos, (void**)&number2);

    // Print the numbers
    printf("Number of grandson 1 is: %d\n", *number1); //%d\n" is used to print integers
    printf("Number of grandson 2 is: %d\n", *number2);

    // Free reserved memory
    free(number1);
    free(number2);

    return 0;
}

//
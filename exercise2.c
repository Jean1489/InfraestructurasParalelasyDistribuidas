#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    int Array[100]; // Use rand() % 10000 for init
    int max = 0;
    int min = 100000; 
    int avg;
    int sum = 0;

    //Initialize the random number generator
    srand(time(NULL));

    //Initialize the array with random numbers
    #pragma omp parallel for
    for(int i = 0; i < 100; i++){
        Array[i] = rand()%10000;
    }

    //Find the maximun and minimun values
    #pragma omp parallel
    {
        int local_max = 0;    // Local maximum for each thread
        int local_min = 100000; // Local minimum for each thread

        // Parallel search for the maximum and minimum
        #pragma omp for
        for (int i = 0; i < 100; i++) {
            if (Array[i] > local_max) {
                local_max = Array[i]; // Update local max
            }
            if (Array[i] < local_min) {
                local_min = Array[i]; // Update local min
            }
        }

        // Update global maximum and minimum safely
        #pragma omp critical
        {
            if (local_max > max) {
                max = local_max; // Update global max
            }
            if (local_min < min) {
                min = local_min; // Update global min
            }
        }
    }

    // Calculate the sum for the average
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 100; i++) {
        sum += Array[i]; // Sum the elements of the array
    }

    // Calculate the average
    avg = sum / 100; // Divide by 100 to ensure int division

    // Print the results
    printf("Max value: %d\n", max);
    printf("Min value: %d\n", min);
    printf("Average value: %d\n", avg);

    


    return 0;
}
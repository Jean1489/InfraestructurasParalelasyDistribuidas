#include <omp.h>
#include <stdio.h>

int main() {
    #pragma omp parallel num_threads(10)
    {
        int thread_id = omp_get_thread_num();
        if (thread_id %2 == 0) {
           printf("Hello from even thread %d\n", thread_id); 
        }else {
            printf("Hello from odd thread %d\n", thread_id);
        }
        
    }
    return 0;
}
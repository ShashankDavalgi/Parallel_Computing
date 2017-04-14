#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int n=50000000;   //number until which primes are counted (inclusive)

int main (int argc, char *argv[]) {

    long local_count=0, global_count=0,     //variables used to keep count of the primes
    start, finish,      //highest and lowest possible primes for this processor 
    i;  

    int rank,           //processor id 
    p,          //number of processes
    size, proc0_size;   //amount of numbers to check on any processor and proc 0
double runtime;         //variable used to keep track of total elapsed time

    //initialize the MPI execution environment
    MPI_Init (NULL, NULL);

    //determine the rank of the calling processor in the communicator
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
        //determine the size of communicator
    MPI_Comm_size (MPI_COMM_WORLD, &p);

    //Ensures that every processor enters code at around the same time
    MPI_Barrier(MPI_COMM_WORLD);
    //Start the timer
    runtime = -MPI_Wtime();

    //compute the range and size to be used for this processor
    start = 2 + rank*(n-1)/p;
    finish = 1 + (rank+1)*(n-1)/p;
    size = finish - start + 1;

    //determine the size of processor 0
    proc0_size = (n-1)/p;

    //in the case where there are too many processors for the amount of numbers
    //to check...   
    if ((2 + proc0_size) < (long) sqrt((double) n)) {
        if (rank == 0)
            printf ("Too many processors to calculate the number of primes up to %d\n", n);
        MPI_Finalize();
        exit(1);
    }
    int j;
    //check every number in the range of this processor
    for (j=start; j<=finish; j++){
     //if the number is not composite, ie prime, increment the local counter
     if (isComposite(j)==0){
        local_count++;
     }
     }

     //MPI_Reduce used to combine all local counts
         MPI_Reduce (&local_count, &global_count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

     //adjust the total elapsed runtime
     runtime += MPI_Wtime();
     printf("Process %d finished\n", rank); 

     // print the results from process ranked root
     if (rank == 0) {
            printf ("There are %ld primes less than or equal to %d\n", global_count, n);
        printf ("Total elapsed time:  %f seconds\n", runtime);
     }

     //terminate the execution environment
     MPI_Finalize ();
     return 0;
   }

//function to check if a number is composite
//returns 0 if it is not composite (prime) and returns a 1 if it is composite

int isComposite (int num){

int retval=0;

if(num==1)
        retval = 1;

   else if(num%2 == 0 && num!=2)
        retval = 1;

    if(retval != 1) {
    int j;
    for(j=3; j<num; j+=2) {
                if(num%j == 0 ){
                        retval = 1;
                        break;
                }
                if(j*j>num) break;
            }
    }

if(retval == 0)
    return 0;
else 
    return 1;
    
}

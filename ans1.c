#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

const int MAX_RANDOM = 10; 
int Find_sum(int my_contrib, int my_rank, int p, MPI_Comm comm);

int main(int argc, char* argv[]) {
   int comm_sz, my_rank;
   MPI_Comm comm;
   int x,sum;
   
   MPI_Init(&argc, &argv);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &comm_sz);
   MPI_Comm_rank(comm, &my_rank);

   srandom((unsigned)time(NULL) + my_rank);
   x = random() % MAX_RANDOM;
   printf("%d,",x);
   sum = Find_sum(x, my_rank, comm_sz, comm);
   if (my_rank == 0)
      printf("\n Final sum = %d\n", sum);
   MPI_Finalize();
   return 0;
} 
int Find_sum(int x, int my_rank, int comm_sz, MPI_Comm comm) {
    int sum =x;
    int temp,partner;
    int done = 0;
    unsigned bitmask = 1;
    MPI_Status status;

    //Using bitwise exclusive or for pairing processes 
    while (!done && bitmask < comm_sz) {
        partner = my_rank ^ bitmask;
        if (my_rank < partner) {
            MPI_Recv(&temp, 1, MPI_INT, partner, 0, comm, &status);
            sum += temp;
            bitmask <<= 1;
        } else {
            MPI_Send(&sum, 1, MPI_INT, partner, 0, comm); 
            done = 1;
        }
    }
    return sum;
} 



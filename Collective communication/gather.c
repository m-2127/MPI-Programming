#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <malloc.h>
#define SENDARRAYSIZE 4

int main(int argc, char **argv){
 MPI_Init(&argc,&argv);


int sendarray[SENDARRAYSIZE]; 
int root = 0, gsize, myrank, *rbuf;

MPI_Comm_rank( MPI_COMM_WORLD, &myrank); 

   if ( myrank == root) { 
   MPI_Comm_size( MPI_COMM_WORLD, &gsize); 
   rbuf = (int *)malloc(gsize*SENDARRAYSIZE*sizeof(int)); 
   }
  
  //int local = myrank*SENDARRAYSIZE;
  
   for(int i =0 ; i < SENDARRAYSIZE ; i++){
	sendarray[i] = myrank*SENDARRAYSIZE + i;
   } 
  
MPI_Gather( sendarray, SENDARRAYSIZE, MPI_INT, rbuf, SENDARRAYSIZE, MPI_INT, root, MPI_COMM_WORLD);


if ( myrank == root) { 
	for(int j = 0; j < gsize ; j++){
	for(int i = j*SENDARRAYSIZE ; i < (j*SENDARRAYSIZE + SENDARRAYSIZE) ; i++){
	  	   printf("%d ", rbuf[i]);
	}
	printf("\n");
}
} 
 
 MPI_Finalize();
 }

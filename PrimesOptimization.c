#include <stdlib.h>
#include <mpi.h> 
#include <stdio.h>


long primeOne(long long *searchArr, long long *limits);

double main(int argc, char **argv) {

  MPI_Init(&argc, &argv);

  long long totalSearch = atoi(argv[1]);
  long packetSize = atoi(argv[2]);

  int myid, numprocs;
  long long limits[2];
  long long j = 0;
  long long k = 0;
  long long i = 0;
  long long z;
  long long place;
  long long sbe = 0;
  long long totalPrimes = 0;
  long receivingPacketSize; // So that mpi doesnt send unnecicarliy long arrays
  double startTime, endTime;
  MPI_Status status;

  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  place = 2; //FIRST PRIME NUMBER TO TEST

  
  if (myid == 0) {//------------------MASTER----------------------------------
    long long *primeFound = malloc(totalSearch * sizeof(long long));
    long long *searchArr = malloc(packetSize * sizeof(long long));

    startTime = MPI_Wtime();

    do {
    j = 1; //RESETTING SLAVE COUNT

      while (totalSearch >= place && j < numprocs) {

        //SETTING SEARCH BOUNDS TO SEND TO SLAVE
        limits[0] = place;
        if (place + packetSize >= totalSearch) { //TRIGGERED WHEN FINISHED. SENDS == BOUNDS
          limits[1] = totalSearch;
          place = totalSearch;
        } else { //NORMAL PACKET BOUNDS WRITE
          place += packetSize;
          limits[1] = place - 1;
        }

        //SENDING SEARCH BOUNDS TO SLAVE
        MPI_Send(limits, 2, MPI_LONG_LONG, j, 11, MPI_COMM_WORLD);
        j++;
        
      }

      //RECEIVEING PRIMES
      for (sbe = 1; sbe < numprocs; sbe++) {
        MPI_Recv(&receivingPacketSize, 1, MPI_LONG_LONG, sbe, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(searchArr, receivingPacketSize, MPI_LONG_LONG, sbe, 1, MPI_COMM_WORLD, &status);
        for (k = 0; k < receivingPacketSize; k++ ) {

          primeFound[totalPrimes] = searchArr[k];
          totalPrimes++;

        }
      }

    } while (totalSearch > place);
    endTime = MPI_Wtime();

    printf("That took %f seconds\n",endTime - startTime);
    fflush(stdout);

    printf("We found %lld primes\n\n",totalPrimes);
    fflush(stdout);

    free(primeFound);
    free(searchArr);

  } 
  

  if (myid != 0) { //------------------SLAVES------------------------------------
    long long *searchArr = malloc(packetSize * sizeof(long long));

    for (z = 0; z < (double)(totalSearch - 2)/packetSize/(numprocs - 1); z++) { 
      MPI_Recv(limits, 2, MPI_LONG_LONG, 0, 11, MPI_COMM_WORLD, &status); //RECIEVES SEARCH BOUNDS\

      receivingPacketSize = primeOne(searchArr, limits);

      MPI_Send(&receivingPacketSize, 1, MPI_LONG_LONG, 0, 1, MPI_COMM_WORLD);
      MPI_Send(searchArr, receivingPacketSize, MPI_LONG_LONG, 0, 1, MPI_COMM_WORLD);
    }

    free(searchArr);
  }

  MPI_Finalize();           /* EXIT MPI */
  return endTime - startTime;
}

long primeOne(long long *searchArr, long long *limits) {
  long position = 0;
  long long j, k;

  for (j = limits[0]; j <= limits[1]; j++) { //SEARCHING FOR PRIMES
    k = 2;
    while ((j % k) != 0) {
      k++;
    }

    if (j == k) {
      searchArr[position] = j;
      position++;
    }
  }
  return position;
}



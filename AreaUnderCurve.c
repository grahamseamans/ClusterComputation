#include <stdlib.h>
#include <mpi.h> 
#include <stdio.h>
#include <math.h>

void areaUnderLine(double *area, long long *limits, double percision);
void areaUnderCurve(long long *calcCounter, double *area, long long *limits, double percision);

int main(int argc, char **argv) {

  MPI_Init(&argc, &argv);

  long long totalSearch = atoi(argv[1]);
  long packetSize = atoi(argv[2]);
  double percision = atof(argv[3]);

  int myid, numprocs;
  long long limits[2];
  long long j = 0;
  long long k = 0;
  long long i = 0;
  long long z;
  long long place;
  long long sbe = 0;
  double startTime, endTime;
  double area = 0;
  long long calcCounter = 0;
  MPI_Status status;

  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  place = 0; //BEGINING AT ORIGIN

  
  if (myid == 0) {//------------------MASTER----------------------------------
    long double totalArea = 0;
    long long totalCalc = 0;
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
          limits[1] = place;  // BOUNDS START WHERE OLD BOUNDS BEGIN
        }

        //SENDING SEARCH BOUNDS TO SLAVE
        MPI_Send(limits, 2, MPI_LONG_LONG, j, 11, MPI_COMM_WORLD);
        j++;
      }

      //RECEIVEING AREAS
      for (sbe = 1; sbe < numprocs; sbe++) {
        MPI_Recv(&area, 1, MPI_DOUBLE, sbe, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&calcCounter, 1, MPI_LONG_LONG, sbe, 1, MPI_COMM_WORLD, &status);
        totalArea += area;
        totalCalc += calcCounter;
      }
      

    } while (totalSearch > place);
    endTime = MPI_Wtime();

    printf("That took %f seconds\n",endTime - startTime);
    fflush(stdout);

    printf("Total area: %.10LG \n",totalArea); 
    fflush(stdout);

    printf("Found with %lld calculations\n\n",totalCalc); 
    fflush(stdout);

  } 
  

  if (myid != 0) { //------------------SLAVES------------------------------------


    for (z = 0; z < (double)(totalSearch - 2)/packetSize/(numprocs - 1); z++) { 
      MPI_Recv(limits, 2, MPI_LONG_LONG, 0, 11, MPI_COMM_WORLD, &status); //RECIEVES SEARCH BOUNDS

      area = 0;
      areaUnderCurve(&calcCounter, &area, limits, percision);

      MPI_Send(&area, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
      MPI_Send(&calcCounter, 1, MPI_LONG_LONG, 0, 1, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();           /* EXIT MPI */
  return 0;
}



void areaUnderLine(double *area, long long *limits, double percision) {
  long double position;

  for (position = limits[0]; position + percision <= limits[1]; position += percision) {

    (*area) += position * 2 * percision;

  }
}



void areaUnderCurve(long long *calcCounter, double *area, long long *limits, double percision) {
  long double position;

  for (position = limits[0]; position + (percision * 2) <= limits[1]; position += percision) {
    (*calcCounter)++;
    (*area) += (cos(position) + 10) * percision;

  }
}



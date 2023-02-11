#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send2");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != 0) {
        double xx;
        pt >> xx;
        int buffsize = sizeof(double) +MPI_BSEND_OVERHEAD;
        double* buff=(double*)malloc(buffsize);
        MPI_Buffer_attach(buff,buffsize);
        MPI_Bsend(&xx, 1, MPI_DOUBLE, 0, rank, MPI_COMM_WORLD);
        MPI_Buffer_detach(buff, &buffsize);
    }
    else {
        
        double xx;
        for (int i = 1;i < size;i++) {
            int N;
            MPI_Status status;
            MPI_Recv(&xx, 1, MPI_DOUBLE, size-i,size-i , MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
            pt << xx;
        }

    }

    
}

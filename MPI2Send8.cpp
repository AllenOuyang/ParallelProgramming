#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send8");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a;
    int b;
    if (rank != 0)
    {
        pt >> a;
        if (a != 0)
        {
            b = rank;
            MPI_Send(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    else
    {
        MPI_Recv(&a, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        MPI_Recv(&b, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        pt << a;
        pt << b;
    }
}

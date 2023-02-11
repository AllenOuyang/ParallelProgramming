#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm26");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm comm;
    int reorder = 1;
    int dims[2];
    dims[0] = 2;
    dims[1] = size / 2;
    int periods[2] = { 0,1 };
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &comm);

    double buf;
    pt >> buf;

    int source1, dest1;
    int direct = 1, displ = 1;
    MPI_Cart_shift(comm, direct, displ, &source1, &dest1);
    //ShowLine(source1);
    //ShowLine(dest1);

    double recv_buf;
    MPI_Sendrecv(&buf, 1, MPI_DOUBLE, dest1, 0, &recv_buf, 1, MPI_DOUBLE, source1, 0, comm, MPI_STATUSES_IGNORE);
    pt << recv_buf;

}

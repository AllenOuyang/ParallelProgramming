#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm21");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    

    double buf;
    pt >> buf;

    int dims[3] = { 2, 2, size/4 };
    int periods[3] = { 0, 0, 0 };
    int reorder = true;
    MPI_Comm cartesian_communicator;

    MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, reorder, &cartesian_communicator);

    int remain_dims1[3] = { false, true, false };
    MPI_Comm subgrid_communicator1;
    MPI_Cart_sub(cartesian_communicator, remain_dims1, &subgrid_communicator1);

    int remain_dims2[2] = { true, false };
    MPI_Comm subgrid_communicator2;
    MPI_Cart_sub(subgrid_communicator1, remain_dims2, &subgrid_communicator2);
    
    int newrank;
    MPI_Comm_rank(subgrid_communicator2, &newrank);
    
    if (newrank == 0) {
        double recv_buf;
        MPI_Recv(&recv_buf, 1, MPI_DOUBLE, 1, 0, subgrid_communicator2, MPI_STATUSES_IGNORE);
        pt << recv_buf * buf;
    }
    else {
        MPI_Send(&buf, 1, MPI_DOUBLE, 0, 0, subgrid_communicator2);
    }

}

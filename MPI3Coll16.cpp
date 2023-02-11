#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll16");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);



    const int Max = 100;
    const int MAX = size * (size + 1) / 2;
    const int To_rank = (rank+1) * size;
    int n[Max], globaldata[Max], ircnt[Max],idisp[Max],j[Max],ircnt2[Max];
    for (int i = 0;i < MAX;i++) {           
        pt >> n[i];
    }
    for (int i = 0;i < size;i++) {
        ircnt[i] = i + 1;
    }
    idisp[0] = 0;
    for (int i = 0;i < size;i++) {
        idisp[i] = (rank+1) * i;
    }
    for (int i = 0;i < size;i++) {
        j[i] = i * (i + 1) / 2;
    }
    for (int i = 0;i < size;i++) {
        ircnt2[i] = rank + 1;
    }
        
    MPI_Alltoallv(&n[0] ,ircnt, j, MPI_INT, &globaldata[0], ircnt2, idisp, MPI_INT, MPI_COMM_WORLD);
    for (int i = 0;i <To_rank;i++)
        pt << globaldata[i];

    return ;

}

/*


*/
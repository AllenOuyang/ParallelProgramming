#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File10");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	char name[20];
	if (rank == 0) pt >> name;
	MPI_Bcast(name, 20, MPI_CHAR, 0, MPI_COMM_WORLD);

	MPI_File f;
	MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f);

	int int_sz;
	MPI_Type_size(MPI_INT, &int_sz);

	
	int *a = new int[rank];
	for (int i = 0; i < rank; i++) pt >> a[i];
	MPI_File_seek(f, rank*(rank - 1) / 2 * int_sz, MPI_SEEK_SET);
	MPI_File_write_all(f, a, rank, MPI_INT, MPI_STATUS_IGNORE);

}

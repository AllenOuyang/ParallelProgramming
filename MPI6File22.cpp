#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI6File22");
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

	int *a = new int[3];
	pt >> a[0] >> a[1] >> a[2];

	MPI_File f;
	MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f);
	
	int int_sz;
	MPI_Type_size(MPI_INT, &int_sz);

	MPI_Datatype t0, t;
	MPI_Type_vector(3, 1, size, MPI_INT, &t0);

	MPI_File_set_view(f, (size - rank - 1)*int_sz, MPI_INT, t0, "native", MPI_INFO_NULL);
	MPI_File_write_all(f, a, 3, MPI_INT, MPI_STATUS_IGNORE);

	MPI_File_close(&f);
}

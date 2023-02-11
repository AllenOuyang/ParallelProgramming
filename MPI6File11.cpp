#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI6File11");
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

	int size1;
	MPI_Type_size(MPI_DOUBLE, &size1);

	int a;
	pt >> a;

	MPI_Comm comm;
	int c = a != 0 ? 0 : MPI_UNDEFINED;
	MPI_Comm_split(MPI_COMM_WORLD, c, rank, &comm);

	if (c == 0) {
		MPI_File f;
		MPI_File_open(comm, name, MPI_MODE_RDWR, MPI_INFO_NULL, &f);

		double b;
		MPI_File_read_at_all(f, (a - 1) * size1, &b, 1, MPI_DOUBLE, MPI_STATUS_IGNORE);
		pt << b;
	}
}
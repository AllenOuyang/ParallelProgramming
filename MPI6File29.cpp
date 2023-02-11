#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File29");
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
	MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_RDWR, MPI_INFO_NULL, &f);

	int int_sz, N;
	MPI_Type_size(MPI_INT, &int_sz);

	MPI_Offset file_sz;
	MPI_File_get_size(f, &file_sz);
	int file_count = file_sz / int_sz;
	for (int i = 2; i <= 5; i++) {
		N = i;
		if (N*N*size == file_count) break;
		else continue;
	}
	
	MPI_Datatype t0;
	MPI_Type_vector(N, N, 3*N, MPI_INT, &t0);
	int disp = rank / 3 * N*3*N*int_sz + rank % 3 * N*int_sz;
	MPI_File_set_view(f, disp, MPI_INT, t0, "native", MPI_INFO_NULL);

	int *a = new int[N*N];
	MPI_File_read_all(f, a, N*N, MPI_INT, MPI_STATUS_IGNORE);
	for (int i = 0; i < N*N; i++) pt << a[i];

	MPI_File_close(&f);
}

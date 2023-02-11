#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI3Coll10");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	const int sumsize = size + 2;
	double* buf = (double*)malloc(sizeof(double) * (size+2));
	double* local_buf = (double*)malloc(sizeof(double) * 3);
	int* local_nums = (int*)malloc(sizeof(int) * size);
	int* offset = (int*)malloc(size * sizeof(int));
	
	if (buf == NULL) {
		printf("error\n");
		exit(-1);
	}
	if (local_buf == NULL) {
		printf("error\n");
		exit(-1);
	}
	if (local_nums == NULL) {
		printf("error\n");
		exit(-1);
	}
	if (offset == NULL) {
		printf("error\n");
		exit(-1);
	}


	if (rank == 0) {
		//if ( (buf!=NULL) && (local_nums!=NULL) && (offset!=NULL) ) {
		for (int i = 0; i < size + 2; i++) {
			pt >> buf[i];
		}
		for (int i = 0; i < size; i++) {
			local_nums[i] = 3;
			offset[i] = i;
		}
	//}
	}

	MPI_Scatterv(buf, local_nums, offset, MPI_DOUBLE, local_buf, 3, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	free(local_nums);
	free(offset);
	free(buf);

	//if (local_buf != NULL) {
		for (int i = 0; i < 3; i++) {
			pt << local_buf[i];
		}
	//}
	free(local_buf);
}

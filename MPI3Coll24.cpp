#include "pt4.h"
#include "mpi.h"
#include <vector>
/*
#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll24");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int* nums = new int[size];
	int* recvcounts = new int[size];
	for (int i = 0; i < size; ++i) {
		pt >> nums[i];
		recvcounts[i] = 1;
	}

	int res;
	MPI_Reduce_scatter(nums, &res, recvcounts, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	pt << res;
}
*/
void Solve()
{
    Task("MPI3Coll24");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::vector<int> n(size);
	std::vector<int> rcount(size, 1);
	for (int i = 0; i < size; ++i) {
		pt >> n[i];
	}
	int re;
	MPI_Reduce_scatter(&n[0], &re, &rcount[0], MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	pt << re;
}

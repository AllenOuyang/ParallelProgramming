#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm23");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int M, N, X, Y;
	if (rank == 0) pt >> M >> N;
	MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	MPI_Comm comm_sub;
	int color = rank < M*N ? 0 : MPI_UNDEFINED;
	MPI_Comm_split(MPI_COMM_WORLD, color, rank, &comm_sub);
	if (comm_sub == MPI_COMM_NULL)
		return;
	
	if (rank < M*N) pt >> X >> Y;
	

	MPI_Comm comm;
	int dims[] = { M,N }, periods[] = { 1,0 };
	MPI_Cart_create(comm_sub, 2, dims, periods, 0, &comm);

	if (rank < M*N) {
		int rank1, coords[] = { X,Y };         //这一段处理第一维度地循环
		while (coords[0] < 0) coords[0] += M;  //处理得并不是很漂亮
		if (coords[0] >= M) coords[0] %= M;    //
		if (Y<0||Y>N-1)
			pt << -1;
		else
		{
			MPI_Cart_rank(comm, coords, &rank1);
			pt << rank1;
		}	
	}
	
}

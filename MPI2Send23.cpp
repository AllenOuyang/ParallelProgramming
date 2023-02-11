#include "pt4.h"
#include "mpi.h"

const int Max = 20;
template<typename T>

void send(int t, int dest, MPI_Datatype d, int count) {
	T x[40];
	for (int i = 0;i < count;i++)
		pt >> x[i];
	MPI_Send(&x[0], count, d, dest, t, MPI_COMM_WORLD);
}
template<typename T>
void recv(MPI_Datatype d, MPI_Status& status,int ran,int count) {
    T xx[40];
    MPI_Recv(&xx[0],count,d,ran, status.MPI_TAG, MPI_COMM_WORLD, &status);
	for (int i = 0;i < count; i++) {
		pt << xx[i];
	}
}
void Solve()
{
    Task("MPI2Send23");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int t, n;
	if (rank != 0) {
		pt >> t >> n;
		if (t == 0) {
			send <int>(t, 0, MPI_INT, n);
		}
		else if (t == 1) {
			send<double>(t, 0, MPI_DOUBLE, n);

		}
	}
	else if(rank==0){
		MPI_Status status;
		for (int i = 1;i < size;i++) {
			int m;
			MPI_Probe(i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

			if (status.MPI_TAG == 1) {
				MPI_Get_count(&status, MPI_DOUBLE, &m);
				recv<double>(MPI_DOUBLE, status, i,m );
			}
			else {
				MPI_Get_count(&status, MPI_INT, &m);
				recv<int>(MPI_INT, status, i,m );
			}
		}
	}
		

}

/*
void send(int t, int dest, MPI_Datatype d, int count) {
	T x[Max];
	for (int i = 0;i < count;i++)
		pt >> x[i];
	MPI_Send(&x, count, d, dest, t, MPI_COMM_WORLD);
}
*/


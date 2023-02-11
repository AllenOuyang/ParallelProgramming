#include "pt4.h"
#include "mpi.h"
#include <vector>
void Solve()
{
    Task("MPI3Coll13");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        //MPI3Col13°。在每个过程中给出一个 R + 2 个整数的序列； 
        //R是进程的秩（即进程0给出两个整数，进程1给出三个整数，以此类推）。
        //使用 MPI_Allgatherv 函数将给定的整数发送给所有进程。
        //按发送进程的排名升序输出每个进程接收到的数据（包括从自身接收到的数量）。
        //MPI_Allgatherv(void* sbuf, int scount, MPI_Datatype stype, void* rbuf, int* rcounts, 
        // int* displs, MPI_Datatype rtype, MPI_Comm comm)
    const int MAX = 500;
    //std::vector<int> n(rank + 2);
    //std::vector<int> globaldata((size + 2) * (size + 2));
    //std::vector<int> ircnt(size);
    //std::vector<int> idisp(size);
    int n[MAX], globaldata[MAX], ircnt[MAX], idisp[MAX];
    int M = size * (size + 3) / 2;
    for (int i = 0;i < rank+2;i++) {
        pt >> n[i];
    }
    for (int i = 0;i < size;i++) {
        ircnt[i] = i + 2;
    }
    idisp[0] = 0;
    for (int i = 1;i < size;i++) {
        idisp[i] = idisp[i - 1] + i+1;
    }
    
    

    MPI_Allgatherv(&n[0], rank+2, MPI_INT,&globaldata[0] , ircnt, idisp, MPI_INT, MPI_COMM_WORLD);

    for(int i=0;i<M;i++)
        pt << globaldata[i];

    return ;
}

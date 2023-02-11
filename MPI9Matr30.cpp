#include "pt4.h"
#include "mpi.h"
#include <cmath>

int k;              // количество процессов
int r;              // ранг текущего процесса

int m, p, q;        // размеры исходных матриц
int m0, p0, q0;     // размеры блоков матриц
int k0;             // порядок декартовой решетки, равный sqrt(k)

int *a_, *b_, *c_;  // массивы для хранения исходных матриц в главном процессе
int *a, *b, *c;     // массивы для хранения блоков матриц в каждом процессе

MPI_Datatype MPI_BLOCK_A; // тип данных для блока матрицы A
MPI_Datatype MPI_BLOCK_B; // тип данных для блока матрицы B
MPI_Datatype MPI_BLOCK_C; // тип данных для блока матрицы C

MPI_Comm MPI_COMM_GRID = MPI_COMM_NULL;
                // коммуникатор, связанный с двумерной декартовой решеткой

void Matr3GatherFile() {
	int size_c = m0 * q0;
	char name[20];
	if (r == 0)
		pt >> name;
	MPI_Bcast(name, 20, MPI_CHAR, 0, MPI_COMM_WORLD);

	MPI_File f;
	MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f);

	int int_sz;
	MPI_Type_size(MPI_INT, &int_sz);

	int len0 = r % k0, high0 = r / k0, len, high;
	//处理输出长度
	if (len0*q0 > q) {
		len = 0;
	}
	else if ((len0 + 1)*q0 > q) {
		len = q - len0 * q0;
	}
	else {
		len = q0;
	}
	//处理输出高度
	if (high0 * m0 > m) {
		high = 0;
	}
	else if ((high0 + 1)*m0 > m) {
		high = m - high0 * m0;
	}
	else {
		high = m0;
	}

	for (int i = 0; i < high; i++) {
		MPI_Offset offset;
		offset = (high0*m0*q + len0*q0 + i * q)*int_sz;
		MPI_File_write_at(f, offset, &c[i*q0], len, MPI_INT, MPI_STATUS_IGNORE);
	}

	return;
}

void Solve()
{
    Task("MPI9Matr30");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    k = size;
    r = rank;
    k0 = (int)floor(sqrt((double)k) + 0.1);

	pt >> m >> q >> m0 >> q0;
	int size_c = m0 * q0;
	c = new int [size_c];
	for (int i = 0; i < size_c; i++)
		pt >> c[i];

	Matr3GatherFile();
}

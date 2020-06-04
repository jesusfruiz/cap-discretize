
compile_seq:
	gcc discretizo.c -o discretizo

compile_omp:
	gcc discretizo_omp.c -o discretizo_omp -fopenmp

compile_mpi:
	mpicc discretizo_mpi.c -o discretizo_mpi

exec_mpi: compile_mpi
	mpirun -np 4 discretizo_mpi

compile_seq:
	gcc discretizo.c -o discretizo

compile_omp:
	gcc discretizo_omp.c -o discretizo_omp -fopenmp

compile_mpi:
	mpicc discretizo_mpi.c -o discretizo_mpi

exec_seq: compile_seq
	./discretizo

exec_omp: compile_omp
	./discretizo_omp

exec_mpi: compile_mpi
	mpirun -np 4 discretizo_mpi

clean: 
	rm -f discretizo discretizo_mpi discretizo_omp > /dev/null
flags=--std=c++17 -pthread -O3 -fopenmp

a.out:mod_ops.o num_threads.o vector_mod.o test.o randomize.o performance.o entrypoint.o
	g++ $(flags) $^ -o $@

mod_ops.o:mod_ops.cpp mod_ops.h config.h
	g++ $(flags) -c mod_ops.cpp

num_threads.o:num_threads.cpp num_threads.h config.h
	g++ $(flags) -c num_threads.cpp

vector_mod.o:vector_mod.cpp vector_mod.h config.h
	g++ $(flags) -c vector_mod.cpp

test.o:test.cpp test.h config.h
	g++ $(flags) -c test.cpp

randomize.o:randomize.cpp randomize.h config.h
	g++ $(flags) -c randomize.cpp

performance.o:performance.cpp performance.h randomize.h config.h
	g++ $(flags) -c performance.cpp

entrypoint.o:entrypoint.cpp performance.h test.h config.h
	g++ $(flags) -c entrypoint.cpp

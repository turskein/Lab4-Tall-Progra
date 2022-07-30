UTILS = node.o graph.o Path.o quickSort.o Solver.o Conditional.o cond_op1.o Sort.o

run_main: main.cpp $(UTILS)
	g++ main.cpp -o main $(UTILS)
	./main

Solver.o: Solver.h Solver.cpp
	g++ -c Solver.cpp

node.o: node.h node.cpp
	g++ -c node.cpp

quickSort.o: quickSort.h quickSort.cpp
	g++ -c quickSort.cpp

graph.o: graph.h graph.cpp 
	g++ -c graph.cpp

Path.o: Path.h Path.cpp
	g++ -c Path.cpp

Sort.o: Sort.h Sort.cpp
	g++ -c Sort.cpp

clean: 
	rm -f test_graph *.o test_Node test_perfomance test_Solver \
	test_graph test_GivenAlgorithm main test_vectors test_Path \
	test_graph test_quicksort test_sort main test

all: cond_op1.o cond_op2 Conditional.o
	

cond_op1.o: cond_op1.h cond_op1.cpp
	g++ -c cond_op1.cpp

Conditional.o: Conditional.h Conditional.cpp
	g++ -c Conditional.cpp

test_Node: node.o test_Node.cpp
	g++ test_Node.cpp -o test_Node node.o
	./test_Node

test_Solver: test_Solver.cpp $(UTILS)
	g++ test_Solver.cpp -o test_Solver $(UTILS)
	./test_Solver

run_test: test_GivenAlgorithm.cpp $(UTILS)
	g++ test_GivenAlgorithm.cpp -o test_GivenAlgorithm $(UTILS)
	./test_GivenAlgorithm

run_perfomance: test_perfomance.cpp $(UTILS)
	g++ test_perfomance.cpp -o test_perfomance $(UTILS)
	./test_perfomance

test_quicksort: test_quicksort.cpp $(UTILS)
	g++ test_quicksort.cpp -o test_quicksort $(UTILS)
	./test_quicksort

test_graph: test_graph.cpp $(UTILS)
	g++ -o test_graph test_graph.cpp $(UTILS)
	./test_graph

test_Path: test_Path.cpp $(UTILS)
	g++ -o test_Path test_Path.cpp $(UTILS)
	./test_Path

test_sort: Sort.o node.o graph.o quickSort.o test_sort.cpp
	g++ test_sort.cpp -o test_sort Sort.o node.o graph.o quickSort.o

test.out:
	g++ test.cpp -o test

test: test.out
	./test

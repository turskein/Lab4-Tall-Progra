##CLEANCOND = make clean
MAKECOND = make
CONDOPS = cond_op1.o cond_op2.o Conditional.o
UTILS = quickSort.o

test_graph: node.o graph.o test_graph.cpp $(UTILS)
	g++ -o test_graph test_graph.cpp node.o graph.o $(UTILS)

#all:
#	+$(MAKE) -C conditionals

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

clean: cleanconditionals
	rm -f test_graph *.o test_Node test_perfomance test_Solver test_graph test_GivenAlgorithm main

cleanconditionals:
	+$(CLEANCOND) -C conditionals

all: cond_op1.o cond_op2 Conditional.o
	

cond_op1.o: cond_op1.h cond_op1.cpp
	g++ -c cond_op1.cpp

cond_op2.o: cond_op2.h cond_op2.cpp
	g++ -c cond_op2.cpp

Conditional.o: Conditional.h Conditional.cpp
	g++ -c Conditional.cpp

run_Node: node.o test_Node.cpp
	g++ test_Node.cpp -o test_Node node.o
	./test_Node

run_Solver: node.o graph.o Path.o quickSort.o Solver.o test_Solver.cpp
	g++ test_Solver.cpp -o test_Solver node.o graph.o Path.o quickSort.o Solver.o
	./test_Solver

run_test: test_GivenAlgorithm.cpp node.o graph.o Path.o quickSort.o Solver.o test_Solver.cpp
	g++ test_GivenAlgorithm.cpp -o test_GivenAlgorithm node.o graph.o Path.o quickSort.o Solver.o
	./test_GivenAlgorithm

run_main: main.cpp node.o graph.o Path.o quickSort.o Solver.o test_Solver.cpp
	g++ main.cpp -o main node.o graph.o Path.o quickSort.o Solver.o
	./main

run_perfomance: test_perfomance.cpp node.o graph.o Path.o quickSort.o Solver.o
	g++ test_perfomance.cpp -o test_perfomance node.o graph.o Path.o quickSort.o Solver.o
	./test_perfomance

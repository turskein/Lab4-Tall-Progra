all: cond_op1.o cond_op2 Conditional.o
	

cond_op1.o: cond_op1.h cond_op1.cpp
	g++ -c cond_op1.cpp

cond_op2.o: cond_op2.h cond_op2.cpp
	g++ -c cond_op2.cpp

Conditional.o: Conditional.h Conditional.cpp
	g++ -c Conditional.cpp

clean:
	rm -f *.o
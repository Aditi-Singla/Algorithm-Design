all: program1 program2

program1: longmultiplication.cpp
	g++ -g -o longmultiplication -O3 longmultiplication.cpp

program2: karatsuba.cpp
	g++ -g -o karatsuba -O3 karatsuba.cpp

clean:
	rm -f karatsuba longmultiplication

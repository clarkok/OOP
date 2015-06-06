main: main.o fraction.o
	clang++ -g --std=c++11 -o $@ $^
	
main.o: main.cpp fraction.h
	clang++ -c -g -std=c++11 -o $@ $<
	
fraction.o: fraction.cpp fraction.h
	clang++ -c -g -std=c++11 -o $@ $<
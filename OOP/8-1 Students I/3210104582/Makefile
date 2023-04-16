homework1: main.o model.o
	g++ -o homework1 main.o model.o

main.o: main.cpp model.h
	g++ -I ./ -c main.cpp
model.o: model.cpp model.h
	g++ -I ./ -c model.cpp

clean: 
	rm -f *.o homework1
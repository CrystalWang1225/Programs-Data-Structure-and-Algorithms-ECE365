merge.exe: main.o
	g++ -o merge.exe main.o
main.o: main.cpp
	g++ -c main.cpp

debug:
	g++ -g -o merge.exe main.cpp
clean:
	rm -f *.exe *.o *.stackdump *~

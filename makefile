default:
	g++ -std=c++11 -o tg.bin main.cpp parse.h parse.cpp

run:
	./tg.bin

clean:
	rm tg.bin

val:
	valgrind ./tg.bin

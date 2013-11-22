all: project_3

project_3: file.o main.o
	g++ -ggdb file.o main.o -o dnasearch

file.o: file.cpp file.h
	g++ -ggdb -c file.cpp

main.o: main.cpp file.cpp file.h
	g++ -ggdb -c main.cpp file.cpp

run:
	dnasearch > output.txt

diff:
	diff --ignore-all-space --ignore-blank-lines short_v.txt output.txt > results.txt
clean:
	rm main.o file.o dnasearch output.txt result.txt

run: compile
	./main.o

compile:
	@clang++ main.cpp -o main.o

clear:
	@rm main.o

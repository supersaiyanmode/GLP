CPPCOMPILER=g++

CCOMPILER=gcc

COMPILEFLAGS=-Wall -g -O3

UNITS=./glp.o ./linux/window_linux.o ./test/main.o

all : $(UNITS)
	$(CPPCOMPILER) $(COMPILEFLAGS) $(UNITS) -lGLU -lGL -lX11 -o test/a.out
./glp.o : ./glp.cpp ./glp.h
	$(CPPCOMPILER) $(COMPILEFLAGS) -c ./glp.cpp -o ./glp.o

./linux/window_linux.o : ./linux/window_linux.cpp ./linux/../glp.h ./linux/XVisualInfo_fixed.h
	$(CPPCOMPILER) $(COMPILEFLAGS) -c ./linux/window_linux.cpp -o ./linux/window_linux.o

./test/main.o : ./test/main.cpp ./test/../glp.h
	$(CPPCOMPILER) $(COMPILEFLAGS) -c ./test/main.cpp -o ./test/main.o

clean:
	rm -rf $(UNITS)

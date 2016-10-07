# ref: http://stackoverflow.com/questions/7815400/how-do-i-make-makefile-to-recompile-only-changed-files

#CXX = /usr/local/bin/g++-5
CXX = g++
LIBS = -I ./tools/eigen
CXXFLAGS = --std=c++0x
OBJDIR = build

FUNCS = build/func_centerMat.o build/func_genData.o build/func_readMatrix.o build/func_writeMatrix.o

all: bin/main

bin/main: build/main.o $(FUNCS)
	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $@

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c $^ -o $@
    
clean:
	rm -fv *.o bin/main build/*
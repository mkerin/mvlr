#CXX = /usr/local/bin/g++-5
CXX = g++
LIBS = -I ./tools/eigen
CXXFLAGS = --std=c++0x
OBJDIR = build

FUNCS = build/func_readMatrix.o build/func_writeMatrix.o build/func_genData.o
FUNCS2 = func_readMatrix.o func_writeMatrix.o func_genData.o

all: main

main: main.o $(FUNCS2)
	$(CXX) $(CXXFLAGS) $(LIBS) build/main.o $(FUNCS) -o bin/main

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c src/main.cpp -o build/main.o

func_writeMatrix.o: src/func_writeMatrix.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c src/func_writeMatrix.cpp -o build/func_writeMatrix.o

func_readMatrix.o: src/func_readMatrix.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c src/func_readMatrix.cpp -o build/func_readMatrix.o

func_genData.o: src/func_genData.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c src/func_genData.cpp -o build/func_genData.o
    
clean:
	rm -fv *.o bin/main build/*
#CXX = /usr/local/bin/g++-5
CXX = g++
LIBS = -I ./tools/eigen
CXXFLAGS = --std=c++0x

FUNCS = func_readMatrix.o func_writeMatrix.o func_genData.o

all: bin/main

bin/main: main.o $(FUNCS)
	$(CXX) $(CXXFLAGS) $(LIBS) main.o $(FUNCS) -o bin/main

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c src/main.cpp -o main.o

func_writeMatrix.o: src/func_writeMatrix.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c src/func_writeMatrix.cpp -o func_writeMatrix.o

func_readMatrix.o: src/func_readMatrix.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c src/func_readMatrix.cpp -o func_readMatrix.o

func_genData.o: src/func_genData.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -c src/func_genData.cpp -o func_genData.o
    
clean:
	rm *.o bin/main
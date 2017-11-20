build-all:build
EXECUTABLE=test
LIB=-lm -lzmq -lzmqpp -lpthread 
INC=-I$(wildcard include) -I$(wildcard /usr/local/include)
CFLAG=-g -Wall -std=c++11
CXX=g++
LIBRARY_PATH=-L$(wildcard lib) -L$(wildcard /usr/local/lib)
SOURCE=$(wildcard *.cpp) 

OBJS=$(patsubst %.cpp,%.o,$(SOURCE))
OBJ=$(filter-out main.o,$(OBJS))
.cpp.o:$(SOURCE)
	$(CXX) $(INC) $(LIBRARY_PATH) $(CFLAG) -c $< -o $@

build:$(OBJ)
	$(CXX) $(CFLAG) $(INC) $(OBJ) -o $(EXECUTABLE) $(LIB)
	
clean:
	rm -rf *.o
	rm -rf lib* $(EXECUTABLE)
.PHONY:build-all

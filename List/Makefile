CXX = clang++
CXXFLAGS = -std=c++14 -Wall -O3
SRC = $(wildcard ../List/*.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

main : main.o list.o
	$(CXX) $< list.o -o $@
	
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all : hello

.PHONY: clean
clean: 
	rm -f main.o list.o main
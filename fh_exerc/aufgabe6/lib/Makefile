CXX = g++
CXXFLAGS = -Wall -fpic -c -o
SRC = ../../aufgabe5
LIBTYPE = a # Default, kann durch Userinput geändert werden
CXXFILES = $(wildcard $(SRC)/*.cpp)
OBJ = $(notdir $(CXXFILES:.cpp=.o))
LIBNAME = aufgabe6

.PHONY: all clean

all: lib$(LIBNAME).$(LIBTYPE) 

$(TARGET): $(OBJ)

$(OBJ): $(CXXFILES)
	$(CXX) $(CXXFLAGS) $@ $<


clean:
	rm $(OBJ) lib* 


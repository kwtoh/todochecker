GCC=g++
CXXFLAGS=--std=c++17
SRC=src/main.cpp src/engine.cpp
STAGE=stage/todochecker
UNIT_SRC=unit_tests/unit.cpp src/engine.cpp
UNIT_STAGE=stage/unit


all: unit todochecker

todochecker: 
	$(GCC) $(CXXFLAGS) $(SRC) -o $(STAGE)

unit:
	$(GCC) $(CXXFLAGS) $(UNIT_SRC) -o $(UNIT_STAGE)

clean:
	 rm stage/*
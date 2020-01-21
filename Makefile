GCC=g++
CXXFLAGS=--std=c++17
CXXFLAGS_BEHIND=-lstdc++fs
SRC=src/main.cpp src/engine.cpp
TODOCHECKER=stage/todochecker
UNIT_SRC=unit_tests/unit.cpp src/engine.cpp
UNIT_STAGE=stage/unit
STAGE=stage


all: unit todochecker

todochecker: 
	mkdir -p $(STAGE)
	$(GCC) $(CXXFLAGS) $(SRC) $(CXXFLAGS_BEHIND) -o $(TODOCHECKER)

unit:
	mkdir -p $(STAGE)
	$(GCC) $(CXXFLAGS) $(UNIT_SRC) $(CXXFLAGS_BEHIND) -o $(UNIT_STAGE)

clean:
	 rm stage/*
